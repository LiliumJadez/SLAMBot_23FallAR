#!/usr/bin/env python3

import sys
import rclpy
import random
from math import pi, radians
from task_manager_client_py.TaskClient import *
from std_srvs.srv import Trigger

rclpy.init(args=sys.argv)
tc = TaskClient('/floor_tasks', 0.2)

scale = 2.0
vel = 0.5
# Initialize the cancel request condition
face_received = ConditionVariable("face detected")

# Define a service to handle cancel requests
def handle_trigger(req, resp):
    global face_received
    face_received.set(False)
    print("Face detected")
    resp.success = True
    resp.message = "Done"
    return resp

s = tc.create_service(Trigger, 'face_received', handle_trigger)

while True:
    tc.Wait(duration = 0.5)
    face_received.set(False)# Reset the cancel request flag at the beginning of each loop
    wait_for_face = tc.WaitForFace(foreground = False)
    tc.addCondition(ConditionIsCompleted("face detected", tc, wait_for_face))
    tc.addCondition(face_received)
    
    try:
        print('Ready for wander')
        tc.WanderFront()
        print('Wander Completed')

    except TaskConditionException as e:
        tc.get_logger().info(
            "Path interrupted on condition %s" %"or".join([str(c) for c in e.conditions])
        )
        print('face is detected')
        print(
            "Path interrupted on condition %s" %"or".join([str(c) for c in e.conditions])
        )
        tc.StareAtFace()
        tc.Wait(duration = 3)

        angle = 60 * random.random()
        tc.SetHeading(target = radians(angle), relative = True)

tc.get_logger().info("Completed.")