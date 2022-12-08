
# Franka test

# build
rosdep install --from-paths src --ignore-src --rosdistro noetic -y --skip-keys libfranka
catkin_make -DCMAKE_BUILD_TYPE=Release -DFranka_DIR:PATH=/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/libfranka/build
source devel/setup.sh