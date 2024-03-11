#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from numpy import *
from numpy.linalg import inv
from math import pi, sin, cos
from visualization_msgs.msg import Marker, MarkerArray
import threading

#  Reminder
# Y = G(X)
# Cov(X) = C
# 
# Cov(Y) = dG/dX C dG/dX^T
# 
# Z = H(X,Y)
# Cov(X) = C
# Cov(Y) = D
# 
# Cov(Z) = dG/dX C dG/dX^T + dG/dY D dG/dY^T


def getRotation(theta):
        # Create a 2x2 rotation matrix based on angle theta
        R = mat(zeros((2,2)))
        R[0,0] = cos(theta); R[0,1] = -sin(theta)
        R[1,0] = sin(theta); R[1,1] = cos(theta)
        return array(R)
class Landmark:
    def __init__(self, Z, X , R):
        # Initialise a landmark based on measurement Z, 
        # current position X and uncertainty R
        # Observation is Z = g(X) + noise
        # X is the current position of the robot
        # R is the uncertainty of the measurement
        # TODO
        # L = g(X,Z) = X_0 + R_theta
        # Cov(L) = dG/dX Cov(X) dG/dX^T + dG/dZ Cov(Z) dG/dZ^T
        L0 = X[:2] + getRotation(X[2,0]) @ Z 
        self.L = L0
        self.P = R


        # self.L =vstack([0,0])
        # self.P =mat([[0,0],[0,0]])

    def update(self,Z, X, R):
        # Update the landmark based on measurement Z, 
        # current position X and uncertainty R(via the Kalman update)
        H = getRotation(-X[2,0])
        K = self.P @ H.T @ inv(H @ self.P @ H.T + R)
        self.P = (eye(2) - K @ H) @ self.P
        self.L = self.L + K @ (Z - H @ (self.L - X[:2]))    
        return
class MappingKF:
    def __init__(self, node):
        self.lock = threading.Lock()
        self.marker_list = {}
        self.marker_pub = node.create_publisher(MarkerArray,"~/landmarks",1)

    def update_ar(self, logger, Z, X, Id, uncertainty):
        self.lock.acquire()
        # TODO
        logger.info("Update: Z="+str(Z.T)+" X="+str(X.T)+" Id="+str(Id))
        R = diag([uncertainty,uncertainty])
        if Id in self.marker_list:
            # Known landmark, we can run the KF update
            # TODO
            self.marker_list[Id].update(Z, X, array(R))
        else:
            # New landmark, we need to create it
            # TODO
            self.marker_list[Id] = Landmark(Z, X, array(R))
            logger.info("Initialised landmark %d at %s" %
                    (Id,str(self.marker_list[Id].L.T)))
        self.lock.release()


    def publish(self, target_frame, timestamp):
        ma = MarkerArray()
        for id in self.marker_list:
            marker = Marker()
            marker.header.stamp = timestamp
            marker.header.frame_id = target_frame
            marker.ns = "landmark_kf"
            marker.id = id
            marker.type = Marker.CYLINDER
            marker.action = Marker.ADD
            Lkf = self.marker_list[id]
            marker.pose.position.x = Lkf.L[0,0]
            marker.pose.position.y = Lkf.L[1,0]
            marker.pose.position.z = 0.
            marker.pose.orientation.x = 0.
            marker.pose.orientation.y = 0.
            marker.pose.orientation.z = 1.
            marker.pose.orientation.w = 0.
            marker.scale.x = max(3*sqrt(Lkf.P[0,0]),0.05)
            marker.scale.y = max(3*sqrt(Lkf.P[1,1]),0.05)
            marker.scale.z = 0.5;
            marker.color.a = 1.0;
            marker.color.r = 1.0;
            marker.color.g = 1.0;
            marker.color.b = 0.0;
            marker.lifetime = rclpy.time.Duration(seconds=3.).to_msg()
            ma.markers.append(marker)
            marker = Marker()
            marker.header.stamp = timestamp
            marker.header.frame_id = target_frame
            marker.ns = "landmark_kf"
            marker.id = 1000+id
            marker.type = Marker.TEXT_VIEW_FACING
            marker.action = Marker.ADD
            Lkf = self.marker_list[id]
            marker.pose.position.x = Lkf.L[0,0]
            marker.pose.position.y = Lkf.L[1,0]
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
