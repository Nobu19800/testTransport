
cmake_minimum_required(VERSION 2.8.12)

project(FastRTPsTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


message(STATUS "Configuring InterfaceDataTypes...")
add_executable(CameraImageTest InterfaceDataTypes.cxx InterfaceDataTypesPubSubTypes.cxx BasicDataTypePubSubTypes.cxx BasicDataType.cxx ExtendedDataTypes.cxx ExtendedDataTypesPubSubTypes.cxx InterfaceDataTypesPublisher.cxx InterfaceDataTypesSubscriber.cxx InterfaceDataTypesPubSubMain.cxx)
target_link_libraries(CameraImageTest fastcdr fastrtps)

