#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from numpy import *
from numpy.linalg import inv
from math import pi, sin, cos
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import PoseWithCovarianceStamped, PoseStamped
import threading
from rover_driver_base.rover_kinematics import RoverKinematics
from ar_loc_base.rover_odo import RoverOdo


class RoverKF(RoverOdo):
    def __init__(self, node, initial_pose, initial_uncertainty):
        super().__init__(node, initial_pose, initial_uncertainty)  # 调用父类构造函数初始化
        self.X = mat(vstack(initial_pose))  # 将初始位置转换为矩阵形式
        self.P = mat(diag(initial_uncertainty))  # 初始不确定性（协方差矩阵）
        # 创建ROS发布者，用于发布位置和不确定性相关的消息
        self.ellipse_pub = node.create_publisher(Marker, "~/ellipse", 1)
        self.pose_with_cov_pub = node.create_publisher(PoseWithCovarianceStamped, "~/pose_with_covariance", 1)

    def predict(self, logger, motor_state, drive_cfg, encoder_precision):
        self.lock.acquire()  # 线程锁，确保线程安全
        if self.first_run:
            # 如果是第一次运行，初始化马达状态
            self.motor_state.copy(motor_state)
            self.first_run = False
            self.lock.release()  # 释放锁
            return (self.X, self.P)
        # print "-"*32
        
        # 计算逆矩阵和位移矩阵，用于预测新位置
        iW = self.prepare_inversion_matrix(drive_cfg)
        S = self.prepare_displacement_matrix(self.motor_state, motor_state, drive_cfg).reshape((12,1))
        self.motor_state.copy(motor_state)
        rot = array(self.getRotation(self.X[2,0]))
        rot = vstack((rot, [0, 0]))
        rot = hstack((rot, [[0], [0], [1]]))
        logger.info(f"rot.shape: {rot.shape}, iw.shape: {iW.shape}, S.shape: {S.shape}")
        DeltaX = rot @ iW @ S  # 位移矩阵
        u = iW @ S


        # TODO: Implement Kalman prediction
        # ultimately : 
        self.X =  self.X + DeltaX
        logger.info(f"DeltaX.shape: {DeltaX.shape}")
        A = array([[1, 0, -sin(self.X[2,0])*u[0,0] - cos(self.X[2,0])*u[1, 0]],
                     [0, 1,  cos(self.X[2,0])*u[0,0] - sin(self.X[2,0])*u[1, 0]],
                     [0, 0,  1]])
        logger.info(f"rot.shape: {rot.shape}, iw.shape: {iW.shape}, S.shape: {S.shape}, diag(S).shape: {diag(S).shape}")
        self.P = A @ self.P @ A.T + diag([encoder_precision, encoder_precision, encoder_precision])
        # + rot @ iW @ diag(S.flatten()) @ iW.T @ rot.T 
        # Update the covariance matrix, P = A*P*A' + Q as per the Kalman filter equations

        self.lock.release() 
        return (self.X, self.P)

    def update_ar(self, logger, Z, L, uncertainty):

        self.lock.acquire() 
        logger.info(f"Update: L={str(L.T)} X={str(self.X.T)}")
        # TODO: According to the AR tag data, update the position and uncertainty
        H = array([
            [-cos(self.X[2,0]), -sin(self.X[2,0]), -sin(self.X[2,0])*(L[0,0]-self.X[0,0]) + cos(self.X[2,0])*(L[1,0]-self.X[1,0])],
            [ sin(self.X[2,0]), -cos(self.X[2,0]), -cos(self.X[2,0])*(L[0,0]-self.X[0,0]) - sin(self.X[2,0])*(L[1,0]-self.X[1,0])]
        ])
        K = self.P @ H.T @ inv(H @ self.P @ H.T + diag([uncertainty,uncertainty]))
        I = eye(3)

        expected_measurement = array([
            [cos(self.X[2,0])*(L[0,0]-self.X[0,0]) + sin(self.X[2,0])*(L[1,0]-self.X[1,0])],
            [-sin(self.X[2,0])*(L[0,0]-self.X[0,0]) + cos(self.X[2,0])*(L[1,0]-self.X[1,0])]
        ])

        # Update the state estimate and covariance matrix
        self.X = self.X + K @ (Z - expected_measurement)    
        # Update the position and uncertainty according to the AR tag data
        # self.X = self.X + K @ array((Z - L + self.X[0:2,0]))
        # # # logger.info()
        # innovation = Z - H @ self.X[:3]  
        # self.X[:3] = self.X[:3] + K @ innovation  
        self.P = (I - K @ H) @ self.P
        logger.info(f"shape of self.X: {self.X.shape}")
        self.lock.release()  
        return (self.X, self.P)

    def update_compass(self, logger, Z, uncertainty):
        self.lock.acquire()  
        logger.info(f"Update: S={str(Z)} X={str(self.X.T)}")
        # TODO: update the position and uncertainty according to the compass data
        H = array([[0,0,1]])
        K = self.P @ H.T @ inv(H @ self.P @ H.T + diag([uncertainty]))
        I = eye(3)
        self.X = self.X + K @ array([[Z - self.X[2,0]]])
        self.P = (I - K @ H) @ self.P
        logger.info(f"shape of H: {H.shape}, shape of K: {K.shape}, shape of I: {I.shape}")
        
        self.lock.release() 
        return (self.X, self.P)

    def publish(self, pose_pub, odom_pub, target_frame, stamp, child_frame):
        # publish the pose and uncertainty related messages to ROS
        pose_simple = super().publish(pose_pub, odom_pub, target_frame, stamp, child_frame)
        pose = PoseWithCovarianceStamped()
        pose.header = pose_simple.header
        pose.pose.pose = pose_simple.pose
        C = [0.]*36
        C[0] = self.P[0,0]; C[1] = self.P[0,1]; C[5] = self.P[0,2]
        C[6] = self.P[1,0]; C[7] = self.P[1,1]; C[11] = self.P[1,2]
        C[30] = self.P[2,0]; C[31] = self.P[2,1]; C[35] = self.P[2,2]
        pose.pose.covariance = C
        self.pose_with_cov_pub.publish(pose)  # publish the pose with covariance

        # publish the ellipse marker
        marker = Marker()
        marker.header = pose.header
        marker.ns = "kf_uncertainty"
        marker.id = 1
        marker.type = Marker.CYLINDER
        marker.action = Marker.ADD
        marker.pose = pose.pose.pose
        marker.scale.x = 3 * sqrt(self.P[0,0])  # x轴半径
        marker.scale.y = 3 * sqrt(self.P[1,1]);  # y轴半径
        marker.scale.z = 0.1;  # 高度
        marker.color.a = 1.0;  # 透明度
        marker.color.r = 1.0;  # 红色
        marker.color.g = 1.0;  # 绿色
        marker.color.b = 0.0;  # 黄色
        self.ellipse_pub.publish(marker)  # 发布椭圆标记
