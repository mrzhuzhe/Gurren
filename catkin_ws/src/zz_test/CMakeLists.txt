cmake_minimum_required(VERSION 3.0.2)
project(zz_test)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  interactive_markers
  moveit_core
  moveit_ros_planning
  moveit_ros_planning_interface
  moveit_ros_perception
  rviz_visual_tools
  moveit_visual_tools
  pluginlib
  geometric_shapes
  pcl_ros
  pcl_conversions
  rosbag
  tf2_ros
  tf2_eigen
  tf2_geometry_msgs  
  # opencv
  image_transport
  cv_bridge 
  sensor_msgs 
  nodelet 
  camera_info_manager
)

find_package(
  Eigen3 REQUIRED
  OpenCV REQUIRED
)

## Declare a catkin package
catkin_package(
  LIBRARIES
  INCLUDE_DIRS
  CATKIN_DEPENDS
    moveit_core
    moveit_visual_tools
    moveit_ros_planning_interface
    interactive_markers
    tf2_geometry_msgs
    # opencv
    image_transport 
    cv_bridge 
    sensor_msgs 
    nodelet 
    camera_info_manager  
  DEPENDS
    EIGEN3
    OpenCV
)

## Declare a cpp library
add_library(cv_camera src/capture.cpp src/driver.cpp)

# INCLUDE_DIRS
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(SYSTEM ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIRS})

# need specify dependence
target_link_libraries(cv_camera
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
  )

# moveit application
add_executable(zz_move_group_interface_tutorial src/zz_move_group_interface_tutorial.cpp)
target_link_libraries(zz_move_group_interface_tutorial 
${catkin_LIBRARIES} 
${Boost_LIBRARIES}
)
install(TARGETS zz_move_group_interface_tutorial DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

# camera application
add_executable(cv_camera_node src/cv_camera_node.cpp)
target_link_libraries(cv_camera_node 
${catkin_LIBRARIES}
cv_camera 
${Boost_LIBRARIES})
install(TARGETS cv_camera_node DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

# gear up
install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
