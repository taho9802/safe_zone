#include "../../include/utils/App_State.hpp"
#include "../../include/capture/Real_Time_Capture.hpp"
#include "../../include/capture/Capture_Loop_Utils.hpp"
#include <opencv2/core.hpp>
#include <iostream>

//simple loop will be a standard loop when the app state is at NONE state

void base_loop() {
  std::cout << "running base loop" << std::endl;
  cv::VideoCapture cap(0);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);

  if(!cap.isOpened()){
   std::cerr << "Error, camera not opened" << std::endl;
  }

  while(app_state.main_mode.load() != Main_Mode::KILL_PROGRAM) {
    switch (app_state.main_mode.load()){
      case Main_Mode::ADD_ZONE:
        std::cout << "in add zone loop" << std::endl;
        //call add_zone function loop
        add_zone(cap);
        //makig sure that the submode is back to default after the loop is exited
        app_state.sub_mode.store(Sub_Mode::NEUTRAL);
        break;
      case Main_Mode::DELETE_ZONE:
        //call delete_zone function loop
        delete_zone(cap);
        //same for the rest of these
        app_state.sub_mode.store(Sub_Mode::NEUTRAL);
        break;
      case Main_Mode::MONITOR:
        monitor_loop(cap);
        // call monitor loop
        break;
      default:
        std::cout << "in default switch loop" << std::endl;
        simple_loop(cap);
        //call basic loop function
        break;
    }
  }
  cap.release();
  cv::destroyAllWindows();
}