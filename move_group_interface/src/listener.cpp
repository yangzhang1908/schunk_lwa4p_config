#include "ros/ros.h"
#include <control_msgs/FollowJointTrajectoryAction.h>
#include "control_msgs/FollowJointTrajectoryFeedback.h"
#include "moveit_msgs/ExecuteTrajectoryActionFeedback.h"
#include "gazebo_msgs/LinkStates.h"
#include "geometry_msgs/Pose.h"
#include "moveit_msgs/MoveGroupActionGoal.h"
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

 void ExecuteTrajectoryActionCallback(const moveit_msgs::ExecuteTrajectoryActionFeedback::ConstPtr &msg)
{ 
  const int s = msg->status.status;
  std::cout << endl << "status = " << s << endl; 
  //return s;
} 


void MoveGroupActionGoalCallback(const moveit_msgs::MoveGroupActionGoal::ConstPtr &msg)
{ 
  //const std::vector<double> primitive = msg->goal.request.goal_constraints.primitive_poses.x;

}
void LinkStatesCallback(const gazebo_msgs::LinkStates::ConstPtr &msg)
{ 
  //const double x = msg-> pose.position.x;
  //const std::vector<double> p = msg->pose.arm_1_link;
  /*const double x = msg->link.position.x;
  const double y = msg->pose.position.x;
  const double z = msg->pose.position.x; */

  
  //const std::vector<double>  eefpositionx = msg->pose.position.x;
  
  /*const std::vector<double> eef_orientation = msg->pose.orientation;
  std::cout << endl << "gazebo_msgs/LinkStates:" << endl;
  std::cout << "eff_position  [";
  std::cout << eef_position[0]<< ", ";
  std::cout << eef_position[1]<< ", ";
  std::cout << eef_position[2];
  std::cout << " ]" << endl; 

  std::cout << "eff_orientation  [";
  std::cout << eef_orientation[0]<< ", ";
  std::cout << eef_orientation[1]<< ", ";
  std::cout << eef_orientation[2];
  std::cout << " ]" << endl; */
}    


/*void ArmJointTrajectoryControllerCallback(const control_msgs::FollowJointTrajectoryActionFeedback::ConstPtr &msg)
{ 
  const std::vector<double> p = msg->feedback.desired.positions;
  const std::vector<double> v = msg->feedback.desired.velocities;
  const std::vector<double> a = msg->feedback.desired.accelerations;

  const std::vector<double> p1 = msg->feedback.actual.positions;
  const std::vector<double> v1 = msg->feedback.actual.velocities;
  const std::vector<double> a1 = msg->feedback.actual.accelerations;

  std::cout <<"control_msgs/FollowJointTrajectoryFeedback feedback" << "std_msgs/Header header"<< endl;
  std::cout <<"joint_names:[arm_1_joint, arm_2_joint, arm_3_joint, arm_4_joint, arm_5_joint, arm_6_joint]" << endl << endl;
  std::cout << "trajectory_msgs/JointTrajectoryPoint:" << endl;
  std::cout <<"  desired positions:   [" ;
  std::cout << p[0]<< ", ";
  std::cout << p[1]<< ", ";
  std::cout << p[2]<< ", ";
  std::cout << p[3]<< ", ";
  std::cout << p[4]<< ", ";
  std::cout << p[5];
  std::cout << " ]" << endl; 
  std::cout <<"  desired velocities:  [" ;
  std::cout << v[0]<< ", ";
  std::cout << v[1]<< ", ";
  std::cout << v[2]<< ", ";
  std::cout << v[3]<< ", ";
  std::cout << v[4]<< ", ";
  std::cout << v[5];
  std::cout << " ]" << endl;
  std::cout <<"  desired accelerations:[" ;
  std::cout << a[0]<< ", ";
  std::cout << a[1]<< ", ";
  std::cout << a[2]<< ", ";
  std::cout << a[3]<< ", ";
  std::cout << a[4]<< ", ";
  std::cout << a[5];
  std::cout << " ]" << endl << endl;
  
  std::cout <<"  actual positions:[";
  std::cout << p1[0] << ", ";
  std::cout << p1[1] << ", ";
  std::cout << p1[2] << ", ";
  std::cout << p1[3] << ", ";
  std::cout << p1[4] << ", ";
  std::cout << p1[5] << " ] " << endl; 
  std::cout <<"  actual velocities:[ " ;
  std::cout << v1[0] << ", ";
  std::cout << v1[1] << ", ";
  std::cout << v1[2] << ", ";
  std::cout << v1[3] << ", ";
  std::cout << v1[4] << ", ";
  std::cout << v1[5];
  std::cout << " ]" << endl << endl;

} */


