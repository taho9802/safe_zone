#ifndef INPUT_COLLECTOR_HPP
#define INPUT_COLLECTOR_HPP
#include <iostream>
#include <atomic>
#include <opencv2/core.hpp>


struct User_Data {
    std::atomic<cv::Point> mouse_left_location {cv::Point(-1, -1)};
    std::atomic<char> last_key_input {0};
};

extern User_Data user_data;


#endif