#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_two_ints_client");
  if (argc != 3)                                                                                        //输入的参数是不是三个
  {
    ROS_INFO("usage: add_two_ints_client X Y");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<beginner_tutorials::AddTwoInts>("add_two_ints");             //创建一个客户端，并方便之后请求服务

  beginner_tutorials::AddTwoInts srv;
  srv.request.a = atoll(argv[1]);                              //传入的参数赋值给srv
  srv.request.b = atoll(argv[2]);

  if (client.call(srv))                                                     //如果调用了服务的话执行这个
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.sum);
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }

  return 0;
}