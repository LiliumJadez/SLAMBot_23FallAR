// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from msg_pkg:msg/RegionsOfInterestArray.idl
// generated code does not contain a copyright notice
#include "msg_pkg/msg/detail/regions_of_interest_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `regions`
#include "sensor_msgs/msg/detail/region_of_interest__functions.h"

bool
msg_pkg__msg__RegionsOfInterestArray__init(msg_pkg__msg__RegionsOfInterestArray * msg)
{
  if (!msg) {
    return false;
  }
  // regions
  if (!sensor_msgs__msg__RegionOfInterest__Sequence__init(&msg->regions, 0)) {
    msg_pkg__msg__RegionsOfInterestArray__fini(msg);
    return false;
  }
  return true;
}

void
msg_pkg__msg__RegionsOfInterestArray__fini(msg_pkg__msg__RegionsOfInterestArray * msg)
{
  if (!msg) {
    return;
  }
  // regions
  sensor_msgs__msg__RegionOfInterest__Sequence__fini(&msg->regions);
}

bool
msg_pkg__msg__RegionsOfInterestArray__are_equal(const msg_pkg__msg__RegionsOfInterestArray * lhs, const msg_pkg__msg__RegionsOfInterestArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // regions
  if (!sensor_msgs__msg__RegionOfInterest__Sequence__are_equal(
      &(lhs->regions), &(rhs->regions)))
  {
    return false;
  }
  return true;
}

bool
msg_pkg__msg__RegionsOfInterestArray__copy(
  const msg_pkg__msg__RegionsOfInterestArray * input,
  msg_pkg__msg__RegionsOfInterestArray * output)
{
  if (!input || !output) {
    return false;
  }
  // regions
  if (!sensor_msgs__msg__RegionOfInterest__Sequence__copy(
      &(input->regions), &(output->regions)))
  {
    return false;
  }
  return true;
}

msg_pkg__msg__RegionsOfInterestArray *
msg_pkg__msg__RegionsOfInterestArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msg_pkg__msg__RegionsOfInterestArray * msg = (msg_pkg__msg__RegionsOfInterestArray *)allocator.allocate(sizeof(msg_pkg__msg__RegionsOfInterestArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(msg_pkg__msg__RegionsOfInterestArray));
  bool success = msg_pkg__msg__RegionsOfInterestArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
msg_pkg__msg__RegionsOfInterestArray__destroy(msg_pkg__msg__RegionsOfInterestArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    msg_pkg__msg__RegionsOfInterestArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
msg_pkg__msg__RegionsOfInterestArray__Sequence__init(msg_pkg__msg__RegionsOfInterestArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msg_pkg__msg__RegionsOfInterestArray * data = NULL;

  if (size) {
    data = (msg_pkg__msg__RegionsOfInterestArray *)allocator.zero_allocate(size, sizeof(msg_pkg__msg__RegionsOfInterestArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = msg_pkg__msg__RegionsOfInterestArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        msg_pkg__msg__RegionsOfInterestArray__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
msg_pkg__msg__RegionsOfInterestArray__Sequence__fini(msg_pkg__msg__RegionsOfInterestArray__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      msg_pkg__msg__RegionsOfInterestArray__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

msg_pkg__msg__RegionsOfInterestArray__Sequence *
msg_pkg__msg__RegionsOfInterestArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  msg_pkg__msg__RegionsOfInterestArray__Sequence * array = (msg_pkg__msg__RegionsOfInterestArray__Sequence *)allocator.allocate(sizeof(msg_pkg__msg__RegionsOfInterestArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = msg_pkg__msg__RegionsOfInterestArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
msg_pkg__msg__RegionsOfInterestArray__Sequence__destroy(msg_pkg__msg__RegionsOfInterestArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    msg_pkg__msg__RegionsOfInterestArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
msg_pkg__msg__RegionsOfInterestArray__Sequence__are_equal(const msg_pkg__msg__RegionsOfInterestArray__Sequence * lhs, const msg_pkg__msg__RegionsOfInterestArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!msg_pkg__msg__RegionsOfInterestArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
msg_pkg__msg__RegionsOfInterestArray__Sequence__copy(
  const msg_pkg__msg__RegionsOfInterestArray__Sequence * input,
  msg_pkg__msg__RegionsOfInterestArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(msg_pkg__msg__RegionsOfInterestArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    msg_pkg__msg__RegionsOfInterestArray * data =
      (msg_pkg__msg__RegionsOfInterestArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!msg_pkg__msg__RegionsOfInterestArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          msg_pkg__msg__RegionsOfInterestArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!msg_pkg__msg__RegionsOfInterestArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
