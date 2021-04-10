#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char **argv)
{
  setlocale(LC_ALL,"");                                               //加入这个注释后ROS::INFO显示中文就不会有乱码了。
  ros::init(argc, argv, "talker");                               //初始化节点，名称为talker
  ros::NodeHandle n;                                                 //获取主节点句柄
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);                //告诉主节点会在chatter中发布一个std_msg/String类型的消息 

  ros::Rate loop_rate(10);                                        //记录上次Rate::sleep()到现在的时间
  int count = 0;

  while (ros::ok())
  {
    std_msgs::String msg;
    std::stringstream ss;
    ss << "hello world " << count;

    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());      

    chatter_pub.publish(msg);                                   //发布消息
    ros::spinOnce();                                                         //调用回调函数，这里没有
    loop_rate.sleep();                                                     //使用ros::Rate在剩下的时间内休眠，达到10hz的发布速率
    ++count;
  }
  
  return 0;
}
