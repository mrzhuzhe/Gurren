#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/fmauch_universal_robot/ur_kinematics"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/install/lib/python3/dist-packages:/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/build" \
    "/usr/bin/python3" \
    "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/src/fmauch_universal_robot/ur_kinematics/setup.py" \
     \
    build --build-base "/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/build/fmauch_universal_robot/ur_kinematics" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/install" --install-scripts="/mnt/e28833eb-0c99-4fe2-802a-09fa58d9c9f5/code/Gurren/catkin_ws/install/bin"
