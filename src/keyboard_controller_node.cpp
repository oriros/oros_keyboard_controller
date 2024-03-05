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
         
        i 
      j k l   
        , 

o : increase dx
c : decrease dx
u : increase dw
m : decrease dw

)"<<std::endl;
  
  this->publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
  this->key = ' ';
  this->timer_=this->create_wall_timer(10ms,std::bind(&KeyboardControllerNode::PubCmdVelCallBack,this));
  std::shared_ptr<std::thread> read_key_thread = std::make_shared<std::thread>(&KeyboardControllerNode::ReadKeyThread,this);
  (*read_key_thread).detach();
  this->acc_x = 0.01;
  this->acc_w = 0.05;
  this->max_lin_speed = 3.0;
  this->max_ang_speed = 1.57;
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
    
    if(key == 'i')
    {
        twist.linear.x += acc_x;
        std::cout << "foward!" <<std::endl;
    }
    else if(key == ',')
    {
        twist.linear.x -= acc_x;
        std::cout << "backward!" <<std::endl;
    }else if(key == 'j')
    {
        twist.angular.z += acc_w;
        std::cout << "left!" <<std::endl;
    }else if(key == 'l')
    {
        twist.angular.z -= acc_w;
        std::cout << "right!" <<std::endl;
    }
    else if(key == 'k')
    {
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;
        std::cout << "stop!" <<std::endl;
    }
    else if(key == 'o')
    {
        acc_x += 0.01;
        acc_x=std::max(0.01,std::min(acc_x,0.1));
        std::cout << "dx : " << acc_x <<std::endl;
    }
    else if(key == '.')
    {
        acc_x -= 0.01;
        acc_x=std::max(0.01,std::min(acc_x,0.1));
        std::cout << "dx : " << acc_x <<std::endl;
    }
    else if(key == 'u')
    {
        acc_w += 0.01;
        acc_w=std::max(0.01,std::min(acc_w,0.2));
        std::cout << "dw : " << acc_w <<std::endl;
    }
    else if(key == 'm')
    {
        acc_w -= 0.01;
        acc_w=std::max(0.01,std::min(acc_w,0.2));
        std::cout << "dw : " << acc_w <<std::endl;
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
  twist.linear.x=std::max(-max_lin_speed,std::min(twist.linear.x,max_lin_speed));
  twist.angular.z=std::max(-max_ang_speed,std::min(twist.angular.z,max_ang_speed));
  publisher_->publish(twist);
}