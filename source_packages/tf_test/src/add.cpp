#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_listener.h>

void tfCallBack(const geometry_msgs::PoseStamped &pose){
	std::cout<<"In call back\n";
	tf::TransformBroadcaster br;
  tf::Transform transform;
	transform.setOrigin( tf::Vector3(pose.pose.position.x, pose.pose.position.y, 0.0) );
  transform.setRotation( tf::createQuaternionFromRPY(0.0,0.0,pose.pose.orientation.z) );
	br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"map","odom"));	
}

int main(int argc, char** argv){
  ros::init(argc, argv, "sonny_tf_broadcaster");
  ros::NodeHandle node;
	ros::Subscriber sub=node.subscribe("odominfo",1000,tfCallBack);
	ros::spin();
	return 0;
};

