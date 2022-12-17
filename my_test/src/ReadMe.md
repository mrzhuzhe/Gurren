# My controller test

## Run

```

roslaunch ur_gazebo ur5_bringup.launch 

roslaunch ur_gazebo ur5e_bringup.launch 

```

## Install

```

catkin build

// install controller plugins
rosdep install -i --from-path src --rosdistro noetic --ignore-src -r -y

```

## RoadMap

### about custom controller 

1. setup ur5 and ur5e driver [ok]
2. create a controller template [ok]
3. add new controller to ur [ok]
    ```
        //  Check list:
        
        /my_test/src/robots/universal_robot/fmauch_universal_robot/ur_gazebo/config/ur5e_controllers.yaml
    ```
4. add robot state print in controller template [need KDL parser]
5. implement a cartesian controller
6. implement a force cartesian algorithem

### about hardware interface 
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