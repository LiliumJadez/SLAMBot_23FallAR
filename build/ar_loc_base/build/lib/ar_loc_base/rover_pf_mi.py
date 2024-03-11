#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
import numpy as np
import numpy
from numpy import *
from numpy.linalg import inv
from math import pi, sin, cos
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import PoseStamped, PoseArray, Pose
import bisect
import threading
from rover_driver_base.rover_kinematics import RoverKinematics
from ar_loc_base.rover_odo import RoverOdo


class RoverPF(RoverOdo):
    def __init__(self, node, initial_pose, initial_uncertainty):
        super().__init__(node,initial_pose, initial_uncertainty)
        self.N = 500
        self.particles = [self.X + self.drawNoise(initial_uncertainty) for i in range(0,self.N)]
        self.pa_pub = node.create_publisher(PoseArray,"~/particles",1)
        # print self.particles

    def getRotationFromWorldToRobot(self):
        return self.getRotation(-self.X[2,0])

    def drawNoise(self, norm):
        if type(norm)==list:
            return mat(vstack(norm)*(2*random.rand(len(norm),1)-vstack([1]*len(norm))))
        else:
            return mat(multiply(norm,((2*random.rand(3,1)-vstack([1,1,1])))))

    def applyDisplacement(self, X, DeltaX, Uncertainty):
        # TODO : Apply the displacement DeltaX to the state X and add noise
        theta = X[2,0]  
        cos_theta, sin_theta = cos(theta), sin(theta)
        rotated_delta_x = DeltaX[0,0] * cos_theta - DeltaX[1,0] * sin_theta
        rotated_delta_y = DeltaX[0,0] * sin_theta + DeltaX[1,0] * cos_theta

        X[0,0] += rotated_delta_x + numpy.random.normal(0, Uncertainty)
        X[1,0] += rotated_delta_y + numpy.random.normal(0, Uncertainty)
        X[2,0] += DeltaX[2,0] + numpy.random.normal(0, Uncertainty)


        return X



    def predict(self, logger, motor_state, drive_cfg, encoder_precision):
        self.lock.acquire()
        # The first time, we need to initialise the state
        if self.first_run:
            self.motor_state.copy(motor_state)
            self.first_run = False
            self.lock.release()
            return self.X
        # then compute odometry using least square
        iW = self.prepare_inversion_matrix(drive_cfg)
        S = self.prepare_displacement_matrix(self.motor_state,motor_state,drive_cfg)
        self.motor_state.copy(motor_state)

        # Apply the particle filter prediction step here
        # TODO
        # print self.particles
        logger.info("Prediction: S="+str(S.T)+" X="+str(self.X.T))
        DeltaX = iW * S  # Displacement in the robot frame
        for i in range(len(self.particles)):
            self.particles[i] = self.applyDisplacement(self.particles[i], DeltaX, encoder_precision)
        

        self.updateMean()
        self.lock.release()

    def evalParticleAR(self, X, Z, L, Uncertainty):
        # Calculate expected observation in the particle's frame
        dx, dy = L[0,0] - X[0,0], L[1,0] - X[1,0]
        expected_angle = arctan2(dy, dx) - X[2,0]
        expected_distance = sqrt(dx**2 + dy**2)
        
        # Calculate actual observation
        observed_angle = arctan2(Z[1,0], Z[0,0])
        observed_distance = sqrt(Z[0,0]**2 + Z[1,0]**2)
        
        # Compute difference using circular distance for angles
        angle_diff = (observed_angle - expected_angle + pi) % (2 * pi) - pi
        distance_diff = observed_distance - expected_distance
        
        # Assuming Gaussian noise, compute the likelihood
        sigma_angle, sigma_distance = Uncertainty, Uncertainty
        likelihood = exp(-0.5 * ((angle_diff / sigma_angle)**2 + (distance_diff / sigma_distance)**2))
        
        return likelihood


    def evalParticleCompass(self, X, Value, Uncertainty):
        # Compute the difference in orientation
        orientation_diff = (X[2,0] - Value + pi) % (2 * pi) - pi
        
        # Assuming Gaussian noise, compute the likelihood
        sigma_orientation = Uncertainty
        likelihood = exp(-0.5 * (orientation_diff / sigma_orientation)**2)
        
        return likelihood

    

    def resample_particles(self, weights):
        N = self.N
        effective_sample_size = 1 / np.sum(np.square(weights))
        new_particles = []
        
        if effective_sample_size < N / 2:  
            positions = (np.arange(N) + np.random.random()) / N
            indexes = np.zeros(N, 'i')
            cumulative_sum = np.cumsum(weights)
            i, j = 0, 0
            while i < N:
                if positions[i] < cumulative_sum[j]:
                    indexes[i] = j
                    i += 1
                else:
                    j += 1
            new_particles = [self.particles[index].copy() for index in indexes]
            
            for p in new_particles:
                jitter = np.random.normal(0, 0.01, size=p.shape)  
                # Adjust jitter magnitude
                p += jitter
        else:
            new_particles = self.particles.copy()

        return new_particles


    def update_ar(self, logger, Z, L, Uncertainty):
        self.lock.acquire()
        logger.info("Update: L="+str(L.T)+" X="+str(self.X.T))
        weights = []
        for particle in self.particles:
            weight = self.evalParticleAR(particle, Z, L, Uncertainty)
            weights.append(weight)
        
        # Normalize weights
        total_weight = sum(weights)
        weights = [w / total_weight for w in weights]
        
        # Resample particles based on weights
        self.particles = self.resample_particles(weights)
        
        self.updateMean()
        self.lock.release()


    def update_compass(self, logger, angle, Uncertainty):
        self.lock.acquire()
        logger.info("Update: S="+str(angle)+" X="+str(self.X.T))
        
        weights = []
        for particle in self.particles:
            weight = self.evalParticleCompass(particle, angle, Uncertainty)
            weights.append(weight)
        
        # Normalize and resample as in update_ar
        total_weight = sum(weights)
        weights = [w / total_weight for w in weights]
        
        self.particles = self.resample_particles(weights)
        
        self.updateMean()
        self.lock.release()


    def updateMean(self):
        X = mat(zeros((3,1)))
        for x in self.particles:
            X += x
        self.X = X / len(self.particles)
        
        return self.X

    def publish(self, pose_pub, odom_pub, target_frame, stamp, child_frame):
        pose = super().publish(pose_pub, odom_pub, target_frame, stamp, child_frame)
        # rclpy.get_logger().info("Publishing particles")
        pa = PoseArray()
        pa.header = pose.header
        for p in self.particles:
            po = Pose()
            po.position.x = p[0,0]
            po.position.y = p[1,0]
            q = self.quaternion_from_euler(0, 0, p[2,0])
            po.orientation.x = q[0]
            po.orientation.y = q[1]
            po.orientation.z = q[2]
            po.orientation.w = q[3]
            pa.poses.append(po)
        self.pa_pub.publish(pa)


