cmake_minimum_required(VERSION 3.8)
project(navigation_components)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(action_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "action/Navigate.action"
  DEPENDENCIES action_msgs
)

add_library(nav_server_component SHARED src/nav_server_component.cpp)
target_include_directories(nav_server_component PRIVATE include)
ament_target_dependencies(nav_server_component
  rclcpp rclcpp_components rclcpp_action geometry_msgs tf2 tf2_ros)
rclcpp_components_register_node(nav_server_component
  PLUGIN "NavServer"
  EXECUTABLE nav_server_node)

rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(nav_server_component "${cpp_typesupport_target}")

add_library(nav_client_component SHARED src/nav_client_component.cpp)
target_include_directories(nav_client_component PRIVATE include)
ament_target_dependencies(nav_client_component
  rclcpp rclcpp_components rclcpp_action geometry_msgs std_msgs)
rclcpp_components_register_node(nav_client_component
  PLUGIN "NavClient"
  EXECUTABLE nav_client_node)

target_link_libraries(nav_client_component "${cpp_typesupport_target}")

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
  nav_server_component
  nav_client_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(PROGRAMS
  scripts/ui_node.py
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

ament_package()