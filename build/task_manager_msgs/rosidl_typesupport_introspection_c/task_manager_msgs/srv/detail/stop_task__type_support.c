// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from task_manager_msgs:srv/StopTask.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "task_manager_msgs/srv/detail/stop_task__rosidl_typesupport_introspection_c.h"
#include "task_manager_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "task_manager_msgs/srv/detail/stop_task__functions.h"
#include "task_manager_msgs/srv/detail/stop_task__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  task_manager_msgs__srv__StopTask_Request__init(message_memory);
}

void task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_fini_function(void * message_memory)
{
  task_manager_msgs__srv__StopTask_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_message_member_array[1] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(task_manager_msgs__srv__StopTask_Request, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_message_members = {
  "task_manager_msgs__srv",  // message namespace
  "StopTask_Request",  // message name
  1,  // number of fields
  sizeof(task_manager_msgs__srv__StopTask_Request),
  task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_message_member_array,  // message members
  task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_message_type_support_handle = {
  0,
  &task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_task_manager_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, StopTask_Request)() {
  if (!task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_message_type_support_handle.typesupport_identifier) {
    task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &task_manager_msgs__srv__StopTask_Request__rosidl_typesupport_introspection_c__StopTask_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "task_manager_msgs/srv/detail/stop_task__rosidl_typesupport_introspection_c.h"
// already included above
// #include "task_manager_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "task_manager_msgs/srv/detail/stop_task__functions.h"
// already included above
// #include "task_manager_msgs/srv/detail/stop_task__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  task_manager_msgs__srv__StopTask_Response__init(message_memory);
}

void task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_fini_function(void * message_memory)
{
  task_manager_msgs__srv__StopTask_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_message_member_array[1] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(task_manager_msgs__srv__StopTask_Response, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_message_members = {
  "task_manager_msgs__srv",  // message namespace
  "StopTask_Response",  // message name
  1,  // number of fields
  sizeof(task_manager_msgs__srv__StopTask_Response),
  task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_message_member_array,  // message members
  task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_message_type_support_handle = {
  0,
  &task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_task_manager_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, StopTask_Response)() {
  if (!task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_message_type_support_handle.typesupport_identifier) {
    task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &task_manager_msgs__srv__StopTask_Response__rosidl_typesupport_introspection_c__StopTask_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "task_manager_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "task_manager_msgs/srv/detail/stop_task__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers task_manager_msgs__srv__detail__stop_task__rosidl_typesupport_introspection_c__StopTask_service_members = {
  "task_manager_msgs__srv",  // service namespace
  "StopTask",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // task_manager_msgs__srv__detail__stop_task__rosidl_typesupport_introspection_c__StopTask_Request_message_type_support_handle,
  NULL  // response message
  // task_manager_msgs__srv__detail__stop_task__rosidl_typesupport_introspection_c__StopTask_Response_message_type_support_handle
};

static rosidl_service_type_support_t task_manager_msgs__srv__detail__stop_task__rosidl_typesupport_introspection_c__StopTask_service_type_support_handle = {
  0,
  &task_manager_msgs__srv__detail__stop_task__rosidl_typesupport_introspection_c__StopTask_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, StopTask_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, StopTask_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_task_manager_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, StopTask)() {
  if (!task_manager_msgs__srv__detail__stop_task__rosidl_typesupport_introspection_c__StopTask_service_type_support_handle.typesupport_identifier) {
    task_manager_msgs__srv__detail__stop_task__rosidl_typesupport_introspection_c__StopTask_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)task_manager_msgs__srv__detail__stop_task__rosidl_typesupport_introspection_c__StopTask_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, StopTask_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, StopTask_Response)()->data;
  }

  return &task_manager_msgs__srv__detail__stop_task__rosidl_typesupport_introspection_c__StopTask_service_type_support_handle;
}