int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle nh;

  ros::Subscriber sub2 = nh.subscribe("execute_trajectory/feedback", 1000, ExecuteTrajectoryActionCallback);
  //int status =ExecuteTrajectoryActionCallback.s;
  //std::cout << endl << "status globle = " << status << endl;
  //s = ExecuteTrajectoryActionCallback;
  //while (ros::ok() s = 3)
  //{
  //ros::Subscriber sub = nh.subscribe("/arm/joint_trajectory_controller/follow_joint_trajectory/feedback", 1000, 	ArmJointTrajectoryControllerCallback);
  //}
  ros::Subscriber sub3 = nh.subscribe("gazebo/link_states", 1000, LinkStatesCallback);
  ros::Subscriber sub4 = nh.subscribe("move_group/goal", 1000, MoveGroupActionGoalCallback);
  ros::spin();
  return 0;
}

/*

include "ros/ros.h"
include "nav_msgs/Odometry.h"

void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
double x = msg->pose.pose.position.x;
double y = msg->pose.pose.position.x;
ROS_INFO("x: %f, y: %f", x, y);
}
int main(int argc, char** argv) {

ros::init(argc, argv, "location_monitor");
ros::NodeHandle nh;
ros::Subscriber sub = nh.subscribe("odom", 10, OdomCallback);
ros::spin();
return 0;
} 

rostopic info /arm/joint_trajectory_controller/follow_joint_trajectory/feedback 
Type: control_msgs/FollowJointTrajectoryActionFeedback

Publishers: 
 * /gazebo (http://yangz-Surface-Pro-4:35863/)

Subscribers: 
 * /move_group (http://yangz-Surface-Pro-4:33683/)


rosmsg show control_msgs/FollowJointTrajectoryActionFeedback 
std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
actionlib_msgs/GoalStatus status
  uint8 PENDING=0
  uint8 ACTIVE=1
  uint8 PREEMPTED=2
  uint8 SUCCEEDED=3
  uint8 ABORTED=4
  uint8 REJECTED=5
  uint8 PREEMPTING=6
  uint8 RECALLING=7
  uint8 RECALLED=8
  uint8 LOST=9
  actionlib_msgs/GoalID goal_id
    time stamp
    string id
  uint8 status
  string text
control_msgs/FollowJointTrajectoryFeedback feedback
  std_msgs/Header header
    uint32 seq
    time stamp
    string frame_id
  string[] joint_names
  trajectory_msgs/JointTrajectoryPoint desired
    float64[] positions
    float64[] velocities
    float64[] accelerations
    float64[] effort
    duration time_from_start
  trajectory_msgs/JointTrajectoryPoint actual
    float64[] positions
    float64[] velocities
    float64[] accelerations
    float64[] effort
    duration time_from_start
  trajectory_msgs/JointTrajectoryPoint error
    float64[] positions
    float64[] velocities
    float64[] accelerations
    float64[] effort
    duration time_from_start */

/*Type: control_msgs/FollowJointTrajectoryActionFeedback

Publishers: 
 * /gazebo (http://yangz-Surface-Pro-4:46177/)

Subscribers: 
 * /move_group (http://yangz-Surface-Pro-4:36165/) */

/*std::cout <<"desired positions:[" << p[0] <<","<< p[1]<< ","<< p[2]<< ","<< p[3]<< ","<< p[4]<< ","<< p[5]<< ","<< "]"<< endl;
  std::cout <<"desired velocities:[" << v[0] <<","<< v[1]<< ","<< v[2]<< ","<< v[3]<< ","<< v[4]<< ","<< v[5]<< ","<< "]"<< endl;
  std::cout <<"desired accelerations:[" << a[0] <<","<< a[1]<< ","<< a[2]<< ","<< a[3]<< ","<< a[4]<< ","<< a[5]<< ","<< "]"<< endl; */

