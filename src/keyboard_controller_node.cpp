#include "oros_keyboard_controller/keyboard_controller.hpp"

KeyboardControllerNode::KeyboardControllerNode():Node("keyboard_controller"){
    std::cout << R"(
 _   __ _______   _______  _____  ___  ____________            
| | / /|  ___\ \ / / ___ \|  _  |/ _ \ | ___ \  _  \           
| |/ / | |__  \ V /| |_/ /| | | / /_\ \| |_/ / | | |           
|    \ |  __|  \ / | ___ \| | | |  _  ||    /| | | |           
| |\  \| |___  | | | |_/ /\ \_/ / | | || |\ \| |/ /            
\_| \_/\____/  \_/ \____/  \___/\_| |_/\_| \_|___/             
                                                               
                                                               
 _____ _____ _   _ ___________ _____ _      _      ___________ 
/  __ \  _  | \ | |_   _| ___ \  _  | |    | |    |  ___| ___ \
| /  \/ | | |  \| | | | | |_/ / | | | |    | |    | |__ | |_/ /
| |   | | | | . ` | | | |    /| | | | |    | |    |  __||    / 
| \__/\ \_/ / |\  | | | | |\ \\ \_/ / |____| |____| |___| |\ \ 
 \____/\___/\_| \_/ \_/ \_| \_|\___/\_____/\_____/\____/\_| \_|
                                                               
)";
  publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
}