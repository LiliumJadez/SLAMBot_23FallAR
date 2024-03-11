#include "TaskGoToPose.h" 
#include "rclcpp/rclcpp.hpp"
#include <math.h>
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;

inline double degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}

TaskIndicator TaskGoToPose::initialise() {
    RCLCPP_INFO(getNode()->get_logger(), "Going to %.2f %.2f with orientation %.2f radians", cfg->goal_x, cfg->goal_y, cfg->goal_theta);
    if (cfg->relative) {
        const geometry_msgs::msg::Pose2D & tpose = env->getPose2D();
        x_init = tpose.x;
        y_init = tpose.y;
    } else {
        x_init = 0.0;
        y_init = 0.0;
    }
    return TaskStatus::TASK_INITIALISED;
}

TaskIndicator TaskGoToPose::iterate() {
    const geometry_msgs::msg::Pose2D & tpose = env->getPose2D();
    double dx = x_init + cfg->goal_x - tpose.x;
    double dy = y_init + cfg->goal_y - tpose.y;
    double r = hypot(dy, dx);
    double goal_angle = atan2(dy, dx);
    double angle_diff = remainder(goal_angle - tpose.theta, 2*M_PI);

    if (cfg->holonomic) {
        geometry_msgs::msg::Twist twist;
        twist.linear.x = cfg->goal_x - tpose.x;
        twist.linear.y = cfg->goal_y - tpose.y;
        twist.angular.z = 0; // could be adjusted if orientation is also a goal
        // twist.angular.z = cfg->goal_theta - tpose.theta;
    } else{
        // Non-holonomic
        if (r < cfg->dist_threshold) {
            double theta_error = remainder(cfg->goal_theta - tpose.theta, 2*M_PI);
            if (fabs(theta_error) < degreesToRadians(5)) {
                return TaskStatus::TASK_COMPLETED;
            }
        }

        if (cfg->use_smart_control) {
            if (fabs(angle_diff) > degreesToRadians(10)) { 
                double rot = std::clamp(cfg->k_alpha * angle_diff, -cfg->max_angular_velocity, cfg->max_angular_velocity);
                env->publishVelocity(0, rot);
            } else { 
                double vel = std::clamp(cfg->k_v * r, -cfg->max_velocity, cfg->max_velocity);
                env->publishVelocity(vel, cfg->k_alpha * angle_diff);
            }
        } else {
            double vel = std::clamp(cfg->k_v * r, -cfg->max_velocity, cfg->max_velocity);
            double rot = std::clamp(cfg->k_alpha * angle_diff, -cfg->max_angular_velocity, cfg->max_angular_velocity);
            env->publishVelocity(vel, rot);
        }
    }
    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskGoToPose::terminate() {
    env->publishVelocity(0, 0);
    return TaskStatus::TASK_TERMINATED;
}

DYNAMIC_TASK(TaskFactoryGoToPose);

