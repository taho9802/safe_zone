#include "../../include/capture/Capture_Loop_Utils.hpp"
#include "../../include/utils/App_State.hpp"
#include "../../include/zones/Zone_Manager.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <vector>


void simple_loop(cv::VideoCapture& cap_obj){
  if(!cap_obj.isOpened()){
    std::cerr << "Cap object is not open at simple loop function" << std::endl;
    return;
  }

  cv::Mat frame;
  while(app_state.main_mode.load() == Main_Mode::NONE){
    cap_obj >> frame;    
    if(frame.empty()){
      std::cerr << "Frame failed to capture at simple loop function" << std::endl;
    }
    cv::putText(frame, "Current Mode: None..", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(225, 0, 0), 2);
    cv::imshow("SZone", frame);
  }
  return; 
}

void add_zone(cv::VideoCapture& cap_obj, Zone_Manager& zm){
  //set last stored point to default to ensure collection consistency//
  app_state.mouse_left_location.store(cv::Point(-1, -1));
  std::vector<cv::Point> potential_verts;
  if(!cap_obj.isOpened()){
    std::cerr << "Cap object failed to open at add_zone loop" << std::endl;
    return; 
  }

  cv::Mat frame;
  while(app_state.main_mode.load() == Main_Mode::ADD_ZONE) {
    if(app_state.sub_mode.load() == Sub_Mode::QUIT) {
      app_state.sub_mode.store(Sub_Mode::NEUTRAL);
      app_state.main_mode.store(Main_Mode::MONITOR);
      return;
    }
    cap_obj >> frame;
    if(frame.empty()) {
      std::cerr << "Frame failed to capture at add_zone loop function" << std::endl;
    }
    cv::putText(frame, "Current Mode: Add zone..", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(225, 0, 0), 2);
    
    if(app_state.mouse_left_location.load() != cv::Point(-1, -1)){
      potential_verts.push_back(app_state.mouse_left_location.load());
      app_state.mouse_left_location.store(cv::Point(-1, -1));
    }

    if(potential_verts.size() != 0) {
      for(int i = 0; i < potential_verts.size(); i++) {
        cv::circle(frame, potential_verts[i], 2, cv::Scalar(0, 225, 225), 2);
      }
    }

    if(zm.get_num_zones() != 0) {
      zm.draw_zones(frame);
    }

    if(app_state.sub_mode.load() == Sub_Mode::SAVE){
      std::cout << "Saving points" << std::endl;
      zm.add_zone(potential_verts);
      app_state.main_mode.store(Main_Mode::MONITOR);
      app_state.sub_mode.store(Sub_Mode::NEUTRAL);
      return;
    }
    cv::imshow("SZone", frame);
  }
  return;
}

void delete_zone(cv::VideoCapture& cap_obj, Zone_Manager& zm){
  if(!cap_obj.isOpened()) {
    std::cerr << "Cap object failed to open at delete_zone loop" << std::endl;
    return;
  }

  cv::Mat frame;
  while(app_state.main_mode.load() == Main_Mode::DELETE_ZONE) {
    if(app_state.sub_mode.load() == Sub_Mode::QUIT){
      std::cout << "exiting delete mode" << std::endl;
      app_state.sub_mode.store(Sub_Mode::NEUTRAL);
      app_state.main_mode.store(Main_Mode::MONITOR);
      return;
    }
    cap_obj >> frame;
    if(frame.empty()){
      std::cerr << "Frame failed to capture at delete_zone loop function" << std::endl;
    }
    cv::putText(frame, "Current Mode: Delete zone..", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(225, 0, 0), 2);
    //add left click logic here and find out which zone it is//
    //then delete zone//
    cv::imshow("SZone", frame);
  }
}


void monitor_loop(cv::VideoCapture& cap_obj, Zone_Manager& zm) {
  if(!cap_obj.isOpened()){
    std::cerr << "Cap object failed to open at monitor_loop" << std::endl;
    return;
  }

  cv::Mat frame;
  while(app_state.main_mode.load() == Main_Mode::MONITOR) {
    if(app_state.sub_mode.load() == Sub_Mode::QUIT) {
      std::cout << "exiting mointor mode" << std::endl;
      app_state.main_mode.store(Main_Mode::NONE);
      app_state.sub_mode.store(Sub_Mode::NEUTRAL);
      return;
    }
    cap_obj >> frame;
    //load zones using zone_manager and all the other logic here//
    cv::putText(frame, "Current Mode: Monitor mode..", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(225, 0, 0), 2);
    zm.draw_zones(frame);
    cv::imshow("SZone", frame);
  }
}
