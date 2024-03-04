#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <unistd.h>
#include <iostream>
#include <termios.h>
class KeyboardControllerNode : public rclcpp::Node
{
    public:
        KeyboardControllerNode();
    private:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
        int get_key();
        char key(' ');
};