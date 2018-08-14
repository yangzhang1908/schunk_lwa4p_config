/* Author:Yang Zhang */

#include "ros/ros.h"
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>
#include <Eigen/Dense>

#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>


#include <cstdlib>
#include <iostream>
#include <ctime>


using namespace std;
  /*robot_model_loader::RobotModelLoader robot_model_loader("lwa4p");
  robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
  ROS_INFO("Model frame: %s", kinematic_model->getModelFrame().c_str()); 
  robot_state::RobotStatePtr kinematic_state(new robot_state::RobotState(kinematic_model));
  kinematic_state->setToDefaultValues();
  const robot_state::JointModelGroup* joint_model_group = kinematic_model->getJointModelGroup("arm");

  const std::vector<std::string>& joint_names = joint_model_group->getVariableNames(); */

  float fl1 = 0;
  float fl2 = 0;
  float fl3 = 0;
  float fl4 = 0;
  bool success2;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "move_group_interface_demo");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  static const std::string PLANNING_GROUP = "arm";
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  const robot_state::JointModelGroup* joint_model_group =
  move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
  moveit::core::RobotStatePtr current_state = move_group.getCurrentState();
  namespace rvt = rviz_visual_tools;
  moveit_visual_tools::MoveItVisualTools visual_tools("arm_1_link");
  visual_tools.deleteAllMarkers();
  visual_tools.loadRemoteControl();

  Eigen::Affine3d text_pose = Eigen::Affine3d::Identity();
  text_pose.translation().z() = 1.75;
  visual_tools.publishText(text_pose, "MoveGroupInterface Demo", rvt::WHITE, rvt::XLARGE);
  visual_tools.trigger();

  /*ROS_INFO_NAMED("demo", "Reference frame: %s", move_group.getPlanningFrame().c_str());
  ROS_INFO_NAMED("demo", "End effector link: %s", move_group.getEndEffectorLink().c_str()); */

  visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to start the demo");

  // Planning to a Pose goal
  geometry_msgs::PoseStamped current_pose;
  //current_pose = (*move_group.getCurrentPose("arm_6_link"));
  geometry_msgs::Pose target_pose;
  target_pose.orientation.w = 1.0;
  target_pose.position.x = 0.28;
  target_pose.position.y = 0.2;
  target_pose.position.z = 0.5;
  move_group.setPoseTarget(target_pose);
  //move_group.setRandomTarget(geometry_msgs::Pose& target_pose);

  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  move_group.execute(my_plan);
  bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  success2 = (move_group.execute(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  std::cout << endl << "success execution?:=" << success2 << endl;
  ROS_INFO_NAMED("demo", "Visualizing plan  (pose goal) %s", success ? "" : "FAILED");
  std::cout <<"success execution?:=" << success2 << endl;
 
  // Visualizing plans
  /*ROS_INFO_NAMED("demo", "Visualizing plan  as trajectory line");
  visual_tools.publishAxisLabeled(target_pose, "pose");
  visual_tools.publishText(text_pose, "Pose Goal", rvt::WHITE, rvt::XLARGE);
  visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
  visual_tools.trigger(); */
  visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo"); 


  int i = 1;
  
 while (ros::ok() && i <=10)
 {  
  srand((unsigned)time(NULL)); 
  fl1 = float(rand()-2147483647/2)/4294967295/5;
  fl2 = float(rand()-2147483647/2)/4294967295/5;
  fl3 = float(rand()-2147483647/2)/4294967295/5;
  fl4 = float(rand()-2147483647/2)/4294967295/5;

  std::cout << endl << "i = ";
  std::cout << i << endl;
  std::cout <<" random float" <<"[";
  std::cout << fl1 <<", " << fl2 <<", "<< fl3 <<", " << fl4<< "]" << endl << endl;
  
  
  // Moving to a pose goal
  move_group.setStartState(*move_group.getCurrentState());
  target_pose.orientation.w = target_pose.orientation.w + fl1;
  target_pose.position.x = target_pose.position.x + fl2;
  target_pose.position.y = target_pose.position.y + fl3;
  target_pose.position.z = target_pose.position.z + fl4;
  move_group.setPoseTarget(target_pose);
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  move_group.execute(my_plan);
  bool success_ = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  success2 = (move_group.execute(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  //move_group.execute(my_plan);
  ROS_INFO_NAMED("demo", "Visualizing plan  (pose goal) %s", success ? "" : "FAILED");
  std::cout <<"success execution?:=" << success2 << endl;
  i++;
  std::cout <<"target_position:["<< target_pose.position.x << ","<< target_pose.position.y << "," << target_pose.position.z <<"]" << endl;
  float cpx = float(current_pose.pose.position.x);
  float cpy = float(current_pose.pose.position.y);
  float cpz = float(current_pose.pose.position.z);
  std::cout <<"current_position:["<< cpx << ","<< cpy << "," << cpz <<"]" << endl;
  // Visualizing plans
  ROS_INFO_NAMED("demo", "Visualizing plan  as trajectory line");
  /*visual_tools.publishAxisLabeled(target_pose, "pose");
  visual_tools.publishText(text_pose, "Pose Goal", rvt::WHITE, rvt::XLARGE);
  visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
  visual_tools.trigger(); */
  visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue the demo");
 }  

  Eigen::Vector3d reference_point_position(0.0, 0.0, 0.0);
  Eigen::MatrixXd jacobian;
  current_state->getJacobian(joint_model_group,
                               current_state->getLinkModel(joint_model_group->getLinkModelNames().back()),
                               reference_point_position, jacobian);
  ROS_INFO_STREAM("Jacobian: \n" << jacobian << "\n");
  ros::shutdown();
  return 0;
}

