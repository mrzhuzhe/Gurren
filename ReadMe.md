# Gurren 

> 红莲！ simulate and control ur5


<br>

## Clone

Notice: this repo has submodule clone it with --recursive

```
# Clone all submodules
git clone --recursive git@github.com:mrzhuzhe/Gurren.git
```

------------------

<br>

## Dependences

Notice: you shall install python3-rosdep
```
# Install ROS Noetic first

# then install rosdep
sudo apt-get install python3-rosdep
sudo rosdep init
rosdep update

# this is ad hoc a bug rqt didn't auto install controller manager
sudo apt-get install ros-noetic-rqt-controller-manager
```

 1. ROS Noetic
 2. UR robot driver  Version 2022/08
 3. moveit Moveit 1 Noetic
 4. gazebo Version 11

------------------

<br>

## 1. Customize ROS_Controller

<br>

Customize ros contoller to implement cartesian velocity control

[Detail](./Docs/CustomizeRosController.md) 


> Video: <a href="https://www.bilibili.com/video/BV1Ze411c7Zd/?spm_id_from=333.999.0.0">【Sim2real】02 自定义ROS_control实现反馈控制 </a>

> Post:  <a href="https://starofus.xyz/post/ros_controller"> 【Sim2real】02 自定义ROS_control实现反馈控制 </a>

------------------

<br>

### Run

```
cd my_test/

source devel/setup.bash

// run to a position with static cartesian velocity  
roslaunch ur_gazebo ur5e_bringup.launch controllers:=cartesian_velocity_position_controller

// caertesian velocity controller 
roslaunch ur_gazebo ur5e_bringup.launch controllers:=cartesian_velocity_controller

// cartesian position 
roslaunch ur_gazebo ur5e_bringup.launch controllers:=cartesian_controller

// only test control hook
roslaunch ur_gazebo ur5e_bringup.launch controllers:=test_controller

// run it with rqt topic publisher 
```
------------------

<br>

### Install 

```
cd my_test/

catkin build

// install controller plugins 
// If you add a controller plugin you need run this once more time
rosdep install -i --from-path src --rosdistro noetic --ignore-src -r -y

source devel/setup.bash
```

<br>

------------------

<br>





## 2. MOVEIT GAZEBO setup demo

<br>

Setup ROS gazebo enviroment and moveit to move robot follow a trajectory base on 3d model convexhull 

[Detail](Docs/MoveItGazeboDemo.md)

<br>

> Video: <a href="https://www.bilibili.com/video/BV1KY4y1F73s/?spm_id_from=333.999.0.0">【Sim2real】01：ROS ， Moveit ， Gazebo 和凸包 </a>

> Post:  <a href="https://starofus.xyz/post/Sim2real_foundation">【Sim2real】01：ROS ， Moveit ， Gazebo 和凸包 </a>

------------------

<br>


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

------------------

<br>

### Install 


```

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

------------------

<br>


