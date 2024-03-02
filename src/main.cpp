#include "oros_keyboard_controller/keyboard_controller.hpp"

// 네이밍
// 프로젝트  : oros_keyboard_controller
// 노드 소스 : keyboard_controller.cpp
// 노드 이름 : keyboard_controller
// 노드 클래스 : keyboardControllerNode

int main(int argc, char** argv){
    rclcpp::init(argc,argv);
    auto node = std::make_shared<KeyboardControllerNode>();
    rclcpp::spin(node);
    return 0;
}