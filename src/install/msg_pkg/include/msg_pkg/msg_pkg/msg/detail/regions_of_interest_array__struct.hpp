// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from msg_pkg:msg/RegionsOfInterestArray.idl
// generated code does not contain a copyright notice

#ifndef MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__STRUCT_HPP_
#define MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'regions'
#include "sensor_msgs/msg/detail/region_of_interest__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__msg_pkg__msg__RegionsOfInterestArray __attribute__((deprecated))
#else
# define DEPRECATED__msg_pkg__msg__RegionsOfInterestArray __declspec(deprecated)
#endif

namespace msg_pkg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RegionsOfInterestArray_
{
  using Type = RegionsOfInterestArray_<ContainerAllocator>;

  explicit RegionsOfInterestArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit RegionsOfInterestArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _regions_type =
    std::vector<sensor_msgs::msg::RegionOfInterest_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sensor_msgs::msg::RegionOfInterest_<ContainerAllocator>>>;
  _regions_type regions;

  // setters for named parameter idiom
  Type & set__regions(
    const std::vector<sensor_msgs::msg::RegionOfInterest_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sensor_msgs::msg::RegionOfInterest_<ContainerAllocator>>> & _arg)
  {
    this->regions = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__msg_pkg__msg__RegionsOfInterestArray
    std::shared_ptr<msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__msg_pkg__msg__RegionsOfInterestArray
    std::shared_ptr<msg_pkg::msg::RegionsOfInterestArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RegionsOfInterestArray_ & other) const
  {
    if (this->regions != other.regions) {
      return false;
    }
    return true;
  }
  bool operator!=(const RegionsOfInterestArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RegionsOfInterestArray_

// alias to use template instance with default allocator
using RegionsOfInterestArray =
  msg_pkg::msg::RegionsOfInterestArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace msg_pkg

#endif  // MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__STRUCT_HPP_
