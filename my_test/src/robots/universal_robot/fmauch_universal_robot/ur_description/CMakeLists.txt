cmake_minimum_required(VERSION 2.8.3)
project(ur_description)

find_package(catkin REQUIRED)

catkin_package()

if (CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)  
  roslaunch_add_file_check(tests/roslaunch_test_ur5e.xml)
  roslaunch_add_file_check(tests/roslaunch_test_ur5.xml)
endif()

install(DIRECTORY cfg config launch meshes urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
