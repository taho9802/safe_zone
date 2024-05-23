#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>
#include <ctime>
#include <opencv2/highgui.hpp>
#include "../include/zones/Zone.hpp"
#include "../include/zones/Zone_Manager.hpp"

void draw_fps(cv::Mat &frame, int fps) {
  cv::putText(frame, std::to_string(fps), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 1);
}

int find_avail_cams(){
  int index = 0;
  cv::VideoCapture cap;
  while(true){
    cap.open(index);
    if(!cap.isOpened()){
      index++;
    }
    else {
      cap.release();
      break;
    }
  }
  return index;
}

int main() {
  int cam_index = find_avail_cams();
  std::cout << "Available camera index: " << + cam_index << std::endl;
  cv::VideoCapture cap(cam_index);
  if(!cap.isOpened()){
    return -1;
  }
  cv::Mat frame;
  cv::namedWindow("TESTING", cv::WINDOW_AUTOSIZE);
  int frame_counter = 0;
  int tick = 0;
  int fps;
  std::time_t time_begin = std::time(0);
  std::vector<cv::Point> verts = {cv::Point{0,0}, cv::Point{100, 0}, cv::Point{100, 100}, cv::Point{0, 100}};
  cv::Scalar color(225, 0, 0);

  Zone_Manager test = Zone_Manager();
  test.add_zone(verts);

  while(true) {
    cap >> frame;
    cv::flip(frame, frame, 1);
    if (frame.empty()){
      std::cerr << "Failed to capture frame" << std::endl;
      continue;
    }

    frame_counter++;

    std::time_t time_now = std::time(0) - time_begin;
    if(time_now - tick >= 1){
      tick++;
      fps = frame_counter;
      frame_counter = 0;
    }
    draw_fps(frame, fps);
    test.draw_zones(frame);
    cv::imshow("TESTING" ,frame);
    int key = cv::waitKey(1);
    if((key & 0xFF) == 27 || (key & 0xFF) == 'q') {
      break;
    }
  }
  cap.release();
  cv::destroyAllWindows();
  return 0;
}