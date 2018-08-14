#include "ros/ros.h"
#include "std_msgs/String.h"
#include "control_msgs/FollowJointTrajectoryFeedback.h"
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <Eigen/Dense>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int Random(int start, int end){
    int dis = end - start;
    return rand() % dis + start;
}
 void ArmJointTrajectoryControllerCallback(const control_msgs::FollowJointTrajectoryActionFeedback::ConstPtr &msg)
{ 

    int a[10];
    int i = 0;
    srand((unsigned)time(NULL));
    for (i = 0; i < 10; i++){
            a[i] = Random(1, 100);
    }

    for (i = 0; i < 8; i++){
            printf("%d ", a[i]);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle nh;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  //Publisher(const std::string & topic 
  //ros::Publisher gazebo_pub = n.advertise<::control_msgs::FollowJointTrajectoryActionFeedback>("arm/joint_trajectory_controller/follow_joint_trajectory/feedback", 1000);
  
  ros::Publisher pub = nh.advertise<std_msgs::String>("/arm/joint_trajectory_controller/follow_joint_trajectory/feedback", 500, ArmJointTrajectoryControllerCallback);

  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}

/*rosservice list
/apply_planning_scene
/arm/cob_control_mode_adapter_node/get_loggers
/arm/cob_control_mode_adapter_node/set_logger_level
/arm/controller_manager/list_controller_types
/arm/controller_manager/list_controllers
/arm/controller_manager/load_controller
/arm/controller_manager/reload_controller_libraries
/arm/controller_manager/switch_controller
/arm/controller_manager/unload_controller
/arm/driver/halt
/arm/driver/init
/arm/driver/recover
/arm/driver/shutdown
/arm/fake_driver/get_loggers
/arm/fake_driver/set_logger_level
/arm/joint_states_relay/get_loggers
/arm/joint_states_relay/set_logger_level
/arm/joint_trajectory_controller/query_state
/arm/robot_state_publisher/get_loggers
/arm/robot_state_publisher/set_logger_level
/check_state_validity
/clear_octomap
/compute_cartesian_path
/compute_fk
/compute_ik
/dashboard_aggregator/get_loggers
/dashboard_aggregator/set_logger_level
/diagnostic_aggregator/get_loggers
/diagnostic_aggregator/set_logger_level
/diagnostics_agg/add_diagnostics
/fake_joint_calibration/get_loggers
/fake_joint_calibration/set_logger_level
/gazebo/apply_body_wrench
/gazebo/apply_joint_effort
/gazebo/clear_body_wrenches
/gazebo/clear_joint_forces
/gazebo/delete_light
/gazebo/delete_model
/gazebo/get_joint_properties
/gazebo/get_light_properties
/gazebo/get_link_properties
/gazebo/get_link_state
/gazebo/get_loggers
/gazebo/get_model_properties
/gazebo/get_model_state
/gazebo/get_physics_properties
/gazebo/get_world_properties
/gazebo/pause_physics
/gazebo/reset_simulation
/gazebo/reset_world
/gazebo/set_joint_properties
/gazebo/set_light_properties
/gazebo/set_link_properties
/gazebo/set_link_state
/gazebo/set_logger_level
/gazebo/set_model_configuration
/gazebo/set_model_state
/gazebo/set_parameters
/gazebo/set_physics_properties
/gazebo/spawn_sdf_model
/gazebo/spawn_urdf_model
/gazebo/unpause_physics
/gazebo_gui/get_loggers
/gazebo_gui/set_logger_level
/gazebo_gui/set_parameters
/get_planner_params
/get_planning_scene
/listener/get_loggers
/listener/set_logger_level
/move_group/get_loggers
/move_group/load_map
/move_group/ompl/set_parameters
/move_group/plan_execution/set_parameters
/move_group/planning_scene_monitor/set_parameters
/move_group/save_map
/move_group/sense_for_plan/set_parameters
/move_group/set_logger_level
/move_group/trajectory_execution/set_parameters
/move_group_interface_demo/get_loggers
/move_group_interface_demo/set_logger_level
/plan_kinematic_path
/query_planner_interface
/robot_state_publisher/get_loggers
/robot_state_publisher/set_logger_level
/rosout/get_loggers
/rosout/set_logger_level
/rviz_yangz_Surface_Pro_4_23809_3057732996494484632/get_loggers
/rviz_yangz_Surface_Pro_4_23809_3057732996494484632/motionplanning_planning_scene_monitor/set_parameters
/rviz_yangz_Surface_Pro_4_23809_3057732996494484632/reload_shaders
/rviz_yangz_Surface_Pro_4_23809_3057732996494484632/set_logger_level
/set_planner_params
yangz@yangz-Surface-Pro-4:~$  */


/* rostopic 
rostopic echo /rviz_moveit_motion_planning_display/robot_interaction_interactive_marker_topic/update
server_id: "/rviz_yangz_Surface_Pro_4_5475_3778461759321351828"
seq_num: 65
type: 1
markers: []
poses: 
  - 
    header: 
      seq: 0
      stamp: 
        secs: 0
        nsecs:         0
      frame_id: "/world"
    pose: 
      position: 
        x: 3.12806710731e-08
        y: 0.00526171437815
        z: 0.806999999998
      orientation: 
        x: -8.13757519268e-09
        y: 3.86143100956e-14
        z: 0.999999999992
        w: 3.97622318106e-06
    name: "EE:goal_arm_6_link"
erases: []
---
server_id: "/rviz_yangz_Surface_Pro_4_5475_3778461759321351828"
seq_num: 65
type: 0
markers: []
poses: []
erases: []
---
server_id: "/rviz_yangz_Surface_Pro_4_5475_3778461759321351828"
seq_num: 66
type: 1
markers: []
poses: 
  - 
    header: 
      seq: 0
      stamp: 
        secs: 0
        nsecs:         0
      frame_id: "/world"
    pose: 
      position: 
        x: 3.12806710731e-08
        y: 0.00526171437815
        z: 0.806999999998
      orientation: 
        x: -8.13757519268e-09
        y: 3.86143100956e-14
        z: 0.999999999992
        w: 3.97622318106e-06
    name: "EE:goal_arm_6_link"

 rostopic info /rviz_moveit_motion_planning_display/robot_interaction_interactive_marker_topic/update
Type: visualization_msgs/InteractiveMarkerUpdate

Publishers: 
 * /rviz_yangz_Surface_Pro_4_5475_3778461759321351828 (http://yangz-Surface-Pro-4:43147/)

Subscribers: 
 * /rviz_yangz_Surface_Pro_4_5475_3778461759321351828 (http://yangz-Surface-Pro-4:43147/)

rostopic type /rviz_moveit_motion_planning_display/robot_interaction_interactive_marker_topic/update
visualization_msgs/InteractiveMarkerUpdate

rosmsg show visualization_msgs/InteractiveMarkerUpdate
uint8 KEEP_ALIVE=0
uint8 UPDATE=1
string server_id
uint64 seq_num
uint8 type
visualization_msgs/InteractiveMarker[] markers
  std_msgs/Header header
    uint32 seq
    time stamp
    string frame_id
  geometry_msgs/Pose pose
    geometry_msgs/Point position
      float64 x
      float64 y
      float64 z
    geometry_msgs/Quaternion orientation
      float64 x
      float64 y
      float64 z
      float64 w
  string name
  string description
  float32 scale
  visualization_msgs/MenuEntry[] menu_entries
    uint8 FEEDBACK=0
    uint8 ROSRUN=1
    uint8 ROSLAUNCH=2
    uint32 id
    uint32 parent_id
    string title
    string command
    uint8 command_type
  visualization_msgs/InteractiveMarkerControl[] controls
    uint8 INHERIT=0
    uint8 FIXED=1
    uint8 VIEW_FACING=2
    uint8 NONE=0
    uint8 MENU=1
    uint8 BUTTON=2
    uint8 MOVE_AXIS=3
    uint8 MOVE_PLANE=4
    uint8 ROTATE_AXIS=5
    uint8 MOVE_ROTATE=6
    uint8 MOVE_3D=7
    uint8 ROTATE_3D=8
    uint8 MOVE_ROTATE_3D=9
    string name
    geometry_msgs/Quaternion orientation
      float64 x
      float64 y
      float64 z
      float64 w
    uint8 orientation_mode
    uint8 interaction_mode
    bool always_visible
    visualization_msgs/Marker[] markers
      uint8 ARROW=0
      uint8 CUBE=1
      uint8 SPHERE=2
      uint8 CYLINDER=3
      uint8 LINE_STRIP=4
      uint8 LINE_LIST=5
      uint8 CUBE_LIST=6
      uint8 SPHERE_LIST=7
      uint8 POINTS=8
      uint8 TEXT_VIEW_FACING=9
      uint8 MESH_RESOURCE=10
      uint8 TRIANGLE_LIST=11
      uint8 ADD=0
      uint8 MODIFY=0
      uint8 DELETE=2
      uint8 DELETEALL=3
      std_msgs/Header header
        uint32 seq
        time stamp
        string frame_id
      string ns
      int32 id
      int32 type
      int32 action
      geometry_msgs/Pose pose
        geometry_msgs/Point position
          float64 x
          float64 y
          float64 z
        geometry_msgs/Quaternion orientation
          float64 x
          float64 y
          float64 z
          float64 w
      geometry_msgs/Vector3 scale
        float64 x
        float64 y
        float64 z
      std_msgs/ColorRGBA color
        float32 r
        float32 g
        float32 b
        float32 a
      duration lifetime
      bool frame_locked
      geometry_msgs/Point[] points
        float64 x
        float64 y
        float64 z
      std_msgs/ColorRGBA[] colors
        float32 r
        float32 g
        float32 b
        float32 a
      string text
      string mesh_resource
      bool mesh_use_embedded_materials
    bool independent_marker_orientation
    string description
visualization_msgs/InteractiveMarkerPose[] poses
  std_msgs/Header header
    uint32 seq
    time stamp
    string frame_id
  geometry_msgs/Pose pose
    geometry_msgs/Point position
      float64 x
      float64 y
      float64 z
    geometry_msgs/Quaternion orientation
      float64 x
      float64 y
      float64 z
      float64 w
  string name
string[] erases */

