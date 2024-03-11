#!/usr/bin/env python3
# ROS specific imports
import sys
import rclpy
from math import pi
from task_manager_client_py.TaskClient import *

rclpy.init(args=sys.argv)
tc = TaskClient('/floor_tasks', 0.2)

scale = 2.0
vel = 0.5

try:
    # Navigate to the first point with an orientation of -45 degrees
    tc.GoToPose(goal_x=-scale, goal_y=-scale, goal_theta=-pi/4, max_velocity=vel, use_smart_control=True)
    tc.Wait(duration=1.0)
    # Rotate to face 90 degrees at the second point
    tc.GoToPose(goal_x=-scale, goal_y=scale, goal_theta=pi/2, max_velocity=vel, use_smart_control=True)
    tc.Wait(duration=1.0)
    # Navigate to the third point with an orientation of 180 degrees (facing backwards)
    tc.GoToPose(goal_x=scale, goal_y=scale, goal_theta=pi, max_velocity=vel, use_smart_control=True)
    tc.Wait(duration=1.0)
    # Rotate to face -90 degrees (or 270 degrees) at the fourth point
    tc.GoToPose(goal_x=scale, goal_y=-scale, goal_theta=-pi/2, max_velocity=vel, use_smart_control=True)
    tc.Wait(duration=1.0)
    # Return to the starting point with the initial orientation
    tc.GoToPose(goal_x=-scale, goal_y=-scale, goal_theta=-pi/4, max_velocity=vel, use_smart_control=True)

except TaskException as e:
    tc.get_logger().error("Exception caught: " + str(e))


tc.get_logger().info("Mission completed")
