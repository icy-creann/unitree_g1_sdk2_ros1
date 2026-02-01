# 查找ROS包
find_package(catkin REQUIRED COMPONENTS
  tf
  roscpp
  sensor_msgs
  geometry_msgs
)

# 包含ROS头文件路径
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(g1_loco_client g1_loco_client.cpp)
target_link_libraries(g1_loco_client unitree_sdk2)

add_executable(g1_move_sub g1_move_sub.cpp)
target_link_libraries(g1_move_sub ${catkin_LIBRARIES} unitree_sdk2)
