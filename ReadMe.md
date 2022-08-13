# Gurren 

> 红莲！ simulate and control ur5

 1. ros 
 2. ur robot driver
 3. moveit 
 4. gazebp

## run


```
// connect robot
roslaunch ur_robot_driver ur5_bringup.launch robot_ip:=192.168.56.101
[gazebo] roslaunch zz_test ur5_gazebo_test.launch

// make planing
roslaunch ur5_moveit_config ur5_moveit_planning_execution.launch
[with gazebo ]roslaunch zz_test ur5_moveit_planning_execution.launch sim:=true

// visualize
roslaunch zz_test moveit_rviz.launch 

// application

// draw a circle/cone
roslaunch zz_test move_group_interface_tutorial.launch 

// [WIP] test plan api
roslaunch zz_test zz_motion_planning_api_tutorial.launch

```


------------------

## setup 

```
source devel/setup.bash
```
> https://github.com/UniversalRobots/Universal_Robots_ROS_Driver/blob/master/README.md#extract-calibration-information


## simulator setup 

use vitual machine on linux 

> https://www.universal-robots.com/download/software-cb-series/simulator-linux/offline-simulator-cb3-linux-ursim-3157/

## example
```
# connect to Robot

roslaunch ur_robot_driver ur5e_bringup.launch robot_ip:=192.168.56.101

# Rviz

roslaunch ur_robot_driver example_rviz.launch


```

> https://github.com/UniversalRobots/Universal_Robots_ROS_Driver/blob/master/ur_robot_driver/doc/usage_example.md


## Moveit 

> https://ros-planning.github.io/moveit_tutorials/doc/getting_started/getting_started.html


Install 

```

# we shall add so many huge package 

warning: adding embedded git repository: ws_moveit/src/geometric_shapes
hint: You've added another git repository inside your current repository.
hint: Clones of the outer repository will not contain the contents of
hint: the embedded repository and will not know how to obtain it.
hint: If you meant to add a submodule, use:
hint: 
hint:   git submodule add <url> ws_moveit/src/geometric_shapes
hint: 
hint: If you added this path by mistake, you can remove it from the
hint: index with:
hint: 
hint:   git rm --cached ws_moveit/src/geometric_shapes
hint: 
hint: See "git help submodule" for more information.
warning: adding embedded git repository: ws_moveit/src/moveit
warning: adding embedded git repository: ws_moveit/src/moveit_msgs
warning: adding embedded git repository: ws_moveit/src/moveit_resources
warning: adding embedded git repository: ws_moveit/src/moveit_visual_tools
warning: adding embedded git repository: ws_moveit/src/rviz_visual_tools
warning: adding embedded git repository: ws_moveit/src/srdfdom


# so clone it as submodules instead
git submodule add https://github.com/ros-planning/geometric_shapes.git ws_moveit/src/geometric_shapes
git submodule add https://github.com/ros-planning/moveit.git ws_moveit/src/moveit
git submodule add https://github.com/ros-planning/moveit_msgs.git ws_moveit/src/moveit_msgs
git submodule add https://github.com/ros-planning/moveit_resources.git ws_moveit/src/moveit_resources
git submodule add https://github.com/ros-planning/moveit_visual_tools.git ws_moveit/src/moveit_visual_tools
git submodule add https://github.com/PickNikRobotics/rviz_visual_tools.git ws_moveit/src/rviz_visual_tools
git submodule add https://github.com/ros-planning/srdfdom.git ws_moveit/src/srdfdom

```

setup workspace

```
source ws_moveit/devel/setup.bash

#   echo 'source /mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/ws_moveit/devel/setup.bash' >> ~/.bashrc
```


1. planning https://ros-planning.github.io/moveit_tutorials/doc/move_group_python_interface/move_group_python_interface_tutorial.html

2. use orientation
https://stackoverflow.com/questions/60840019/practical-understanding-of-quaternions-in-ros-moveit

```
quaternion = quaternion_from_euler(60, 0, 30)

pose_goal.orientation.x = quaternion[0]
pose_goal.orientation.y = quaternion[1]
pose_goal.orientation.z = quaternion[2]
pose_goal.orientation.w = quaternion[3]

move_group.set_pose_target(pose_goal)
```


## gazebo

docs:
https://classic.gazebosim.org/tutorials?tut=components&cat=get_started

physics setting: 
https://classic.gazebosim.org/tutorials?cat=physics
there are some setting wrong in inertial friction and so on

## ROS sensor 

1. http://wiki.ros.org/Sensors drivers and so on
2. http://wiki.ros.org/Sensors/Cameras 
3. https://classic.gazebosim.org/tutorials?tut=ros_gzplugins&cat=connect_ros 
4. /rrbot/camera1/image_raw
5. gazebo cannot be definte in world only used in URDF

## references

1. https://github.com/fmauch/universal_robot
2. https://github.com/cambel/ur3/
3. https://github.com/lihuang3/ur5_ROS-Gazebo
4. https://github.com/MingshanHe/Compliant-Control-and-Application
5.  World Robot Summit 