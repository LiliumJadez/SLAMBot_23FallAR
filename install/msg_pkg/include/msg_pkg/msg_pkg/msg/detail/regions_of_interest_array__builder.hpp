// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msg_pkg:msg/RegionsOfInterestArray.idl
// generated code does not contain a copyright notice

#ifndef MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__BUILDER_HPP_
#define MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "msg_pkg/msg/detail/regions_of_interest_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace msg_pkg
{

namespace msg
{

namespace builder
{

class Init_RegionsOfInterestArray_regions
{
public:
  Init_RegionsOfInterestArray_regions()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::msg_pkg::msg::RegionsOfInterestArray regions(::msg_pkg::msg::RegionsOfInterestArray::_regions_type arg)
  {
    msg_.regions = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msg_pkg::msg::RegionsOfInterestArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::msg_pkg::msg::RegionsOfInterestArray>()
{
  return msg_pkg::msg::builder::Init_RegionsOfInterestArray_regions();
}

}  // namespace msg_pkg

#endif  // MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__BUILDER_HPP_
