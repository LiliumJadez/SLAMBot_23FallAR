// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from msg_pkg:msg/RegionsOfInterestArray.idl
// generated code does not contain a copyright notice

#ifndef MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__TRAITS_HPP_
#define MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "msg_pkg/msg/detail/regions_of_interest_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'regions'
#include "sensor_msgs/msg/detail/region_of_interest__traits.hpp"

namespace msg_pkg
{

namespace msg
{

inline void to_flow_style_yaml(
  const RegionsOfInterestArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: regions
  {
    if (msg.regions.size() == 0) {
      out << "regions: []";
    } else {
      out << "regions: [";
      size_t pending_items = msg.regions.size();
      for (auto item : msg.regions) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RegionsOfInterestArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: regions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.regions.size() == 0) {
      out << "regions: []\n";
    } else {
      out << "regions:\n";
      for (auto item : msg.regions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RegionsOfInterestArray & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace msg_pkg

namespace rosidl_generator_traits
{

[[deprecated("use msg_pkg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const msg_pkg::msg::RegionsOfInterestArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  msg_pkg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use msg_pkg::msg::to_yaml() instead")]]
inline std::string to_yaml(const msg_pkg::msg::RegionsOfInterestArray & msg)
{
  return msg_pkg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<msg_pkg::msg::RegionsOfInterestArray>()
{
  return "msg_pkg::msg::RegionsOfInterestArray";
}

template<>
inline const char * name<msg_pkg::msg::RegionsOfInterestArray>()
{
  return "msg_pkg/msg/RegionsOfInterestArray";
}

template<>
struct has_fixed_size<msg_pkg::msg::RegionsOfInterestArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<msg_pkg::msg::RegionsOfInterestArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<msg_pkg::msg::RegionsOfInterestArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MSG_PKG__MSG__DETAIL__REGIONS_OF_INTEREST_ARRAY__TRAITS_HPP_
