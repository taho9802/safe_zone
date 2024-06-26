
#ifndef APP_STATE_HPP
#define APP_STATE_HPP

#include <atomic>
#include <opencv2/core.hpp>

enum class Main_Mode {
  KILL_PROGRAM,
  MONITOR,
  ADD_ZONE,
  DELETE_ZONE,
  NONE,
};

enum class Sub_Mode {
  SAVE,
  QUIT,
  NEUTRAL,
};


struct App_Mode {
  std::atomic<Main_Mode> main_mode {Main_Mode::NONE};
  std::atomic<Sub_Mode> sub_mode {Sub_Mode::NEUTRAL};
  std::atomic<cv::Point> mouse_left_location {cv::Point(-1, -1)};
};

extern App_Mode app_state;

#endif // APP_STATE_HPP