#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <chrono>

using namespace std::chrono_literals;

class KeyboardControllerNode : public rclcpp::Node
{
    public:
        KeyboardControllerNode();
    private:
        void ReadKeyThread();
        void PubCmdVelCallBack();
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
        int get_key();
        char key;
        rclcpp::TimerBase::SharedPtr timer_;
        geometry_msgs::msg::Twist twist;
};