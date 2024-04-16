#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

int main() {
  cv::VideoCapture cap(0);
  if(!cap.isOpened()){
    return -1;
  }
  cv::Mat frame;
  cv::namedWindow("TESTING", cv::WINDOW_AUTOSIZE);
  while(true) {
    cap >> frame;
    cv::flip(frame, frame, 1);
    if (frame.empty()){
      std::cerr << "Failed to capture frame" << std::endl;
      continue;
    }
    
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