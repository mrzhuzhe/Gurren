# MOVEIT GAZEBO setup

Setup ROS gazebo enviroment and moveit to move robot follow a trajectory base on 3d model convexhull 

> Video <a href="https://www.bilibili.com/video/BV1KY4y1F73s/?spm_id_from=333.999.0.0">【Sim2real】01：ROS ， Moveit ， Gazebo 和凸包
</a>

### Dependence 

 1. ROS Noetic
 2. UR robot driver  Version 2022/08
 3. moveit Moveit 1 Noetic
 4. gazebo Version 11

### Run

```
cd catkin_ws/

// connect robot
roslaunch ur_robot_driver ur5_bringup.launch robot_ip:=192.168.130.105
[gazebo] roslaunch zz_test ur5_gazebo_test.launch

// make planing
roslaunch zz_test ur5_moveit_planning_execution.launch
[with gazebo ]roslaunch zz_test ur5_moveit_planning_execution.launch sim:=true

// visualize
roslaunch zz_test moveit_rviz.launch 

// application

// draw a circle/cone
roslaunch zz_test move_group_interface_tutorial.launch 

```
<br>

------------------

<br>
<br>

### Install 


```
# Install ROS Noetic first

# then install rosdep
sudo apt-get install python3-rosdep
sudo rosdep init
rosdep update


# then clone all submodules
git clone --recursive git@github.com:mrzhuzhe/Gurren.git

# install dependencies
$ sudo apt update -qq
$ rosdep update
$ rosdep install --from-paths src --ignore-src -y

# build the workspace
$ cd catkin_ws
$ catkin_make

# activate the workspace (ie: source it)
$ source devel/setup.bash


```
<br>

------------------

<br>
<br>


### Applications

Robot applications features will be develop in other reposs

1. calculate way point from CAD https://github.com/mrzhuzhe/Patrick/tree/main/geo/contour

<br>

------------------

<br>
<br>

### Setup 

```
source devel/setup.bash
```

<br>

------------------

<br>
<br>

### UR Simulator setup 

use vitual machine on linux 

1. https://github.com/UniversalRobots/Universal_Robots_ROS_Driver/blob/master/README.md#extract-calibration-information
2.  https://www.universal-robots.com/download/software-cb-series/simulator-linux/offline-simulator-cb3-linux-ursim-3157/
3. https://github.com/UniversalRobots/Universal_Robots_ROS_Driver/blob/master/ur_robot_driver/doc/usage_example.md


```
# connect to Robot

roslaunch ur_robot_driver ur5e_bringup.launch robot_ip:=192.168.56.101

# Rviz

roslaunch ur_robot_driver example_rviz.launch


```


<br>

------------------

<br>
<br>



### gazebo


Docs:

https://classic.gazebosim.org/tutorials?tut=components&cat=get_started

Physics setting: 

https://classic.gazebosim.org/tutorials?cat=physics
there are some setting wrong in inertial friction and so on

<br>

------------------

<br>
<br>

### ROS sensor 

use custom camera

1. http://wiki.ros.org/Sensors drivers and so on
2. http://wiki.ros.org/Sensors/Cameras 
3. https://classic.gazebosim.org/tutorials?tut=ros_gzplugins&cat=connect_ros 
4. /rrbot/camera1/image_raw
5. gazebo cannot be definte in world only used in URDF

<br>

------------------

<br>
<br>

### References

1. https://github.com/fmauch/universal_robot
2. https://github.com/cambel/ur3/
3. https://github.com/lihuang3/ur5_ROS-Gazebo
4. https://github.com/MingshanHe/Compliant-Control-and-Application
5.  World Robot Summit 

<br>

------------------

<br>
<br>