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
                                                               
)"<<std::endl;
std::cout << R"(
         
          _    _           
         | |  | |          
         | |  | |          
         | |/\| |          
         \  /\  /          
          \/  \/           
                           
                           
  ___      _____    ______ 
 / _ \    /  ___|   |  _  \
/ /_\ \   \ `--.    | | | |
|  _  |    `--. \   | | | |
| | | |   /\__/ /   | |/ / 
\_| |_/   \____/    |___/  
                           
                           
          __   __          
          \ \ / /          
           \ V /           
           /   \           
          / /^\ \          
          \/   \/          
                                                                              
)"<<std::endl;
  
  this->publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
  this->key = ' ';
  this->timer_=this->create_wall_timer(10ms,std::bind(&KeyboardControllerNode::PubCmdVelCallBack,this));
  std::shared_ptr<std::thread> read_key_thread = std::make_shared<std::thread>(&KeyboardControllerNode::ReadKeyThread,this);
  (*read_key_thread).detach();
  this->acc_x = 0.02;
  this->acc_w = 0.1;
}


int KeyboardControllerNode::get_key(){
  int ch;
  struct termios oldt;
  struct termios newt;
  
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_iflag |= IGNBRK;
  newt.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
  newt.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
  newt.c_cc[VMIN] = 1;
  newt.c_cc[VTIME] = 0;
  tcsetattr(fileno(stdin), TCSANOW, &newt);
 
  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

void KeyboardControllerNode::ReadKeyThread(){
  while(rclcpp::ok())
  {
    key = get_key();
    std::cout << "pushed : " << key << std::endl;
    
    if(key == 'w')
    {
        twist.linear.x += acc_x;
        std::cout << "foward!" <<std::endl;
    }
    else if(key == 's')
    {
        twist.linear.x -= acc_x;
        std::cout << "backward!" <<std::endl;
    }else if(key == 'a')
    {
        twist.angular.z += acc_w;
        std::cout << "left!" <<std::endl;
    }else if(key == 'd')
    {
        twist.angular.z -= acc_w;
        std::cout << "right!" <<std::endl;
    }
    else if(key == 'x')
    {
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;
        std::cout << "stop!" <<std::endl;
    }
    else if (key == '\x03')
    {
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;
        std::cout << "KEYBOARD WILL BE BACK..." << std::endl;
        rclcpp::shutdown();
    }
  }
}

void KeyboardControllerNode::PubCmdVelCallBack(){
  publisher_->publish(twist);
}