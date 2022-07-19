# Gurren 

> simulate and control ur5

 1. ros 
 2. ur robot driver
 3. moveit 

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