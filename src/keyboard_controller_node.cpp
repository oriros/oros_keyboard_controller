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
#include <stdio.h>
#include <unistd.h>
void KeyboardControllerNode::get_key(){
  int ch;
  struct termios oldt;
  struct termios newt;

  // Store old settings, and copy to new settings
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  // Make required changes and apply the settings
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_iflag |= IGNBRK;
  newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
  newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
  newt.c_cc[VMIN] = 1;
  newt.c_cc[VTIME] = 0;
  tcsetattr(fileno(stdin), TCSANOW, &newt);

  // Get the current character
  ch = getchar();

  // Reapply old settings
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return ch;
}