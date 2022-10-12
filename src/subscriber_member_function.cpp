// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>

#include <fstream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "buffer.h"
#include "nav_msgs/msg/odometry.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    odom_ = Odom_Data();
    result_path_ = "/home/zy/ws/odom_buffer_dev/result/";
    result_path_ += "/" + std::to_string(int(rclcpp::Clock().now().seconds())) + ".txt";
    std::cout<<result_path_<<std::endl;
    subscription_ = this->create_subscription<nav_msgs::msg::Odometry>(
      "odom", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const nav_msgs::msg::Odometry::SharedPtr msg) const
  {
    //std::cout<<msg->child_frame_id<<std::endl;
    static std::ofstream of_write(result_path_);

    // Eigen::Matrix3d R = msg->pose.block(0, 0, 3, 3);
    // Eigen::Quaterniond q(R);
    // std_msgs::msg::Header tmp = msg->header;
     of_write << std::fixed << rclcpp::Time(msg->header.stamp).seconds()
                             << " " << msg->pose.pose.position.x << " " << msg->pose.pose.position.y << " " << msg->pose.pose.position.z
                             << " " << msg->pose.pose.orientation.x << " " << msg->pose.pose.orientation.y << " " << msg->pose.pose.orientation.z << " " << msg->pose.pose.orientation.w
                            << std::endl;
    
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->child_frame_id.c_str());
  }
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_;
  Odom_Data odom_;
  std::string result_path_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
