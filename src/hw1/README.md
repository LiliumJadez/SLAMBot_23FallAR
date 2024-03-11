## Assignment 1

Open 4 terminals, 3 are required and 1 is optional.
For different terminal, run the command following:
- ros2 run src joystick
- ros2 run joy joy_node --ros-args
- ros2 topic echo /joy
- ros2 topic echo /robot/cmd_vel

You can observe the joystick status in last 2 terminals.