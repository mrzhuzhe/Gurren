#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>


#include <tf2_geometry_msgs/tf2_geometry_msgs.h>





// The circle constant tau = 2*pi. One tau is one rotation in radians.
const double tau = 2 * M_PI;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;

  // ROS spinning must be running for the MoveGroupInterface to get information
  // about the robot's state. One way to do this is to start an AsyncSpinner
  // beforehand.
  ros::AsyncSpinner spinner(1);
  spinner.start();

  // BEGIN_TUTORIAL
  //
  // Setup
  // ^^^^^
  //
  // MoveIt operates on sets of joints called "planning groups" and stores them in an object called
  // the `JointModelGroup`. Throughout MoveIt the terms "planning group" and "joint model group"
  // are used interchangeably.
  static const std::string PLANNING_GROUP = "manipulator";

  // The :planning_interface:`MoveGroupInterface` class can be easily
  // setup using just the name of the planning group you would like to control and plan for.
  moveit::planning_interface::MoveGroupInterface move_group_interface(PLANNING_GROUP);

  // We will use the :planning_interface:`PlanningSceneInterface`
  // class to add and remove collision objects in our "virtual world" scene
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  // Raw pointers are frequently used to refer to the planning group for improved performance.
  const moveit::core::JointModelGroup* joint_model_group =
      move_group_interface.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  // Visualization
  // ^^^^^^^^^^^^^
  //
  // The package MoveItVisualTools provides many capabilities for visualizing objects, robots,
  // and trajectories in RViz as well as debugging tools such as step-by-step introspection of a script.
  namespace rvt = rviz_visual_tools;
  moveit_visual_tools::MoveItVisualTools visual_tools("base_link");
  visual_tools.deleteAllMarkers();

  // Remote control is an introspection tool that allows users to step through a high level script
  // via buttons and keyboard shortcuts in RViz
  visual_tools.loadRemoteControl();

  // RViz provides many types of markers, in this demo we will use text, cylinders, and spheres
  Eigen::Isometry3d text_pose = Eigen::Isometry3d::Identity();
  text_pose.translation().z() = 1.0;
  visual_tools.publishText(text_pose, "MoveGroupInterface Demo", rvt::WHITE, rvt::XLARGE);

  // Batch publishing is used to reduce the number of messages being sent to RViz for large visualizations
  visual_tools.trigger();

  // Getting Basic Information
  // ^^^^^^^^^^^^^^^^^^^^^^^^^
  //
  // We can print the name of the reference frame for this robot.
  ROS_INFO_NAMED("tutorial", "Planning frame: %s", move_group_interface.getPlanningFrame().c_str());

  // We can also print the name of the end-effector link for this group.
  ROS_INFO_NAMED("tutorial", "End effector link: %s", move_group_interface.getEndEffectorLink().c_str());

  // We can get a list of all the groups in the robot:
  ROS_INFO_NAMED("tutorial", "Available Planning Groups:");
  std::copy(move_group_interface.getJointModelGroupNames().begin(),
            move_group_interface.getJointModelGroupNames().end(), std::ostream_iterator<std::string>(std::cout, ", "));

  


  // get robot state start 
  const std::vector<std::string>& joint_names = joint_model_group->getVariableNames();

  moveit::core::RobotStatePtr kinematic_state(new moveit::core::RobotState(*move_group_interface.getCurrentState()));

  std::vector<double> joint_values;

  kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);

  for (std::size_t i = 0; i < joint_names.size(); ++i)
  {
    ROS_INFO("Joint %s: %f", joint_names[i].c_str(), joint_values[i]);
  }

  const Eigen::Isometry3d& end_effector_state = kinematic_state->getGlobalLinkTransform("tool0");

  /* Print end-effector pose. Remember that this is in the model frame */
  ROS_INFO_STREAM("Translation: \n" << end_effector_state.translation() << "\n");
  ROS_INFO_STREAM("Rotation: \n" << end_effector_state.rotation() << "\n");
  // get robot state end

  // add constraint
  moveit_msgs::CollisionObject collision_object;
  collision_object.header.frame_id = move_group_interface.getPlanningFrame();

  // The id of the object is used to identify it.
  collision_object.id = "box1";

  // Define a box to add to the world.
  shape_msgs::SolidPrimitive primitive;
  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  primitive.dimensions[primitive.BOX_X] = 1;
  primitive.dimensions[primitive.BOX_Y] = 1;
  primitive.dimensions[primitive.BOX_Z] = 0.04;

  // Define a pose for the box (specified relative to frame_id)
  geometry_msgs::Pose box_pose;
  box_pose.orientation.w = 1.0;
  box_pose.position.x = 0.0;
  box_pose.position.y = 0.0;
  box_pose.position.z = -0.03;

  collision_object.primitives.push_back(primitive);
  collision_object.primitive_poses.push_back(box_pose);
  collision_object.operation = collision_object.ADD;

  std::vector<moveit_msgs::CollisionObject> collision_objects;
  collision_objects.push_back(collision_object);

  // Now, let's add the collision object into the world
  // (using a vector that could contain additional objects)
  ROS_INFO_NAMED("tutorial", "Add an object into the world");
  planning_scene_interface.addCollisionObjects(collision_objects);

  /*
  moveit_msgs::CollisionObject object_to_attach;
  object_to_attach.id = "cylinder1";

  shape_msgs::SolidPrimitive cylinder_primitive;
  cylinder_primitive.type = primitive.CYLINDER;
  cylinder_primitive.dimensions.resize(2);
  cylinder_primitive.dimensions[primitive.CYLINDER_HEIGHT] = 0.15;
  cylinder_primitive.dimensions[primitive.CYLINDER_RADIUS] = 0.02;

  // We define the frame/pose for this cylinder so that it appears in the gripper
  object_to_attach.header.frame_id = move_group_interface.getEndEffectorLink();
  geometry_msgs::Pose grab_pose;
  grab_pose.orientation.w = 1.0;
  grab_pose.position.z = 0.076;  // 0.001 for seperate

  // First, we add the object to the world (without using a vector)
  object_to_attach.primitives.push_back(cylinder_primitive);
  object_to_attach.primitive_poses.push_back(grab_pose);
  object_to_attach.operation = object_to_attach.ADD;
  planning_scene_interface.applyCollisionObject(object_to_attach);

  move_group_interface.attachObject(object_to_attach.id, "tool0");
  */


  // Start the demo
  // ^^^^^^^^^^^^^^^^^^^^^^^^^
  visual_tools.prompt("Press 456456 'next' in the RvizVisualToolsGui window to start the demo");

  tf2::Quaternion q_rot;
  //double r=0, p=3.14, y=0;  // Rotate the previous pose by 180* about X
  double r=0, p=-M_PI, y=0;  // Rotate the previous pose by 180* about X
  q_rot.setRPY(r, p, y);


  geometry_msgs::Pose target_pose1;
  
  target_pose1.orientation.x = q_rot.getX();
  target_pose1.orientation.y = q_rot.getY();
  target_pose1.orientation.z = q_rot.getZ();
  target_pose1.orientation.w = q_rot.getW();
  
  //target_pose1.orientation.w = 1;
  //241.63190381 164.11916515 -66.55903408
  // max 311.95508195 179.15869388 -89.40987434
  
  // ar35 start
  double origin_radius = 0.316481, offset = 0.18 - 0.05 - 0.09338/2;
  double _waypoints[][3] = {
    {111.52829481 , 15.79576352 , -0.43032822},
    {113.37640759 , 40.50318239 , -8.2831536 ,},
    {116.55643712 , 56.95550696 ,-13.59613984},
    {121.19111118 , 72.88308036 ,-18.8522062 ,},
    {127.31303781 , 88.42468439 ,-24.14729109},
    {134.79937422 ,103.2580389 , -29.41250812},
    {143.54763533 ,117.24452073 ,-34.63785995},
    {149.15940235 ,124.94619003 ,-37.59234425},
    {154.41090118 ,131.45243789 ,-40.15283932},
    {161.51906458 ,139.4074243 , -43.41189818},
    {169.18424475 ,147.05434548 ,-46.72470837},
    {177.22706957 ,154.20268131 ,-50.01494105},
    {185.71291648 ,160.91168479 ,-53.32445744},
    {192.43448597 ,165.69739 ,   -55.82593744},
    {199.36573424 ,170.18088793 ,-58.32868148},
    {207.97958475 ,175.18636729 ,-61.34977763},
    {216.71372746 ,179.66822432 ,-64.32179369},
    {225.72565251 ,183.7148857 , -67.31486085},
    {230.72500664 ,185.72866997 ,-68.86638649},
    {237.88819481 ,188.3287366 , -71.16986413},
    {247.30137345 ,191.26720783 ,-74.15691788},
    {256.79336088 ,193.6973136 , -77.12260501},
    {257.22200786 ,193.79559161 ,-76.99712456},
    {262.87719384 ,195.01184472 ,-78.67320359},
    {269.8972906 , 196.28670024 ,-80.74113069},
    {276.96895827 ,197.30866985 ,-82.81243603},
    {284.05192781 ,198.07255512 ,-84.87663768},
    {291.92973893 ,198.6175388 , -87.27514473},
    {294.87957901 ,198.737655 ,  -88.00691118},
    {298.66452937 ,198.83832971 ,-88.94587661},
    {302.43500079 ,198.87697515 ,-89.87967904}
 };
  // ar35 end

  int _cur = 5;  // 6 - end
  int _len = sizeof(_waypoints) / sizeof(_waypoints[0]);
  double tableHeight = 0.08, radius, degs, waypoint_z;   
  target_pose1.position.x = origin_radius + offset; // 0.399791
  target_pose1.position.y = origin_radius + offset;
  
  /*
  move_group_interface.setPoseTarget(target_pose1);

  //  ROS_INFO_NAMED("tutorial", "x: " << q_rot.getX() << " y: " << q_rot.getY() << " z: " << q_rot.getZ() << " w: " << q_rot.getW());
  ROS_INFO_NAMED("tutorial", "x: %f y: %f z: %f w: %f", q_rot.getX(), q_rot.getY(), q_rot.getZ(), q_rot.getW());

  // Now, we call the planner to compute the plan and visualize it.
  // Note that we are just planning, not asking move_group_interface
  // to actually move the robot.
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;

  
  bool success = (move_group_interface.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  
  ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");
  

  // Visualizing plans
  // ^^^^^^^^^^^^^^^^^
  // We can also visualize the plan as a line with markers in RViz.
  ROS_INFO_NAMED("tutorial", "Visualizing plan 1 as trajectory line");
  visual_tools.publishAxisLabeled(target_pose1, "pose1");
  visual_tools.publishText(text_pose, "Pose Goal with Move", rvt::WHITE, rvt::XLARGE);
  visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
  visual_tools.trigger();
  visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");
  */
  // Finally, to execute the trajectory stored in my_plan, you could use the following method call:
  // Note that this can lead to problems if the robot moved in the meanwhile.
  // move_group_interface.execute(my_plan);

  // Moving to a pose goal
  // ^^^^^^^^^^^^^^^^^^^^^
  //
  // If you do not want to inspect the planned trajectory,
  // the following is a more robust combination of the two-step plan+execute pattern shown above
  // and should be preferred. Note that the pose goal we had set earlier is still active,
  // so the robot will try to move to that goal.

  //move_group_interface.move();

  //  ROS_INFO_NAMED("tutorial", "x: " << q_rot.getX() << " y: " << q_rot.getY() << " z: " << q_rot.getZ() << " w: " << q_rot.getW());
  ROS_INFO_NAMED("tutorial", "x: %f y: %f z: %f w: %f", q_rot.getX(), q_rot.getY(), q_rot.getZ(), q_rot.getW());

  std::vector<geometry_msgs::Pose> waypoints;
  //waypoints.push_back(start_pose2);
  //waypoints.push_back(target_pose1);

  //geometry_msgs::Pose target_pose3 = start_pose2;


  
  // zz test
  // [BUG] initial point shall not been added to waypoints https://answers.ros.org/question/253004/moveit-problem-error-trajectory-message-contains-waypoints-that-are-not-strictly-increasing-in-time/
  geometry_msgs::Pose recover_pose = target_pose1;
  geometry_msgs::Pose running_pose = target_pose1;

  for (int i = _cur; i < _len; ++i){

    ROS_INFO_STREAM("_waypoints[_cur]" << _waypoints[i][0] << " " << _waypoints[i][1] << " " << _waypoints[i][2] << "\n");
    radius = _waypoints[i][0] * 0.001, degs = 90 + _waypoints[i][2], waypoint_z = _waypoints[i][1]* 0.001;        
    
    recover_pose.position.z = tableHeight + waypoint_z + 0.1;
    waypoints.push_back(recover_pose);
        
    int theta = 100; // only 350 degree
    for (; theta < 450; ++theta)
      {
          
      //double r=0, p=3.14*2*(180+degs)/360, y=3.14*2*(-theta-90)/360;  // Rotate the previous pose by 180* about X
      double r=0, p=M_PI*2*(180+degs)/360, y=M_PI*2*(-theta-90)/360;  // Rotate the previous pose by 180* about X
      q_rot.setRPY(r, p, y);
      running_pose.orientation.x = q_rot.getX();
      running_pose.orientation.y = q_rot.getY();
      running_pose.orientation.z = q_rot.getZ();
      running_pose.orientation.w = q_rot.getW();
      
      running_pose.position.y = recover_pose.position.y + radius * cos(3.14*2*theta/360);
      running_pose.position.x = recover_pose.position.x + radius * sin(3.14*2*theta/360);    
      running_pose.position.z = tableHeight + waypoint_z;
      waypoints.push_back(running_pose);

      }
    
    // back
    recover_pose.position.z = tableHeight + waypoint_z + 0.09;
    waypoints.push_back(recover_pose);

  }

  // recover to higher
  recover_pose.position.z += 0.1;
  waypoints.push_back(recover_pose);


    

  // We want the Cartesian path to be interpolated at a resolution of 1 cm
  // which is why we will specify 0.01 as the max step in Cartesian
  // translation.  We will specify the jump threshold as 0.0, effectively disabling it.
  // Warning - disabling the jump threshold while operating real hardware can cause
  // large unpredictable motions of redundant joints and could be a safety issue
  moveit_msgs::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;
  double fraction = move_group_interface.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
  ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (Cartesian path) (%.2f%% achieved)", fraction * 100.0);

  // Visualize the plan in RViz
  visual_tools.deleteAllMarkers();
  visual_tools.publishText(text_pose, "Cartesian Path", rvt::WHITE, rvt::XLARGE);
  visual_tools.publishPath(waypoints, rvt::LIME_GREEN, rvt::SMALL);

  ROS_INFO_NAMED("tutorial", "waypoint %ld", waypoints.size());


  //for (std::size_t i = 0; i < waypoints.size(); ++i)
  //  visual_tools.publishAxisLabeled(waypoints[i], "pt" + std::to_string(i), rvt::SMALL);
  visual_tools.trigger();
  visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");

  move_group_interface.execute(trajectory);

  //target_pose1.position.z = 0.4;
  //move_group_interface.setPoseTarget(target_pose1);
  //move_group_interface.move();


  ros::shutdown();
  return 0;
}
