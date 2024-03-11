#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <geometry_msgs/msg/twist.hpp>

class JoystickListener : public rclcpp::Node
{
public:
    JoystickListener() : Node("joystick_listener")
    {
        // subscribe to Joy message and publish to /robot/cmd_vel
        subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "/joy", 10, std::bind(&JoystickListener::joy_callback, this, std::placeholders::_1));
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/robot/cmd_vel", 10);
    }

private:
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        if (msg->axes.size() < 3) {
            RCLCPP_ERROR(this->get_logger(), "Received Joy message with insufficient axes size");
            return;
        }

        double linear_x = msg->axes[1];  // move forward/backward
        double angular_z = msg->axes[2];  // rotate

        // publish Twist message
        auto twist = geometry_msgs::msg::Twist();
        twist.linear.x = linear_x;
        twist.angular.z = angular_z;
        publisher_->publish(twist);

        // record log
        RCLCPP_INFO(this->get_logger(), "Published Twist command: linear_x = %f, angular_z = %f", linear_x, angular_z);
    }

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<JoystickListener>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
