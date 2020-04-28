#include <ros/ros.h>
#include <visualization_msgs/Marker.h> 
#include <nav_msgs/Odometry.h>
#include <math.h>

//float goal_x1 = 0;
//float goal_y1 = 0;
//float goal_x2 = 0;
//float goal_y2 = 0;

bool goal_reached = false;


void odom_callback(const nav_msgs::Odometry::ConstPtr& odom_msg){
  const float threshold = 0.001;
//ROS_INFO_STREAM(sqrt(pow(odom_msg->twist.twist.linear.x,2)+pow(odom_msg->twist.twist.linear.y,2)+pow(odom_msg->twist.twist.angular.z,2)));
    
  if (sqrt(pow(odom_msg->twist.twist.linear.x,2)+pow(odom_msg->twist.twist.linear.y,2)+pow(odom_msg->twist.twist.angular.z,2)) < threshold){
    goal_reached = true;
  }
  else {
    goal_reached = false;
  }

}

int main(int argc, char** argv){
  ros::init(argc,argv,"add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("odom", 1000, odom_callback);
  // Set our shape type to be cude
  uint32_t shape = visualization_msgs::Marker::CUBE;
//while(ros::ok()){
  visualization_msgs::Marker marker;

    //ROS_INFO_STREAM(odom_sub);
    //set the frame id and timestamp
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    //set the namespace and id for this marker
    marker.ns = "add_markers";
    marker.id = 0;
    marker.type = shape; // cube

    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker
    marker.pose.position.x = -4.0;
    marker.pose.position.y = -3.0;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker
    marker.scale.x = 0.4;
    marker.scale.y = 0.4;
    marker.scale.z = 0.4;

    // Set the color of the marker
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    sleep(1);
    marker_pub.publish(marker);

    //goal_x1 = marker.pose.position.x;
    //goal_y1 = marker.pose.position.y;
    //ROS_ERROR_STREAM(goal_x);
    while(ros::ok() && !goal_reached){
      ros::spinOnce();
    }
    ROS_INFO("Robot reached the pickup location");
    marker.action = visualization_msgs::Marker::DELETE;
    sleep(1);    
    ROS_INFO("Object picket and delivery in progress!!");
    marker_pub.publish(marker); 
    
    // Set the new pose of the marker
    marker.pose.position.x = 2.0;
    marker.pose.position.y = 1.0;
    goal_reached = false;
    sleep(6);
    //goal_x2 = marker.pose.position.x;
    //goal_y2 = marker.pose.position.y;
    //ROS_ERROR_STREAM("Dropoff set" << goal_x);
    while (ros::ok() && !goal_reached){
//ROS_ERROR_STREAM("to the drop_off");
      ros::spinOnce();
      //time_between_ros_wakeups.sleep();
    }

    marker.action = visualization_msgs::Marker::ADD;
    //sleep(0.001);
    ROS_INFO("Hurray, Object reached the drop off location!!");
    marker_pub.publish(marker);
    
    //sleep(5);

    r.sleep();
    return 0;
 //} 
}
