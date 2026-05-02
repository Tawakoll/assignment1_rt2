// generated from rosidl_generator_cpp/resource/rosidl_generator_cpp__visibility_control.hpp.in
// generated code does not contain a copyright notice

#ifndef NAVIGATION_COMPONENTS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
#define NAVIGATION_COMPONENTS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_CPP_EXPORT_navigation_components __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_CPP_IMPORT_navigation_components __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_CPP_EXPORT_navigation_components __declspec(dllexport)
    #define ROSIDL_GENERATOR_CPP_IMPORT_navigation_components __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_CPP_BUILDING_DLL_navigation_components
    #define ROSIDL_GENERATOR_CPP_PUBLIC_navigation_components ROSIDL_GENERATOR_CPP_EXPORT_navigation_components
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_navigation_components ROSIDL_GENERATOR_CPP_IMPORT_navigation_components
  #endif
#else
  #define ROSIDL_GENERATOR_CPP_EXPORT_navigation_components __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_CPP_IMPORT_navigation_components
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_CPP_PUBLIC_navigation_components __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_navigation_components
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // NAVIGATION_COMPONENTS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
