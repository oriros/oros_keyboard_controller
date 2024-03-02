#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <iostream>
class KeyboardControllerNode : public rclcpp::Node
{
    public:
        KeyboardControllerNode();
    private:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

};