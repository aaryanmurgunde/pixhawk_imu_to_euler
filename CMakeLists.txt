cmake_minimum_required(VERSION 3.0.2)
project(pixhawk_imu_to_euler)

find_package(catkin REQUIRED
COMPONENTS
roscpp
std_msgs
sensor_msgs
geometry_msgs
tf2_ros
)

catkin_package(

)
include_directories(${catkin_INCLUDE_DIRS})

add_executable(vector3_broadcaster src/vector3_broadcast.cpp)
target_link_libraries(vector3_broadcaster
  ${catkin_LIBRARIES} 
)
