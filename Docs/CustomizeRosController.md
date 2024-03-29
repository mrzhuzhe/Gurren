# Customize ROS_Controller

Customize ros contoller to implement cartesian velocity control

## Run

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

## Install 

```
cd my_test/

catkin build

// install controller plugins 
// If you add a controller plugin you need run this once more time
rosdep install -i --from-path src --rosdistro noetic --ignore-src -r -y

source devel/setup.bash
```
## RoadMap

### About custom controller 

1. setup ur5 and ur5e driver [ok]
2. create a controller template [ok]
3. add new controller to ur [ok]
    ```
        //  Check list:
        
        /my_test/src/robots/universal_robot/fmauch_universal_robot/ur_gazebo/config/ur5e_controllers.yaml
    ```
4. add robot state print in controller template [ok]
5. implement a cartesian controller [ok] but this is depend on solver in KDL libary which is heavily out of date, 
6. implement a force cartesian algorithem [trivil]
7. implement KDL libary according to ur_cartesian and so on 
    Trak ik 
    ur_cartesian
    fastik
    kdl

### About hardware interface 

1. customer a robot hardware reffer to ur_cartesian


## References

1. https://frankaemika.github.io/docs/franka_ros.html#writing-your-own-controller
2. http://wiki.ros.org/ros_control/Tutorials 
3. https://github.com/ros-controls/ros_control/wiki/hardware_interface hardware interface
4. http://wiki.ros.org/rqt
5. https://github.com/fzi-forschungszentrum-informatik/cartesian_controllers 

    maybe much better [Note]: 
    
    UR did not support joint_torque_controller

    Bug in this repo

    sudo apt-get install ros-noetic-rqt-controller-manager
6. http://wiki.ros.org/kdl KDL

