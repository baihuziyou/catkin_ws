#include"ros/ros.h"
#include "tf2_ros/transform_listener.h"                                   //创建TransformListener类,用于监听tf坐标
#include"tf2_ros/buffer.h"                                                              //创建Buffer用于给TransformListener的构造函数中
#include"geometry_msgs/PointStamped.h"                         //创建PointStamped数据所需要包含的头文件
#include"tf2_geometry_msgs/tf2_geometry_msgs.h"     //tf2_ros::Buffer使用方法transform会用到这个头文件定义的数据类型定义


int main(int argc, char  *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "static_sub");
    ros::NodeHandle n;

    // 创建一个buff缓存,然后在创建监听对象,监听对象会把订阅到的数据存入到buffer中
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listern(buffer);

    // 设定一个pointStanp,表示在雷达坐标中的坐标点. 求出base_link的坐标是多少
    geometry_msgs::PointStamped my_point;
    my_point.header.frame_id = "laser_link";             //设定这个点所属于的坐标系是那个
    my_point.header.stamp = ros::Time::now();
    my_point.point.x = 2.0;
    my_point.point.y = 3.0;
    my_point.point.z = 4.0;

    //防止异常base_link找不到,因为订阅数据要时间.两种解决方法
    // 1.在转换之前休眠
    // 2.捕获异常,一直捕获直到不抛出异常
    // ros::Duration(2).sleep();                                                 

    ros::Rate rate(100);
    while (ros::ok())
    {
        try
        {
            geometry_msgs::PointStamped my_point2;
            //使用buffer的转换,传输参数PointStamped,和想要转换到那个坐标系中,然后会返回一个PointStamped类型的值给你
            // 同时转换过程中会用到#include"tf2_geometry_msgs/tf2_geometry_msgs.h"这个头文件
            my_point2 = buffer.transform(my_point, "base_link");
            ROS_INFO("转换后的数据为:%.2f,%.2f,%.2f,参考的坐标系为:%s",
                     my_point2.point.x,
                     my_point2.point.y,
                     my_point2.point.z,
                     my_point2.header.frame_id.c_str()); //c++string是類型,c_str()是为了吧stirng变成c字符数组方便输出.

            rate.sleep();
            ros::spinOnce();
        }
        catch(const std::exception& e)
        {
            ROS_INFO("异常消息:%s", e.what());
        }

        /* code */
    }
    
    /* code */
    return 0;
}
