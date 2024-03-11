#!/usr/bin/env python
from geometry_msgs.msg import Twist
import numpy
from numpy.linalg import pinv
from math import atan2, hypot, pi, cos, sin

# Front Left, Front Right, Center Left....
prefix=["FL","FR","CL","CR","RL","RR"]

class RoverMotors:
    def __init__(self):
        self.steering={}
        self.drive={}
        for k in prefix:
            self.steering[k]=0.0
            self.drive[k]=0.0
    def copy(self,value):
        for k in prefix:
            self.steering[k]=value.steering[k]
            self.drive[k]=value.drive[k]

# Where the center of rover is
class DriveConfiguration:
    def __init__(self,radius,x,y,z):
        self.x = x
        self.y = y
        self.z = z
        self.radius = radius


class RoverKinematics:
    def __init__(self):
        self.X = numpy.asmatrix(numpy.zeros((3,1)))
        self.motor_state = RoverMotors()
        self.ICR = (pi/2,pi/2)
        self.first_run = True

    def ICR_cart_to_polar(x,y):
        return (atan2(y,x), atan(hypot(y,x)))

    def ICR_polar_to_cart(theta,phi):
        r = tan(phi)
        return (r*cos(theta),r*sin(theta))

    def ICR_from_twist(vx,vy,wz):
        theta=atan2(vy,vx)+pi/2
        phi=atan2(hypot(vx,vy),wz)
        return (theta,phi)

    def ICR_to_twist(theta,phi,v):
        r = tan(phi)
        T = Twist()
        T.angular.z = v / r
        T.linear.x = v * cos(theta-pi/2)
        T.linear.y = v * sin(theta-pi/2)
        return T

    def filter_twist(self, twist_in, drive_cfg):
        twist_out = Twist()
        vx = twist_in.linear.x; vy = twist_in.linear.y; wz = twist_in.angular.z
        v = hypot(vx,vy)
        if abs(v)<1e-2:
            # not moving while not changing the current ICR
            theta,phi = self.ICR
            return ICR_to_twist(theta,phi,1e-3)
        elif abs(wz)<1e-2:
            pass
        else:
            pass
        return twist_out

    def twist_to_motors(self, twist, drive_cfg, skidsteer=False, drive_state=None):
        motors = RoverMotors()
        if skidsteer:
            for k in drive_cfg.keys():
                # TODO: In case we are in skidsteer mode (driving like a tank)
                # Insert here the steering and velocity of 
                # each wheel in skid-steer mode
                v_x = twist.linear.x
                v_y = twist.linear.v
                omega_z = twist.angular.z
                if k == 'FL' or k == 'RL' or k=='CL':
                    W_x = drive_cfg['CL'].x
                    W_y = drive_cfg['CL'].y
                    v_w_x = v_x - omega_z * W_y
                    motors.steering[k] = 0
                    motors.drive[k] = v_w_x
                if k == 'FR' or k == 'RR' or k=='CR':
                    W_x = drive_cfg['CR'].x
                    W_y = drive_cfg['CR'].y
                    v_w_x = v_x - omega_z * W_y
                    motors.steering[k] = 0
                    motors.drive[k] = v_w_x
                motors.steering[k] = 0
                motors.drive[k] = 0
        else:
            for k in drive_cfg.keys():
                # TODO: In case we are in rolling without slipping mode (driving normally)
                # Insert here the steering and velocity of 
                # each wheel in rolling-without-slipping mode
                v_x = twist.linear.x
                v_y = twist.linear.y
                omega_z = twist.angular.z
                W_x = drive_cfg[k].x
                W_y = drive_cfg[k].y
                v_w_x = v_x - omega_z * W_y
                v_w_y = v_y + omega_z * W_x
                motors.steering[k] = atan2(v_w_y, v_w_x)
                motors.drive[k] = hypot(v_w_x, v_w_y)/drive_cfg[k].radius
                # rotate the steering angle if it is greater than pi/2 or less than -pi/2
                if motors.steering[k] > pi/2:
                    motors.steering[k] -= pi
                    motors.drive[k] = -motors.drive[k]
                if motors.steering[k] <-pi/2:
                    motors.steering[k] += pi
                    motors.drive[k] = -motors.drive[k]
        return motors

    def prepare_inversion_matrix(self,drive_cfg):
        # TODO: Build pseudo inverse of W using the notation from the class. The matrix size below is wrong.
        A = numpy.array([
            [1, 0, -drive_cfg['FL'].y],
            [0, 1, drive_cfg['FL'].x],
            [1, 0, -drive_cfg['FR'].y],
            [0, 1, drive_cfg['FR'].x],
            [1, 0, -drive_cfg['CL'].y],
            [0, 1, drive_cfg['CL'].x],
            [1, 0, -drive_cfg['CR'].y],
            [0, 1, drive_cfg['CR'].x],
            [1, 0, -drive_cfg['RL'].y],
            [0, 1, drive_cfg['RL'].x],
            [1, 0, -drive_cfg['RR'].y],
            [0, 1, drive_cfg['RR'].x],
        ])
        iW = pinv(A)
        return iW

    def prepare_displacement_matrix(self, motor_state_t1, motor_state_t2, drive_cfg):
        # then compute odometry using least square
        # TODO: Build S using the notation from the class. The matrix size below is wrong.
        B = []
        for k in prefix:
            ds = (motor_state_t2.drive[k] - motor_state_t1.drive[k]) % (2*pi)
            if ds>pi:
                ds -= 2*pi
            if ds<-pi:
                ds += 2*pi
            
            ds *= drive_cfg[k].radius
            B.append(ds*cos((motor_state_t1.steering[k]+motor_state_t2.steering[k])/2))
            B.append(ds*sin((motor_state_t1.steering[k]+motor_state_t2.steering[k])/2))
        S = numpy.array(B)
        return S


    def compute_displacement(self, motor_state, drive_cfg):
        # The first time, we need to initialise the state
        if self.first_run:
            self.motor_state.copy(motor_state)
            self.first_run = False
            return numpy.asmatrix(numpy.zeros((3,1)))
        # then compute odometry using least square
        # We assume that S = W * dX, hence dX = iW * S, where iW is the pseudo inverse of W
        # TODO: First compute iW based on the wheel positions given in drive_cfg
        iW = self.prepare_inversion_matrix(drive_cfg)
        # TODO: Then compute the displacement matrix S based on the current motor_state, and the previous one stored in self.motor_state
        S = self.prepare_displacement_matrix(self.motor_state,motor_state,drive_cfg)
        # Finally the displacement in the local frame is the product
        dX = iW * S 
        # And we backup the current motor state
        self.motor_state.copy(motor_state)
        return dX

    def integrate_odometry(self, motor_state, drive_cfg):
        # First compute the local displacement in the robot frame
        dX = self.compute_displacement(motor_state,drive_cfg)
        # TODO: Now integrate the local displacement in the global frame
        self.X[0,0] += dX[0,0] * cos(self.X[2,0]) - dX[1,0] * sin(self.X[2,0])
        self.X[1,0] += dX[1,0] * sin(self.X[2,0]) + dX[1,0] * cos(self.X[2,0])
        self.X[2,0] += dX[2,0]
        return self.X

        # This is the result of Odometry return




def quaternion_from_euler(ai, aj, ak):
    ai /= 2.0
    aj /= 2.0
    ak /= 2.0
    ci = cos(ai)
    si = sin(ai)
    cj = cos(aj)
    sj = sin(aj)
    ck = cos(ak)
    sk = sin(ak)
    cc = ci*ck
    cs = ci*sk
    sc = si*ck
    ss = si*sk

    q = np.empty((4, ))
    q[0] = cj*sc - sj*cs
    q[1] = cj*ss + sj*cc
    q[2] = cj*cs - sj*sc
    q[3] = cj*cc + sj*ss

    return q

