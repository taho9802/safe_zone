#include "../../include/utils/App_State.hpp"
#include "../../include/capture/Real_Time_Capture.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <atomic>
#include <iostream>

//simple loop will be a standard loop when the app state is at NONE state
void simple_loop(cv::VideoCapture* cap_pointer){
  if(!cap_pointer->isOpened()){
    std::cerr << "Cap object is not open at simple loop function" << std::endl;
    return;
  }

  cv::Mat frame;
  while(app_state.main_mode.load() == Main_Mode::NONE){
    std::cout << "running in simple loop" << std::endl;
    *cap_pointer >> frame;    
    if(frame.empty()){
      std::cerr << "Frame failed to capture at simple loop function" << std::endl;
    }
    cv::putText(frame, "Current Mode: None..", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(225, 0, 0), 2);
    cv::imshow("SZone", frame);
    cv::waitKey(1);
  }
  return; 
}

void add_zone(cv::VideoCapture* cap_pointer){
  if(!cap_pointer->isOpened()){
    std::cerr << "Cap object failed to open at add_zone loop" << std::endl;
    return; 
  }

  cv::Mat frame;
  while(app_state.main_mode.load() == Main_Mode::ADD_ZONE) {
    if(app_state.sub_mode.load() == Sub_Mode::QUIT) {
      app_state.sub_mode.store(Sub_Mode::NUETRAL);
      app_state.main_mode.store(Main_Mode::MONITOR);
      return;
    }
    *cap_pointer >> frame;
    if(frame.empty()) {
      std::cerr << "Frame failed to capture at add_zone loop function" << std::endl;
    }
    cv::putText(frame, "Current Mode: Add zone..", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(225, 0, 0), 2);
    //add left-click event listener here//
    if(app_state.sub_mode.load() == Sub_Mode::SAVE){
      std::cout << "Saving points" << std::endl;
      app_state.main_mode.store(Main_Mode::MONITOR);
      app_state.sub_mode.store(Sub_Mode::NUETRAL);
      return;
    //add logic to add the zone to the zone manager.
    cv::imshow("SZone", frame);
    cv::waitKey(1);
    }
  }
  return;
}

void delete_zone(cv::VideoCapture* cap_pointer){
  if(!cap_pointer->isOpened()) {
    std::cerr << "Cap object failed to open at delete_zone loop" << std::endl;
    return;
  }

  cv::Mat frame;
  while(app_state.main_mode.load() == Main_Mode::DELETE_ZONE) {
    if(app_state.sub_mode.load() == Sub_Mode::QUIT){
      std::cout << "exiting delete mode" << std::endl;
      app_state.sub_mode.store(Sub_Mode::NUETRAL);
      app_state.main_mode.store(Main_Mode::MONITOR);
      return;
    }
    *cap_pointer >> frame;
    if(frame.empty()){
      std::cerr << "Frame failed to capture at delete_zone loop function" << std::endl;
    }
    cv::putText(frame, "Current Mode: Delete zone..", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(225, 0, 0), 2);
    //add left click logic here and find out which zone it is//
    //then delete zone//
    cv::imshow("SZone", frame);
    cv::waitKey(1);
  }
}


void monitor_loop(cv::VideoCapture* cap_pointer) {
  if(!cap_pointer->isOpened()){
    std::cerr << "Cap object failed to open at monitor_loop" << std::endl;
    return;
  }

  cv::Mat frame;
  while(app_state.main_mode.load() == Main_Mode::MONITOR) {
    if(app_state.sub_mode.load() == Sub_Mode::QUIT) {
      std::cout << "exiting mointor mode" << std::endl;
      app_state.main_mode.store(Main_Mode::NONE);
      app_state.sub_mode.store(Sub_Mode::NUETRAL);
      return;
    }
    //load zones using zone_manager and all the other logic here//
    cv::putText(frame, "Current Mode: Monitor mode..", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(225, 0, 0), 2);
    cv::imshow("SZone", frame);
    cv::waitKey(1);
  }
}


void base_loop() {
  std::cout << "running base loop" << std::endl;
  cv::VideoCapture cap(0);

  if(!cap.isOpened()){
   std::cerr << "Error, camera not opened" << std::endl;
  }

  while(app_state.main_mode.load() != Main_Mode::KILL_PROGRAM) {
    cv::waitKey(1);
    switch (app_state.main_mode.load()){
      case Main_Mode::ADD_ZONE:
        //call add_zone function loop
        add_zone(&cap);
        //makig sure that the submode is back to default after the loop is exited
        app_state.sub_mode.store(Sub_Mode::NUETRAL);
        break;
      case Main_Mode::DELETE_ZONE:
        //call delete_zone function loop
        delete_zone(&cap);
        //same for the rest of these
        app_state.sub_mode.store(Sub_Mode::NUETRAL);
        break;
      case Main_Mode::MONITOR:
        monitor_loop(&cap);
        // call monitor loop
        break;
      default:
        std::cout << "in default switch loop" << std::endl;
        simple_loop(&cap);
        //call basic loop function
        break;
    }
  }
  cap.release();
  cv::destroyAllWindows();
}