#include <iostream>
#include <thread>
#include "../include/user_interface/Input_Collector.hpp"
#include "../include/user_interface/User_Interface.hpp"
#include "../include/utils/App_State.hpp"
#include "../include/capture/Real_Time_Capture.hpp"

App_Mode app_state;
User_Data user_data;

int main() {
  std::cout << "Starting CV thread..." << std::endl;
  std::thread cv_thread(base_loop);
  std::cout << "CV thread started on core 1." << std::endl;
  std::thread ui_thread(user_interface);
  cv_thread.join();
  ui_thread.join();
  return 0;
}