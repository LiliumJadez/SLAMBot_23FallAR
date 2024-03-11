import rclpy
from rclpy.node import Node

class HelloWorldPublisher(Node):
    def __init__(self):
        super().__init__('hello_world_publisher')
        self.timer = self.create_timer(1, self.timer_callback)

    def timer_callback(self):
        self.get_logger().info('Hello World')

def main(args=None):
    rclpy.init(args=args)
    hello_world_publisher = HelloWorldPublisher()
    rclpy.spin(hello_world_publisher)
    hello_world_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
