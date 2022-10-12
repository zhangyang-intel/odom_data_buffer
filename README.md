# odom_data_buffer
目前就是subscriber订阅topic /odom，然后把数据写在一个文件中
直接编译即可
colcon build
运行
source install/setup.bash
ros2 run cpp_pubsub listener

然后在rosbag的终端
ros2 bag play rosbag2_2022_10_09-18_25_30/
