#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from numpy import *
from numpy.linalg import inv
from math import pi, sin, cos, fmod
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import PoseWithCovarianceStamped, PoseStamped, TransformStamped
from nav_msgs.msg import Odometry
import threading
from rover_driver_base.rover_kinematics import *

class RoverOdo(RoverKinematics):
    def __init__(self, node, initial_pose, initial_uncertainty):
        super().__init__()  # 调用父类构造函数
        self.first_run = True  # 标志位，指示是否是首次运行
        self.lock = threading.Lock()  # 线程锁，用于确保线程安全
        self.X = mat(vstack(initial_pose))  # 将初始位置转换为矩阵形式

    def getRotation(self, theta):
        # 根据给定角度theta，创建一个2x2的旋转矩阵
        R = mat(zeros((2,2)))
        R[0,0] = cos(theta); R[0,1] = -sin(theta)
        R[1,0] = sin(theta); R[1,1] = cos(theta)
        return R

    def diffAngle(self, theta1, theta2):
        # 计算并返回两个角度之间的差值，结果被规范化到[-π, π]区间
        return fmod(theta1 - theta2 + 4*pi + pi, 2*pi) - pi

    def normAngle(self, theta):
        # 规范化给定的角度到[-π, π]区间
        return fmod(theta + 4*pi + pi, 2*pi) - pi
    
    def predict(self, logger, motor_state, drive_cfg, encoder_precision):
        # 根据马达状态预测机器人的新位置
        self.lock.acquire()  # 获取锁
        if self.first_run:
            # 如果是首次运行，初始化马达状态，然后返回
            self.motor_state.copy(motor_state)
            self.first_run = False
            self.lock.release()  # 释放锁
            return 
        # 计算逆矩阵和位移矩阵，用于最小二乘法计算新位置
        iW = self.prepare_inversion_matrix(drive_cfg)
        S = self.prepare_displacement_matrix(self.motor_state, motor_state, drive_cfg)
        self.motor_state.copy(motor_state)
        
        # 这里可以实现Kalman滤波器的预测步骤
        
        # 根据当前姿态角theta计算旋转矩阵Rtheta
        theta = self.X[2,0]
        Rtheta = mat([[cos(theta), -sin(theta), 0], 
                      [sin(theta),  cos(theta), 0],
                      [         0,           0, 1]]);
        # 使用伪逆方法估计位置变化DeltaX
        DeltaX = iW*S
        self.X = self.X + Rtheta*DeltaX  # 更新位置
        self.X[2,0] = self.normAngle(self.X[2,0])  # 规范化角度
        self.lock.release()  # 释放锁

    def update_ar(self, logger, Z, L, uncertainty):
        
        return 

    def update_compass(self, logger, Z, uncertainty):
        
        return 

    def publish(self, pose_pub, odom_pub, target_frame, stamp, child_frame):
        # 发布机器人的姿态信息到ROS
        pose = PoseStamped()
        pose.header.frame_id = target_frame
        pose.header.stamp = stamp
        pose.pose.position.x = self.X[0,0]
        pose.pose.position.y = self.X[1,0]
        pose.pose.position.z = 0.0  # 假设在2D平面内，因此z坐标为0
        Q = self.quaternion_from_euler(0, 0, self.X[2,0])  # 从欧拉角到四元数
        pose.pose.orientation.x = Q[0]
        pose.pose.orientation.y = Q[1]
        pose.pose.orientation.z = Q[2]
        pose.pose.orientation.w = Q[3]
        pose_pub.publish(pose)  # 发布姿态信息
        odom = Odometry()
        odom.header = pose.header
        odom.child_frame_id = child_frame
        odom.pose.pose = pose.pose
        # 其他里程计字段暂时不填充
        odom_pub.publish(odom)
        return pose

    def broadcast(self, br, target_frame, stamp):
        # 发布TF变换，避免在TF树中出现问题
        t = TransformStamped()
        t.header.stamp = stamp
        t.header.frame_id = target_frame
        t.child_frame_id = "arloc"
        t.transform.translation.x = self.X[0,0]
        t.transform.translation.y = self.X[1,0]
        t.transform.translation.z = 0.0
        q = self.quaternion_from_euler(0, 0, self.X[2,0])  # 从欧拉角到四元数
        t.transform.rotation.x = q[0]
        t.transform.rotation.y = q[1]
        t.transform.rotation.z = q[2]
        t.transform.rotation.w = q[3]
        br.sendTransform(t)  # 发送变换

    def quaternion_from_euler(self, ai, aj, ak):
        # 将欧拉角转换为四元数，用于姿态表示
        # 这是一个在机器人学中常用的转换方法，可以避免万向节锁问题
        ai /= 2.0
        aj /= 2.0
        ak /= 2.0
        ci = math.cos(ai)
        si = math.sin(ai)
        cj = math.cos(aj)
        sj = math.sin(aj)
        ck = math.cos(ak)
        sk = math.sin(ak)
        cc = ci*ck
        cs = ci*sk
        sc = si*ck
        ss = si*sk

        q = empty((4, ))
        q[0] = cj*sc - sj*cs
        q[1] = cj*ss + sj*cc
        q[2] = cj*cs - sj*sc
        q[3] = cj*cc + sj*ss

        return q


