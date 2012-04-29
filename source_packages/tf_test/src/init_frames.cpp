#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>

void tfCallBack(const geometry_msgs::PoseStamped &pose){
	
	std::cout<<"In call back\n";
	static tf::TransformBroadcaster br;
  tf::Transform transform;

	transform.setOrigin( tf::Vector3(0.089, 0.0, 0.0) );
  transform.setRotation( tf::Quaternion(0.0, 0.0, 0.0,1.0) );
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));

	transform.setOrigin( tf::Vector3(0.218,0.0,0.0) );
	transform.setRotation( tf::Quaternion(0.0,0.0,0.0,1.0) );
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "openni_camera"));

	transform.setOrigin( tf::Vector3(pose.pose.position.x/100, pose.pose.position.y/100, 0.0) );
  transform.setRotation( tf::createQuaternionFromRPY(0.0,0.0,pose.pose.orientation.z) );
	br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"map","odom"));	
}


int main(int argc, char** argv){

	ros::init(argc, argv, "sonny_tf_broadcaster_init");
  ros::NodeHandle node;
	ros::Subscriber sub=node.subscribe("odominfo",1000,tfCallBack);
	ros::spin();
  return 0;
};
