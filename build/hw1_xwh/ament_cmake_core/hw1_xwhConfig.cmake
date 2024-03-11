# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_hw1_xwh_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED hw1_xwh_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(hw1_xwh_FOUND FALSE)
  elseif(NOT hw1_xwh_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(hw1_xwh_FOUND FALSE)
  endif()
  return()
endif()
set(_hw1_xwh_CONFIG_INCLUDED TRUE)

# output package information
if(NOT hw1_xwh_FIND_QUIETLY)
  message(STATUS "Found hw1_xwh: 0.0.0 (${hw1_xwh_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'hw1_xwh' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${hw1_xwh_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(hw1_xwh_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${hw1_xwh_DIR}/${_extra}")
endforeach()
