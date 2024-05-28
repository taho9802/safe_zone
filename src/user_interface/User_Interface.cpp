#include "../../include/user_interface/User_Interface.hpp"
#include "../../include/utils/App_State.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <cctype>
#include <iostream>

void user_interface() {
  std::cout << "user_inface is running" << std::endl;
    while(app_state.main_mode.load() != Main_Mode::KILL_PROGRAM) {
      std::cout << "loop fnished running" << std::endl;
      char input = cv::waitKey(1);
      if(input == 'a') {
        app_state.main_mode.store(Main_Mode::ADD_ZONE);
        app_state.sub_mode.store(Sub_Mode::NUETRAL);
      }
      else if(input == 'd') {
        app_state.main_mode.store(Main_Mode::DELETE_ZONE);
        app_state.sub_mode.store(Sub_Mode::NUETRAL);
      }
      else if(input == 'q') {
        app_state.main_mode.store(Main_Mode::KILL_PROGRAM);
      }
      else if(input == 's'){
        if(app_state.main_mode.load() == Main_Mode::ADD_ZONE || app_state.main_mode.load() == Main_Mode::DELETE_ZONE) {
          app_state.sub_mode.store(Sub_Mode::SAVE);
        }
      }
      else if(input == 'c'){
        if(app_state.main_mode.load() == Main_Mode::ADD_ZONE || app_state.main_mode.load() == Main_Mode::DELETE_ZONE) {
          app_state.sub_mode.store(Sub_Mode::QUIT);
        }
      }
    }
}