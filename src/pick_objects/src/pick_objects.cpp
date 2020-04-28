#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

//Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc,argv,"pick_objects");
  
  // tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  
  //wait 5 sec for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  move_base_msgs::MoveBaseGoal goal;
  
  //we'll send a goal to the robot to move 1 meter forward
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = -4.0;
  goal.target_pose.pose.position.y = -3.0;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending pickup goal");

  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the robot moved to the pickup zone");
  }
  else{
    ROS_INFO("ERROR: The robot failed to move to the pickup zone");
  }

  //wait 5 sec for the action server to come up

  ros::Duration(5.0).sleep();
  ROS_INFO("Wait 5 second to pick the package");

  //Add the second (dropoff) goal
  goal.target_pose.pose.position.x = 2.0;
  goal.target_pose.pose.position.y = 1.0;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending drop off goal");

  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the robot moved to the drop off zone");
  }
  else{
    ROS_INFO("ERROR: The robot failed to move to the pickup zone");
  }


  //return 0;
}
