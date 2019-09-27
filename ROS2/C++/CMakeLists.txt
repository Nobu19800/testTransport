cmake_minimum_required(VERSION 3.5)
project(ros2test)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(subscriber subscriber.cpp)
ament_target_dependencies(subscriber rclcpp sensor_msgs)

add_executable(publisher publisher.cpp)
ament_target_dependencies(publisher rclcpp sensor_msgs)


install(TARGETS
  publisher
  subscriber
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
