cmake_minimum_required(VERSION 3.5)
project(oros_keyboard_controller)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include include/${PROJECT_NAME})

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(keyboard_controller_node src/main.cpp src/keyboard_controller_node.cpp)

ament_target_dependencies(keyboard_controller_node rclcpp geometry_msgs std_msgs)

install(TARGETS
keyboard_controller_node
DESTINATION lib/${PROJECT_NAME}
)

ament_package()
