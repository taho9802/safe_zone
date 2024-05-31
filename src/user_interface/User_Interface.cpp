#include "../../include/user_interface/User_Interface.hpp"
#include "../../include/utils/App_State.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <cctype>
#include <iostream>

App_Mode test;

void user_interface() {
  std::cout << "user_inface is running" << std::endl;
    while(test.main_mode != Main_Mode::KILL_PROGRAM) {
      std::cout << "loop fnished running" << std::endl;
      char input = cv::waitKey(1);
      if(input == 'a') {
        test.main_mode = Main_Mode::ADD_ZONE;
        test.sub_mode = Sub_Mode::NUETRAL;
      }
      else if(input == 'd') {
        test.main_mode = Main_Mode::DELETE_ZONE;
        test.sub_mode = Sub_Mode::NUETRAL;
      }
      else if(input == 'q') {
        test.main_mode = Main_Mode::KILL_PROGRAM;
      }
      else if(input == 's'){
        if(test.main_mode == Main_Mode::ADD_ZONE || app_state.main_mode == Main_Mode::DELETE_ZONE) {
          test.sub_mode = Sub_Mode::SAVE;
        }
      }
      else if(input == 'c'){
        if(test.main_mode == Main_Mode::ADD_ZONE || app_state.main_mode == Main_Mode::DELETE_ZONE) {
          test.sub_mode = Sub_Mode::QUIT;
        }
      }
    }
}