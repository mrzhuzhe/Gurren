/*********************************************************************
 way points
 XC924:
 [
 [141.7283586   23.37476801  -2.5312582 ]
 [148.32357805  62.06995544 -16.99646102]
 [156.31206129  82.81996499 -25.11564635]
 [165.32296036  99.39501807 -31.94494157]
 [174.5926348  112.70585208 -37.76189701]
 [184.28402943 124.08254742 -43.09098257]
 [193.2839186  132.98302989 -47.54528995]
 [200.71756702 139.39296791 -50.91325777]
 [206.93604009 144.21216159 -53.53679733]
 [212.12789027 147.90687012 -55.58909296]
 [218.25905153 151.91934477 -58.00627907]
 [226.52083334 156.75794159 -61.28208229]
 [234.13574469 160.68365643 -64.17301788]
 [238.09946373 162.54727092 -65.46408384]
 [241.63190381 164.11916515 -66.55903408]
 [246.03767845 165.96391188 -68.00171686]
 [251.20596528 167.96139586 -69.73637004]
 [257.57248207 170.17436855 -71.92911076]
 [264.07968499 172.15916675 -74.14589448]
 [269.78490478 173.67906434 -76.01936324]
 [274.51303725 174.79185482 -77.49294939]
 [278.4283619  175.61934829 -78.63953325]
 [281.95430736 176.29615727 -79.62900044]
 [288.29429588 177.33831188 -81.7014383 ]
 [295.98123895 178.28355523 -84.27800438]
 [302.85647615 178.83618722 -86.53090407]
 [307.38486318 179.05663333 -87.96322679]
 [311.95508195 179.15869388 -89.40987434]]

 *********************************************************************/


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
    {131.52773071,  15.64555205,  -0.43032822},
    {133.1677714,   37.6218774,   -8.2831536 },
    {135.99597393,  52.25397438, -13.59613984},
    {140.11821575,  66.42051797, -18.8522062 },
    {145.56297454,  80.24300916, -24.14729109},
    {152.22150667,  93.43616021, -29.41250812},
    {160.0028547,  105.87677005, -34.63785995},
    {165.0068256,  112.74540415, -37.59234425},
    {169.69744221, 118.55586226, -40.15283932},
    {176.04770404, 125.66265673, -43.41189818},
    {182.8943336,  132.4929766,  -46.72470837},
    {190.07882609, 138.87844057, -50.01494105},
    {197.65857336, 144.87107128, -53.32445744},
    {203.6686641,  149.15069118, -55.82593744},
    {209.86664786, 153.159407,   -58.32868148},
    {217.56881008, 157.63510643, -61.34977763},
    {225.38005364, 161.64338617, -64.32179369},
    {233.43898751, 165.26212267, -67.31486085},
    {237.93588821, 167.07382644, -68.86638649},
    {244.34346601, 169.39914406, -71.16986413},
    {252.76144716, 172.02694809, -74.15691788},
    {261.25067136, 174.20032964, -77.12260501},
    {261.72200693, 174.30841613, -76.99712456},
    {266.80528869, 175.40138652, -78.67320359},
    {273.11519759, 176.5472708,  -80.74113069},
    {279.47131612, 177.46583222, -82.81243603},
    {285.83793631, 178.1524604,  -84.87663768},
    {292.88053435, 178.64015188, -87.27514473},
    {295.57515795, 178.74975441, -88.00691118},
    {299.03246709, 178.84171445, -88.94587661},
    {302.47700069, 178.87701925, -89.87967904}
  };
  // ar35 end

  int _cur = 26;  // 6 - 26
  ROS_INFO_STREAM("_waypoints[_cur]" << _waypoints[_cur][0] << " " << _waypoints[_cur][1] << " " << _waypoints[_cur][2] << "\n");
  double radius = _waypoints[_cur][0] * 0.001, degs = 90 + _waypoints[_cur][2], tableHeight = 0.08, waypoint_z = _waypoints[_cur][1]* 0.001;
  target_pose1.position.x = origin_radius + offset; // 0.399791
  target_pose1.position.y = origin_radius + offset;
  target_pose1.position.z = tableHeight + waypoint_z + 0.1;
  
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
  geometry_msgs::Pose target_pose3 = target_pose1;

  // zz test
  // [BUG] initial point shall not been added to waypoints https://answers.ros.org/question/253004/moveit-problem-error-trajectory-message-contains-waypoints-that-are-not-strictly-increasing-in-time/
  waypoints.push_back(target_pose1);


  
  int theta = 100; // only 350 degree
  for (; theta < 450; ++theta)
    {
        
    //double r=0, p=3.14*2*(180+degs)/360, y=3.14*2*(-theta-90)/360;  // Rotate the previous pose by 180* about X
    double r=0, p=M_PI*2*(180+degs)/360, y=M_PI*2*(-theta-90)/360;  // Rotate the previous pose by 180* about X
    q_rot.setRPY(r, p, y);
    target_pose3.orientation.x = q_rot.getX();
    target_pose3.orientation.y = q_rot.getY();
    target_pose3.orientation.z = q_rot.getZ();
    target_pose3.orientation.w = q_rot.getW();
    
    target_pose3.position.y = target_pose1.position.y + radius * cos(3.14*2*theta/360);
    target_pose3.position.x = target_pose1.position.x + radius * sin(3.14*2*theta/360);
    // avoid joint limit
    target_pose3.position.z = target_pose1.position.z - 0.1;
    waypoints.push_back(target_pose3);

    }
  // [ERROR] [1659608954.356257928]: Trajectory message contains waypoints that are not strictly increasing in time
  // return to a different point
  target_pose1.position.z += 0.2;
  waypoints.push_back(target_pose1);

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
