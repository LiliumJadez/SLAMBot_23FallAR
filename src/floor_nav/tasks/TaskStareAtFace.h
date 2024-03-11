#ifndef TASK_STARE_AT_FACE_H
#define TASK_STARE_AT_FACE_H

#include "task_manager_lib/TaskInstance.h"
#include "floor_nav/SimTasksEnv.h"
#include "rclcpp/rclcpp.hpp"
#include "msg_pkg/msg/regions_of_interest_array.hpp"  

using namespace task_manager_lib;

namespace floor_nav {
    // Task configuration might include parameters for face detection, like minimum face size or detection confidence
    struct TaskStareAtFaceConfig : public TaskConfig {
        TaskStareAtFaceConfig() {
            define("max_angular_velocity",1.0,"Maximum angular velocity",false,max_angular_velocity); 
            define("k_theta", 0.5, "Gain for angutar contral",false,k_theta);
            define("center_pixel_threshald",232.0, "number of pixel error at which the face is centered",false, center_pixel_threshold);
            define("rotation_angle",  0.03,"Unit angle to rotate by",false,rotation_angle); 
            define("image_width", 720.0,"Image width pixel",false,image_width);        }

    double k_theta;
    double max_angular_velocity; 
    double center_pixel_threshold; 
    double rotation_angle; 
    double image_width; 
    bool relative;
};
class TaskStareAtFace : public TaskInstance<TaskStareAtFaceConfig,SimTasksEnv>
{
    protected:
        rclcpp::Subscription<msg_pkg::msg::RegionsOfInterestArray>::SharedPtr face_sub; 
        double initial_heading;
        sensor_msgs::msg::RegionOfInterest face_roi;

        void faceCallback(const msg_pkg::msg::RegionsOfInterestArray::SharedPtr msg); 
    public:
        TaskStareAtFace(TaskDefinitionPtr def,TaskEnvironmentPtr env) : Parent(def,env){}
        virtual ~TaskStareAtFace(){};
        virtual TaskIndicator initialise(); 
        virtual TaskIndicator iterate(); 
        virtual TaskIndicator terminate();
};

class TaskFactoryStareAtFace : public TaskDefinition<TaskStareAtFaceConfig,SimTasksEnv,TaskStareAtFace>
{
    public:
        TaskFactoryStareAtFace(TaskEnvironmentPtr env):
            Parent("StareAtFace", "Reach a desired heading angle", true, env) {}
        virtual ~TaskFactoryStareAtFace() {};
};
}

#endif 