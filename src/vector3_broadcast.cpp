#include <ros/ros.h>
#include <math.h>
#include <sensor_msgs/Imu.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Vector3.h>

ros::Publisher pub_orientation;
geometry_msgs::Vector3 orientation;

float radToDeg(float rad){
    float pi = 3.1415;
    return (rad * (180/pi));
}

void pixhawkImuCallback(const sensor_msgs::Imu::ConstPtr& data){
sensor_msgs::Imu pixhawk_imu;
pixhawk_imu = *data;

tf2::Quaternion q_orig, q_new;
tf2::convert(pixhawk_imu.orientation , q_orig);
tf2::Matrix3x3 m(q_orig);
double roll, pitch, yaw;
m.getRPY(roll, pitch, yaw);
q_new.setRPY(-pitch , roll, -yaw);
//Quaternion conversion
// tf2::Quaternion q_orig, q_rot, q_new;
// tf2::convert(pixhawk_imu.orientation , q_orig);
// q_rot.setRPY(radToDeg(90.0) , 0, radToDeg(90.0));
// q_new = q_rot*q_orig;
//tf2::convert(q_new, pixhawk_imu.orientation);
ROS_INFO_STREAM("\nRotation in:\nx: " << roll << "\t"<< radToDeg(roll) << "\ny: "<< pitch<< "\t"<< radToDeg(pitch) << "\nz: "<< yaw<< "\t"<< radToDeg(yaw));
orientation.x = radToDeg(roll);
orientation.y = radToDeg(pitch);
orientation.z = radToDeg(yaw);
pub_orientation.publish(orientation);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "pixhawk_imu_to_eular");
  ros::NodeHandle nh;
  ros::Subscriber imu_sub;

  imu_sub = nh.subscribe<sensor_msgs::Imu>( "/mavros/imu/data", 1,  pixhawkImuCallback);  
  pub_orientation = nh.advertise<geometry_msgs::Vector3>("/mavros/imu/data/eular", 1);
  ros::spin();
  return 0;
}