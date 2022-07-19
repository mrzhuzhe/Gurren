# Install script for directory: /mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur_dashboard_msgs/msg" TYPE FILE FILES
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/msg/ProgramState.msg"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/msg/RobotMode.msg"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/msg/SafetyMode.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur_dashboard_msgs/srv" TYPE FILE FILES
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/AddToLog.srv"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/GetLoadedProgram.srv"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/GetProgramState.srv"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/GetRobotMode.srv"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/GetSafetyMode.srv"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/IsProgramRunning.srv"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/IsProgramSaved.srv"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/Load.srv"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/Popup.srv"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/srv/RawRequest.srv"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur_dashboard_msgs/action" TYPE FILE FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/action/SetMode.action")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur_dashboard_msgs/msg" TYPE FILE FILES
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/ur_dashboard_msgs/msg/SetModeAction.msg"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/ur_dashboard_msgs/msg/SetModeActionGoal.msg"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/ur_dashboard_msgs/msg/SetModeActionResult.msg"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/ur_dashboard_msgs/msg/SetModeActionFeedback.msg"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/ur_dashboard_msgs/msg/SetModeGoal.msg"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/ur_dashboard_msgs/msg/SetModeResult.msg"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/ur_dashboard_msgs/msg/SetModeFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur_dashboard_msgs/cmake" TYPE FILE FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/build/Universal_Robots_ROS_Driver/ur_dashboard_msgs/catkin_generated/installspace/ur_dashboard_msgs-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/include/ur_dashboard_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/roseus/ros/ur_dashboard_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/common-lisp/ros/ur_dashboard_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/share/gennodejs/ros/ur_dashboard_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/lib/python3/dist-packages/ur_dashboard_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/devel/lib/python3/dist-packages/ur_dashboard_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/build/Universal_Robots_ROS_Driver/ur_dashboard_msgs/catkin_generated/installspace/ur_dashboard_msgs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur_dashboard_msgs/cmake" TYPE FILE FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/build/Universal_Robots_ROS_Driver/ur_dashboard_msgs/catkin_generated/installspace/ur_dashboard_msgs-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur_dashboard_msgs/cmake" TYPE FILE FILES
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/build/Universal_Robots_ROS_Driver/ur_dashboard_msgs/catkin_generated/installspace/ur_dashboard_msgsConfig.cmake"
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/build/Universal_Robots_ROS_Driver/ur_dashboard_msgs/catkin_generated/installspace/ur_dashboard_msgsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ur_dashboard_msgs" TYPE FILE FILES "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/Universal_Robots_ROS_Driver/ur_dashboard_msgs/package.xml")
endif()

