#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
import numpy as np
from numpy.linalg import inv
from math import pi, sin, cos,hypot,sqrt
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import PoseWithCovarianceStamped, PoseStamped
import threading
from rover_driver_base.rover_kinematics import RoverKinematics
from ar_loc_base.rover_odo import RoverOdo


def getRotation(theta):
    # Create a 2x2 rotation matrix based on angle theta
    R = np.array([
        [cos(theta), -sin(theta)],
        [sin(theta),  cos(theta)]
    ])
    return R
class MappingKF(RoverOdo):
    def __init__(self, node, initial_pose, initial_uncertainty):
        super().__init__(node,initial_pose,initial_uncertainty)
        self.lock = threading.Lock()
        self.X = np.mat(np.vstack(initial_pose))
        self.P = np.mat(np.diag(initial_uncertainty))
        self.idx = {}
        self.marker_pub = node.create_publisher(MarkerArray,"~/landmarks",1)

    def predict_rover(self, logger, motor_state, drive_cfg, encoder_precision):
        self.lock.acquire()
        # The first time, we need to initialise the state
        if self.first_run:
            self.motor_state.copy(motor_state)
            self.first_run = False
            self.lock.release()
            return (self.X, self.P)
        # print("-"*32)
        # then compute odometry using least square
        iW = self.prepare_inversion_matrix(drive_cfg)
        S = self.prepare_displacement_matrix(self.motor_state,motor_state,drive_cfg)
        self.motor_state.copy(motor_state)
        
        # Implement Kalman prediction here
        # Compute the update in the body frame and the resulting uncertainty in the body frame
        DeltaX = iW @ S
        DeltaP = np.diag([encoder_precision, encoder_precision, encoder_precision])  # Uncertainty in the body frame
        self.lock.release()
        return self.predict_delta(logger, DeltaX, DeltaP)

    def predict_delta(self, logger, DeltaX, DeltaP):
        self.lock.acquire()
        DeltaX = DeltaX.reshape((3,1))
        # Update the state using the provided displacement, but we only need to deal with a subset of the state
        # Assumption: deltaX and deltaP are defined in the body frame and need to be rotated to account for the jacobian 
        # of the transfer function
        # TODO
        theta = self.X[2, 0]
        # self.X[0:3,0] = ...
        # self.P[0:3,0:3] = ...
        rot = np.array(getRotation(self.X[2, 0]))
        rot = np.vstack((rot, [0, 0]))
        rot = np.hstack((rot, [[0], [0], [1]]))
        DeltaX = np.array(DeltaX)
        DeltaX_global = rot @ DeltaX
        logger.info("DeltaX_global: " + str(DeltaX_global))
        self.X[:3, 0] = self.X[:3, 0] + DeltaX_global
        # Update uncertainty
        J = np.array([[1, 0, -sin(theta) * DeltaX[0, 0] - cos(theta) * DeltaX[1, 0]], 
                        [0, 1,  cos(theta) * DeltaX[0, 0] - sin(theta) * DeltaX[1, 0]], 
                        [0, 0, 1]])
        self.P[0:3, 0:3] = J @ self.P[0:3, 0:3] @ J.T + rot @ DeltaP
        self.lock.release()
        return (self.X,self.P)


    def update_ar(self, logger, Z, id, uncertainty):
        self.lock.acquire()
        # TODO
        logger.info("Update: Z="+str(Z.T)+" X="+str(self.X.T)+" Id="+str(id))
        print("Update: Z="+str(Z.T)+" X="+str(self.X.T)+" Id="+str(id))
        # Update the full state self.X and self.P based on landmark id
        # be careful that this might be the first time that id is observed
        # TODO
        # self.X = ...
        # self.P = ...
        if (id not in self.idx):
            self.idx[id] = self.X.shape[0]
            position = self.X[0:2, 0] + getRotation(self.X[2, 0]) @ Z
            self.X = np.vstack([self.X, position])

            R1 = np.diag([uncertainty, uncertainty])
            pGpx = np.array([[1, 0, -Z[0,0]*sin(self.X[2])-Z[1, 0]*cos(self.X[2, 0])],
                             [0, 1, Z[0, 0]*cos(self.X[2]-Z[1, 0]*sin(self.X[2, 0]))]                             
                             ])
            covX = self.P[:3, :3]
            R = R1 + pGpx @ covX @ pGpx.T
            logger.info("shape of self.P, init: " + str(self.P.shape))
            self.P = np.block([[self.P, np.zeros((self.P.shape[0], 2))], 
                               [np.zeros((2, self.P.shape[1])), R]])
            logger.info("shape of self.P, init2: " + str(self.P.shape))
               
        else:
            # Known landmark, KF update
            l = self.idx[id]
            # H = getRotation(-self.X[2, 0])
            # K = self.P[l:l+2, l:l+2] @ H.T @ inv(H @ self.P[l:l+2, l:l+2] @ H.T + np.mat(np.diag([uncertainty, uncertainty])))
            # self.P = (np.eye(3) - K @ H) @ self.P
            # self.X[l:l+2, 0] = self.X[l:l+2, 0] + K @ (Z - H @ (self.X[l:l+2, 0] - self.X[0:2, 0]))

            H_rr = np.array([
                [-(Z[0, 0] - self.X[0, 0]) * sin(self.X[2, 0]) + (Z[1, 0] - self.X[1, 0]) * cos(self.X[2, 0])],
                [-(Z[0, 0] - self.X[0, 0]) * cos(self.X[2, 0]) - (Z[1, 0] - self.X[1, 0]) * sin(self.X[2, 0])]
                            ])
            H_R = np.block([np.array([[-cos(self.X[2,0]), -sin(self.X[2,0])],
                                      [sin(self.X[2, 0]), -cos(self.X[2, 0])]]), H_rr])
            H_L = getRotation(-self.X[2, 0])
            H = np.zeros((2, self.X.shape[0]))
            H[:,0:3] = H_R
            H[:,l:l+2] = H_L
            logger.info("H: " + str(H))
            R1 = np.diag([uncertainty, uncertainty])
            pGpx = np.array([[1, 0, -Z[0, 0]*sin(self.X[2, 0])-Z[1, 0]*cos(self.X[2, 0])],
                             [0, 1, Z[0, 0]*cos(self.X[2, 0]-Z[1, 0]*sin(self.X[2, 0]))]                             
                             ])
            covX = self.P[:3, :3]
            R = R1 + pGpx @ covX @ pGpx.T

            K = self.P @ H.T @ inv(H @ self.P @ H.T + R)
            logger.info("shape of self.P, init3: " + str(self.P.shape))
            self.P = (np.eye(self.P.shape[0]) - K @ H) @ self.P
            logger.info("shape of self.P, init4: " + str(self.P.shape))
            expected_measurement = getRotation(-self.X[2, 0]) @ (-self.X[0:2, 0] + self.X[l:l+2, 0])
            logger.info("shape of self.X, updadte1: " + str(self.X.shape))
            self.X = self.X + K @ (Z - expected_measurement)
            logger.info("shape of self.X, updadte: " + str(self.X.shape))


        self.lock.release()
        return (self.X,self.P)

    def update_compass(self, logger, Z, uncertainty):
        self.lock.acquire()
        logger.info("Update: S="+str(Z)+" X="+str(self.X.T))
        # Update the full state self.X and self.P based on compass measurement
        H = np.zeros((1, self.X.shape[0]))
        H[0,2] = 1
        K = self.P @ H.T @ inv(H @ self.P @ H.T + np.diag([uncertainty]))
        logger.info("shape of self.P, init5: " + str(self.P.shape))

        self.P = (np.eye(self.P.shape[0]) - K @ H) @ self.P
        logger.info(str(Z -self.X[2,0]))
        self.X = self.X + K @ np.array([[Z - self.X[2, 0]]])
        logger.info("shape of self.P, init6: " + str(self.P.shape))

        
        self.lock.release()
        return (self.X,self.P)


    def publish(self, pose_pub, odom_pub, target_frame, stamp, child_frame):
        pose = super().publish(pose_pub, odom_pub, target_frame, stamp, child_frame)
        ma = MarkerArray()
        marker = Marker()
        marker.header = pose.header
        marker.ns = "kf_uncertainty"
        marker.id = 5000
        marker.type = Marker.CYLINDER
        marker.action = Marker.ADD
        marker.pose = pose.pose
        marker.pose.position.z = -0.1
        marker.scale.x = 3*sqrt(self.P[0,0])
        marker.scale.y = 3*sqrt(self.P[1,1]);
        marker.scale.z = 0.1;
        marker.color.a = 1.0;
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 1.0;
        ma.markers.append(marker)
        for id in self.idx:
            marker = Marker()
            marker.header = pose.header
            marker.ns = "landmark_kf"
            marker.id = id
            marker.type = Marker.CYLINDER
            marker.action = Marker.ADD
            l = self.idx[id]
            marker.pose.position.x = self.X[l,0]
            marker.pose.position.y = self.X[l+1,0]
            marker.pose.position.z = -0.1
            marker.pose.orientation.x = 0.
            marker.pose.orientation.y = 0.
            marker.pose.orientation.z = 1.
            marker.pose.orientation.w = 0.
            marker.scale.x = 3*sqrt(self.P[l,l])
            marker.scale.y = 3*sqrt(self.P[l+1,l+1]);
            marker.scale.z = 0.1;
            marker.color.a = 1.0;
            marker.color.r = 1.0;
            marker.color.g = 1.0;
            marker.color.b = 0.0;
            marker.lifetime = rclpy.time.Duration(seconds=3.).to_msg()
            ma.markers.append(marker)
            marker = Marker()
            marker.header = pose.header
            marker.ns = "landmark_kf"
            marker.id = 1000+id
            marker.type = Marker.TEXT_VIEW_FACING
            marker.action = Marker.ADD
            marker.pose.position.x = self.X[l+0,0]
            marker.pose.position.y = self.X[l+1,0]
            marker.pose.position.z = 1.0
            marker.pose.orientation.x = 0.
            marker.pose.orientation.y = 0.
            marker.pose.orientation.z = 1.
            marker.pose.orientation.w = 0.
            marker.text = str(id)
            marker.scale.x = 1.0
            marker.scale.y = 1.0
            marker.scale.z = 0.2
            marker.color.a = 1.0;
            marker.color.r = 1.0;
            marker.color.g = 1.0;
            marker.color.b = 1.0;
            marker.lifetime = rclpy.time.Duration(seconds=3.).to_msg()
            ma.markers.append(marker)
        self.marker_pub.publish(ma)

