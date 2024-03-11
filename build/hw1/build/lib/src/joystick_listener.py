import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

class JoystickListener(Node):
    def __init__(self):
        super().__init__('joystick_listener')
        self.subscription = self.create_subscription(
            Joy,
            'joy',
            self.joy_callback,
            10)
        self.subscription  # prevent unused variable warning

        
        self.publisher = self.create_publisher(Twist, '/robot/cmd_vel', 10)

    def joy_callback(self, msg):
        # 
        # 
        linear_x = msg.axes[1]  # 
        angular_z = msg.axes[2]  # 

        # 
        twist = Twist()
        twist.linear.x = linear_x
        twist.angular.z = angular_z

        # 
        self.publisher.publish(twist)

        # print to console
        self.get_logger().info(f'Published Twist command: linear_x = {linear_x}, angular_z = {angular_z}')

def main(args=None):
    rclpy.init(args=args)
    joystick_listener = JoystickListener()
    rclpy.spin(joystick_listener)
    joystick_listener.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
