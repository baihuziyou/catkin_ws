#include"ros/ros.h"
#include"tf2_ros/static_transform_broadcaster.h"   //静态坐标广播器，StaticTransformBroadcaster在这个里面
#include"geometry_msgs/TransformStamped.h"     //TransformStamped 类在这个里面
#include"tf2/LinearMath/Quaternion.h"                        //四元数头文件

/*
    使用StaticTransformBroadcaster发布tf数据,发布的数据类型是geometry_msgs::TransformStamped
    使用使用StaticTransformBroadcaster类的sendTransform方法发布数据
 */

int main(int argc, char  *argv[])
{
    // 2.配置地域的信,参数为空则为当地。这样配置中文不会乱码。
    setlocale(LC_ALL, "");

    // 2.节点初始化 ,节点名称为static_pub。节点句柄ros::NodeleHandle n;
    ros::init(argc, argv, "static_pub");
    ros::NodeHandle n;

    // 3.创建发布对象,发布方法为:sendTransform(const std::vector<geometry_msgs::TransformStamped> &transforms)
    //     所以要创建一个TransformStamped的消息用来发布。
    tf2_ros::StaticTransformBroadcaster pub;

    // 4.组织被发布的消息
    geometry_msgs::TransformStamped my_msgs;
    my_msgs.header.stamp = ros::Time::now();                          //获取当前时间戳给tfs的header的stamp值
    my_msgs.header.frame_id = "base_link";
    my_msgs.child_frame_id = "laser_link";
    my_msgs.transform.translation.x = 0.2;
    my_msgs.transform.translation.y = 0.2;
    my_msgs.transform.translation.z = 0.5;
    //TransformStamped需要使用四元数制定旋转，四元数在tf2/LinearMath/Quaternion.h中
    tf2::Quaternion qtn;
    qtn.setRPY(0, 0, 0); //通过给四元数指定RPY构造出四元数的值,通过四元数的GETX,Y,Z,W获得对应的x,y,z;
    my_msgs.transform.rotation.x = qtn.getX();
    my_msgs.transform.rotation.y = qtn.getY();
    my_msgs.transform.rotation.z = qtn.getZ();
    my_msgs.transform.rotation.w = qtn.getW();

    // 5.发布数据
    pub.sendTransform(my_msgs);

    // 6.ros::spin()
    ros::spin(); //while(1)

    return 0;
}
