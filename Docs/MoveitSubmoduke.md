# Moveit test (legacy)

> Now deleted

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
<br>

------------------

<br>
<br>