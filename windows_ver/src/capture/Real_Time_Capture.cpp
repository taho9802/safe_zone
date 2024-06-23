#include "../../include/utils/App_State.hpp"
#include "../../include/capture/Real_Time_Capture.hpp"
#include "../../include/capture/Capture_Loop_Utils.hpp"
#include "../../include/zones/Zone_Manager.hpp"
#include "../../include/user_interface/Input_Collector.hpp"
#include <opencv2/core.hpp>
#include <iostream>

//simple loop will be a standard loop when the app state is at NONE state

void on_mouse(int event, int x, int y, int, void* user_input) {
  if (event == cv::EVENT_LBUTTONDOWN) {
    cv::Point* click_point = static_cast<cv::Point*>(user_input);
    click_point->x = x;
    click_point->y = y;
    std::cout << "Mouse clicked at (" << x << ", " << y << ")" << std::endl;
    user_data.mouse_left_location.store(cv::Point(x, y));
  }
}

void base_loop() {
  std::cout << "running base loop" << std::endl;
  cv::VideoCapture cap(0);
  cv::namedWindow("SZone", cv::WINDOW_NORMAL);
  cv::Point click_point(-1, -1);
  cv::setMouseCallback("SZone", on_mouse, &click_point);

  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 1920);

  

  if(!cap.isOpened()){
   std::cerr << "Error, camera not opened" << std::endl;
  }

  std::cout << "initializing zone manager" << std::endl;
  Zone_Manager zm = Zone_Manager();



  while(app_state.main_mode.load() != Main_Mode::KILL_PROGRAM) {
    switch (app_state.main_mode.load()){
      case Main_Mode::ADD_ZONE:
        std::cout << "in add zone loop" << std::endl;
        //call add_zone function loop
        add_zone(cap, zm);
        //makig sure that the submode is back to default after the loop is exited
        app_state.sub_mode.store(Sub_Mode::NEUTRAL);
        break;
      case Main_Mode::DELETE_ZONE:
        //call delete_zone function loop
        delete_zone(cap, zm);
        //same for the rest of these
        app_state.sub_mode.store(Sub_Mode::NEUTRAL);
        break;
      case Main_Mode::MONITOR:
        monitor_loop(cap, zm);
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