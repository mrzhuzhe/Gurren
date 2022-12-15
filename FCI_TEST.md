
# Franka test

> franka ros controller example for customerize ros controller
 

# build

```
rosdep install --from-paths src --ignore-src --rosdistro noetic -y --skip-keys libfranka
catkin_make -DCMAKE_BUILD_TYPE=Release -DFranka_DIR:PATH=/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/libfranka/build
source devel/setup.sh
```

# run sim controller

```
roslaunch franka_gazebo panda.launch x:=-0.5 \
    world:=$(rospack find franka_gazebo)/world/stone.sdf \
    controller:=my_test_controller \
    rviz:=true 
```

```
//  http://wiki.ros.org/rqt_reconfigure reconfigure dynamic 
rosrun rqt_reconfigure rqt_reconfigure
```

# Reffer

1. https://frankaemika.github.io/docs/franka_ros.html#writing-your-own-controller
2. http://wiki.ros.org/ros_control/Tutorials 
3. https://github.com/ros-controls/ros_control/wiki/hardware_interface hardware interface
4. https://frankaemika.github.io/docs/franka_ros.html
5. http://wiki.ros.org/rqt
6. https://github.com/fzi-forschungszentrum-informatik/cartesian_controllers maybe much better [Note]: UR did not support joint_torque_controller
    Bug in this repo
    sudo apt-get install ros-noetic-rqt-controller-manager