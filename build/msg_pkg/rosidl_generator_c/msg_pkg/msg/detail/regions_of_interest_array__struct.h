// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msg_pkg:msg/RegionsOfInterestArray.idl
// generated code does not contain a copyright notice

#ifndef MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__STRUCT_H_
#define MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'regions'
#include "sensor_msgs/msg/detail/region_of_interest__struct.h"

/// Struct defined in msg/RegionsOfInterestArray in the package msg_pkg.
typedef struct msg_pkg__msg__RegionsOfInterestArray
{
  sensor_msgs__msg__RegionOfInterest__Sequence regions;
} msg_pkg__msg__RegionsOfInterestArray;

// Struct for a sequence of msg_pkg__msg__RegionsOfInterestArray.
typedef struct msg_pkg__msg__RegionsOfInterestArray__Sequence
{
  msg_pkg__msg__RegionsOfInterestArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msg_pkg__msg__RegionsOfInterestArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__STRUCT_H_
