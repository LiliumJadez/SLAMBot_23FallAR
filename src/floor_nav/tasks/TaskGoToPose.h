#ifndef TASK_GO_TO_POSE_H
#define TASK_GO_TO_POSE_H

#include "task_manager_lib/TaskInstance.h"
#include "floor_nav/SimTasksEnv.h"
#include "rclcpp/rclcpp.hpp"

using namespace task_manager_lib;

namespace floor_nav {
    struct TaskGoToPoseConfig : public TaskConfig {
        TaskGoToPoseConfig() : TaskConfig() { 
            define("goal_x", 0.0, "X coordinate of destination", false, goal_x);
            define("goal_y", 0.0, "Y coordinate of destination", false, goal_y);
            define("goal_theta", 0.0, "Orientation angle of destination in radians", false, goal_theta); // New
            define("k_v", 1.0, "Gain for velocity control", false, k_v);
            define("k_alpha", 1.0, "Gain for angular control", false, k_alpha);
            define("max_velocity", 1.0, "Max allowed velocity", false, max_velocity);
            define("max_angular_velocity", 1.0, "Max allowed angular velocity", false, max_angular_velocity);
            define("dist_threshold", 0.1, "Distance at which the target is considered reached", false, dist_threshold);
            define("relative", false, "Is the target pose relative or absolute", true, relative);
            define("use_smart_control", false, "Use smart control method instead of dumb", true, use_smart_control); // New
            define("holonomic", false, "If true, take advantage of the rover's holonomic capabilities", false, holonomic); 
        }

        double goal_x, goal_y, goal_theta;  
        double k_v, k_alpha;
        double max_velocity, max_angular_velocity;
        double dist_threshold;
        bool relative, use_smart_control; 
        bool holonomic;

    };

    class TaskGoToPose : public TaskInstance<TaskGoToPoseConfig, SimTasksEnv> {
    protected:
        double x_init, y_init;
    public:
        TaskGoToPose(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def, env) {}
        virtual ~TaskGoToPose() {};

        virtual TaskIndicator initialise();
        virtual TaskIndicator iterate();
        virtual TaskIndicator terminate();
    };

    class TaskFactoryGoToPose : public TaskDefinition<TaskGoToPoseConfig, SimTasksEnv, TaskGoToPose> {
    public:
        TaskFactoryGoToPose(TaskEnvironmentPtr env) : 
            Parent("GoToPose", "Reach a desired destination with orientation", true, env) {}
        virtual ~TaskFactoryGoToPose() {};
    };
};

#endif // TASK_GO_TO_POSE_H
