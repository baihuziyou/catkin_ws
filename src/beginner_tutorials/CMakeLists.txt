cmake_minimum_required(VERSION 3.0.2)
project(beginner_tutorials)

#找到catkin的功能包
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation     #使用msg和srv文件时要添加这个功能包
)



#添加msg文件
add_message_files(
  FILES
  Num.msg
)

#添加srv文件
add_service_files(
  FILES
  AddTwoInts.srv
)



#通过这个使得msg和srv生成对应的头文件
generate_messages(
  DEPENDENCIES
  std_msgs
)


catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
#  DEPENDS system_lib
)


include_directories(
 include ${catkin_INCLUDE_DIRS}
)


add_executable(talker src/talker.cpp)                                                                                 #编译talker.cpp为talker
target_link_libraries(talker ${catkin_LIBRARIES})                                                          #把catkin_LIBRARIES和talker链接起来
add_dependencies(talker beginner_tutorials_generate_messages_cpp)          #使用msg和srv生成的头文件要添加依赖，不用可以不谢，talker和listenner中可以不用写的

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener beginner_tutorials_generate_messages_cpp)

add_executable(add_two_ints_server src/add_two_ints_server.cpp)                #服务端客户端的cmake构建
target_link_libraries(add_two_ints_server ${catkin_LIBRARIES})
add_dependencies(add_two_ints_server beginner_tutorials_gencpp)

add_executable(add_two_ints_client src/add_two_ints_client.cpp)
target_link_libraries(add_two_ints_client ${catkin_LIBRARIES})
add_dependencies(add_two_ints_client beginner_tutorials_gencpp)
