// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from msg_pkg:msg/RegionsOfInterestArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "msg_pkg/msg/detail/regions_of_interest_array__rosidl_typesupport_introspection_c.h"
#include "msg_pkg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "msg_pkg/msg/detail/regions_of_interest_array__functions.h"
#include "msg_pkg/msg/detail/regions_of_interest_array__struct.h"


// Include directives for member types
// Member `regions`
#include "sensor_msgs/msg/region_of_interest.h"
// Member `regions`
#include "sensor_msgs/msg/detail/region_of_interest__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  msg_pkg__msg__RegionsOfInterestArray__init(message_memory);
}

void msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_fini_function(void * message_memory)
{
  msg_pkg__msg__RegionsOfInterestArray__fini(message_memory);
}

size_t msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__size_function__RegionsOfInterestArray__regions(
  const void * untyped_member)
{
  const sensor_msgs__msg__RegionOfInterest__Sequence * member =
    (const sensor_msgs__msg__RegionOfInterest__Sequence *)(untyped_member);
  return member->size;
}

const void * msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__get_const_function__RegionsOfInterestArray__regions(
  const void * untyped_member, size_t index)
{
  const sensor_msgs__msg__RegionOfInterest__Sequence * member =
    (const sensor_msgs__msg__RegionOfInterest__Sequence *)(untyped_member);
  return &member->data[index];
}

void * msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__get_function__RegionsOfInterestArray__regions(
  void * untyped_member, size_t index)
{
  sensor_msgs__msg__RegionOfInterest__Sequence * member =
    (sensor_msgs__msg__RegionOfInterest__Sequence *)(untyped_member);
  return &member->data[index];
}

void msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__fetch_function__RegionsOfInterestArray__regions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const sensor_msgs__msg__RegionOfInterest * item =
    ((const sensor_msgs__msg__RegionOfInterest *)
    msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__get_const_function__RegionsOfInterestArray__regions(untyped_member, index));
  sensor_msgs__msg__RegionOfInterest * value =
    (sensor_msgs__msg__RegionOfInterest *)(untyped_value);
  *value = *item;
}

void msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__assign_function__RegionsOfInterestArray__regions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  sensor_msgs__msg__RegionOfInterest * item =
    ((sensor_msgs__msg__RegionOfInterest *)
    msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__get_function__RegionsOfInterestArray__regions(untyped_member, index));
  const sensor_msgs__msg__RegionOfInterest * value =
    (const sensor_msgs__msg__RegionOfInterest *)(untyped_value);
  *item = *value;
}

bool msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__resize_function__RegionsOfInterestArray__regions(
  void * untyped_member, size_t size)
{
  sensor_msgs__msg__RegionOfInterest__Sequence * member =
    (sensor_msgs__msg__RegionOfInterest__Sequence *)(untyped_member);
  sensor_msgs__msg__RegionOfInterest__Sequence__fini(member);
  return sensor_msgs__msg__RegionOfInterest__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_message_member_array[1] = {
  {
    "regions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msg_pkg__msg__RegionsOfInterestArray, regions),  // bytes offset in struct
    NULL,  // default value
    msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__size_function__RegionsOfInterestArray__regions,  // size() function pointer
    msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__get_const_function__RegionsOfInterestArray__regions,  // get_const(index) function pointer
    msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__get_function__RegionsOfInterestArray__regions,  // get(index) function pointer
    msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__fetch_function__RegionsOfInterestArray__regions,  // fetch(index, &value) function pointer
    msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__assign_function__RegionsOfInterestArray__regions,  // assign(index, value) function pointer
    msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__resize_function__RegionsOfInterestArray__regions  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_message_members = {
  "msg_pkg__msg",  // message namespace
  "RegionsOfInterestArray",  // message name
  1,  // number of fields
  sizeof(msg_pkg__msg__RegionsOfInterestArray),
  msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_message_member_array,  // message members
  msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_init_function,  // function to initialize message memory (memory has to be allocated)
  msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_message_type_support_handle = {
  0,
  &msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msg_pkg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msg_pkg, msg, RegionsOfInterestArray)() {
  msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sensor_msgs, msg, RegionOfInterest)();
  if (!msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_message_type_support_handle.typesupport_identifier) {
    msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &msg_pkg__msg__RegionsOfInterestArray__rosidl_typesupport_introspection_c__RegionsOfInterestArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
