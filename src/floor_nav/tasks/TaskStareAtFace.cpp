#include <math.h>
#include "TaskStareAtFace.h"  
#include "rclcpp/rclcpp.hpp"
#include "msg_pkg/msg/regions_of_interest_array.hpp"  
using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;

TaskIndicator TaskStareAtFace::initialise() {
    face_sub = node->create_subscription<msg_pkg::msg::RegionsOfInterestArray>(
        "face_detect", 1, std::bind(&TaskStareAtFace::faceCallback, this, std::placeholders::_1));
    initial_heading = env->getPose2D().theta;
    return TaskStatus::TASK_INITIALISED;
}

TaskIndicator TaskStareAtFace::iterate() {
    if (face_roi.width == 0) {
        RCLCPP_INFO(node->get_logger(), "face not detected yet!");
        return TaskStatus::TASK_RUNNING; 
    }

    uint32_t face_center_x = face_roi.x_offset + (face_roi.width / 2);
    uint32_t image_center_x = cfg->image_width / 2;
    int offset_x = static_cast<int>(face_center_x) - static_cast<int>(image_center_x);

    RCLCPP_INFO(node->get_logger(), "Face Center X: %u, Image Center X: %u, offset X: %d", 
                face_center_x, image_center_x, offset_x);

 
    if (std::abs(offset_x) < cfg->center_pixel_threshold) {
        RCLCPP_INFO(node->get_logger(), "centered face detected!");
        // by setting the angular velocity to 0, we stop the robot from rotating
        env->publishVelocity(0, cfg->max_angular_velocity); 
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate a short rotation
        env->publishVelocity(0, 0);
        return TaskStatus::TASK_COMPLETED;
    } else {
        // calculate the rotation angle based on the offset(-338 to -126)
        double rot = cfg->k_theta * offset_x;
        // clamp the rotation to the maximum angular velocity
        rot = std::clamp(rot, -cfg->max_angular_velocity, cfg->max_angular_velocity);
    
        env->publishVelocity(0, rot);
    }

    return TaskStatus::TASK_RUNNING;
}

TaskIndicator TaskStareAtFace::terminate() {
    env->publishVelocity(0, 0); // make sure the robot stops moving
    return TaskStatus::TASK_TERMINATED;
}

void TaskStareAtFace::faceCallback(const msg_pkg::msg::RegionsOfInterestArray::SharedPtr msg) {
    if (msg->regions.empty()) {
        return;
    }
    face_roi = msg->regions[0];
}

DYNAMIC_TASK(TaskFactoryStareAtFace);  // Update the factory for TaskStareAtFace