/*rostopic type /execute_trajectory/feedback 
moveit_msgs/ExecuteTrajectoryActionFeedback

rosmsg show moveit_msgs/ExecuteTrajectoryActionFeedback
std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
actionlib_msgs/GoalStatus status
  uint8 PENDING=0
  uint8 ACTIVE=1
  uint8 PREEMPTED=2
  uint8 SUCCEEDED=3
  uint8 ABORTED=4
  uint8 REJECTED=5
  uint8 PREEMPTING=6
  uint8 RECALLING=7
  uint8 RECALLED=8
  uint8 LOST=9
  actionlib_msgs/GoalID goal_id
    time stamp
    string id
  uint8 status
  string text
moveit_msgs/ExecuteTrajectoryFeedback feedback
  string state
header: 
  seq: 3
  stamp: 
    secs: 112
    nsecs: 397000000
  frame_id: ''
status: 
  goal_id: 
    stamp: 
      secs: 112
      nsecs: 397000000
    id: "/move_group_interface_demo2-4-112.397000000"
  status: 4
  text: "Solution found but controller failed during execution"
feedback: 
  state: "IDLE"
---
header: 
  seq: 4
  stamp: 
    secs: 112
    nsecs: 447000000
  frame_id: ''
status: 
  goal_id: 
    stamp: 
      secs: 112
      nsecs: 446000000
    id: "/move_group_interface_demo2-6-112.446000000"
  status: 1
  text: "This goal has been accepted by the simple action server"
feedback: 
  state: "MONITOR"
---
header: 
  seq: 5
  stamp: 
    secs: 116
    nsecs: 318000000
  frame_id: ''
status: 
  goal_id: 
    stamp: 
      secs: 112
      nsecs: 446000000
    id: "/move_group_interface_demo2-6-112.446000000"
  status: 3
  text: "Solution was found and executed."
feedback: 
  state: "IDLE"
---
header: 
  seq: 6
  stamp: 
    secs: 138
    nsecs: 140000000
  frame_id: ''
status: 
  goal_id: 
    stamp: 
      secs: 138
      nsecs: 140000000
    id: "/move_group_interface_demo2-7-138.140000000"
  status: 4
  text: "Solution found but controller failed during execution"
feedback: 
  state: "IDLE"
---
header: 
  seq: 7
  stamp: 
    secs: 138
    nsecs: 176000000
  frame_id: ''
status: 
  goal_id: 
    stamp: 
      secs: 138
      nsecs: 176000000
    id: "/move_group_interface_demo2-9-138.176000000"
  status: 1
  text: "This goal has been accepted by the simple action server"
feedback: 
  state: "MONITOR"
---
header: 
  seq: 8
  stamp: 
    secs: 139 
    nsecs:  38000000
  frame_id: ''
status: 
  goal_id: 
    stamp: 
      secs: 138
      nsecs: 176000000
    id: "/move_group_interface_demo2-9-138.176000000"
  status: 3
  text: "Solution was found and executed."
feedback: 
  state: "IDLE"  */




/*rostopic type /arm/joint_trajectory_controller/follow_joint_trajectory/feedback 
control_msgs/FollowJointTrajectoryActionFeedback
yangz@yangz-Surface-Pro-4:~$ rosmsg show control_msgs/FollowJointTrajectoryActionFeedback

std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
actionlib_msgs/GoalStatus status
  uint8 PENDING=0
  uint8 ACTIVE=1
  uint8 PREEMPTED=2
  uint8 SUCCEEDED=3
  uint8 ABORTED=4
  uint8 REJECTED=5
  uint8 PREEMPTING=6
  uint8 RECALLING=7
  uint8 RECALLED=8
  uint8 LOST=9
  actionlib_msgs/GoalID goal_id
    time stamp
    string id
  uint8 status
  string text
control_msgs/FollowJointTrajectoryFeedback feedback
  std_msgs/Header header
    uint32 seq
    time stamp
    string frame_id
  string[] joint_names
  trajectory_msgs/JointTrajectoryPoint desired
    float64[] positions
    float64[] velocities
    float64[] accelerations
    float64[] effort
    duration time_from_start
  trajectory_msgs/JointTrajectoryPoint actual
    float64[] positions
    float64[] velocities
    float64[] accelerations
    float64[] effort
    duration time_from_start
  trajectory_msgs/JointTrajectoryPoint error
    float64[] positions
    float64[] velocities
    float64[] accelerations
    float64[] effort
    duration time_from_start */

