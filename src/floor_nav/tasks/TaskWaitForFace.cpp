#include <cmath>
#include "TaskWaitForFace.h"
#include "msg_pkg/msg/regions_of_interest_array.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace task_manager_msgs;
using namespace task_manager_lib;
using namespace floor_nav;
TaskIndicator TaskWaitForFace::initialise()
{
    triggered = false;
    face_sub = node->create_subscription<msg_pkg::msg::RegionsOfInterestArray>("face_detect",1,
            std::bind(&TaskWaitForFace::faceCallback,this,std::placeholders::_1));
      
	return TaskStatus::TASK_INITIALISED;

}



TaskIndicator TaskWaitForFace::iterate()
{
    if (triggered) {
		  return TaskStatus::TASK_COMPLETED;
    }
	return TaskStatus::TASK_RUNNING;
}

DYNAMIC_TASK(TaskFactoryWaitForFace)