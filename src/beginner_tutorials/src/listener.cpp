#include "ros/ros.h"
#include "std_msgs/String.h"

//回调函数 chaatterCallback 当有消息到达chatter话题时，就会被调用。他是使用boost shared_ptr（共享所有权）智能指针传递数据的
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);     //通过主节点订阅chatter话题，有消息时，ROS就会调用chatterCallback()函数，第二个参数是队列
  ros::spin();                        //==while(1),同时也会查看并调用回调函数
  return 0;
}