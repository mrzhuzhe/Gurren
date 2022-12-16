# My controller test


## RoadMap

### about custom controller 

1. setup ur5 and ur5e driver [ok]
2. create a controller template [ok]
3. add robot state print in controller template
4. implement a cartesian controller
5. implement a force cartesian algorithem

### about hardware interface 
1. customer a robot hardware reffer to ur_cartesian


```

roslaunch ur_gazebo ur5_bringup.launch 

roslaunch ur_gazebo ur5e_bringup.launch 

```


## References

1. https://frankaemika.github.io/docs/franka_ros.html#writing-your-own-controller
2. http://wiki.ros.org/ros_control/Tutorials 
3. https://github.com/ros-controls/ros_control/wiki/hardware_interface hardware interface
4. https://frankaemika.github.io/docs/franka_ros.html
5. http://wiki.ros.org/rqt
6. https://github.com/fzi-forschungszentrum-informatik/cartesian_controllers maybe much better [Note]: UR did not support joint_torque_controller
    Bug in this repo
    sudo apt-get install ros-noetic-rqt-controller-manager