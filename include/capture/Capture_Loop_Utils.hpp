#ifndef CAPTURE_LOOP_UTILS_HPP
#define CAPTURE_LOOP_UTILS_HPP

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "../zones/Zone_Manager.hpp"
#include <iostream>

void simple_loop(cv::VideoCapture& cap_obj);
void add_zone(cv::VideoCapture& cap_obj, Zone_Manager& zm);
void delete_zone(cv::VideoCapture& cap_obj , Zone_Manager& zm);
void monitor_loop(cv::VideoCapture& cap_obj, Zone_Manager& zm);


#endif //CAPTURE_LOOP_UTILS_HPP