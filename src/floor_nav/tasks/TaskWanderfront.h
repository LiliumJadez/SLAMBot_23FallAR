#ifndef TASK_WANDER_FRONT_H
#define TASK_WANDER_FRONT_H

#include "task_manager_lib/TaskInstance.h"
#include "floor_nav/SimTasksEnv.h"
#include "msg_pkg/msg/regions_of_interest_array.hpp"

using namespace task_manager_lib;

namespace floor_nav {
    struct TaskWanderFrontConfig : public TaskConfig {
        TaskWanderFrontConfig() {
            define("front_sector",  false,    "If true, use a front sector", true, front_sector);
            define("angular_range",  (15 * M_PI / 180),    "Size of angular sensors (in rad)", true, angular_range);
            define("safety_range",  0.25,    "Distance at which we need to stop", false, safety_range);
            define("dont_care_range",  1.0,    "Distance at which we can ignore obstacles", false, dont_care_range);
            define("max_linear_speed",  1.0,    "Max allowed linear speed", false, max_linear_speed);
            define("max_angular_speed",  1.0,    "Max allowed angular speed", false, max_angular_speed);
        }
        bool front_sector;
        double angular_range;
        double safety_range;
        double dont_care_range;
        double max_linear_speed;
        double max_angular_speed;
    };
    class TaskWanderFront : public TaskInstance<TaskWanderFrontConfig, SimTasksEnv> {
    public:
        TaskWanderFront(TaskDefinitionPtr def, TaskEnvironmentPtr env) : Parent(def, env) {}
        virtual ~TaskWanderFront() {}

        virtual TaskIndicator iterate();

        virtual TaskIndicator terminate();
    };

    class TaskFactoryWanderFront : public TaskDefinition<TaskWanderFrontConfig, SimTasksEnv, TaskWanderFront> 
    {
        public:
            TaskFactoryWanderFront(TaskEnvironmentPtr env) : 
                Parent("WanderFront", "Wander aimlessly while avoiding obstacles in the front", true, env) {}
            virtual ~TaskFactoryWanderFront() {}
    };
};

#endif // TASK_WANDER_FRONT_H
