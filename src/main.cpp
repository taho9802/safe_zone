#include <iostream>
#include <thread>
#include <pthread.h>
#include <sched.h>
#include "../include/user_interface/User_Interface.hpp"
#include "../include/utils/App_State.hpp"
#include "../include/capture/Real_Time_Capture.hpp"

App_Mode app_state;

void set_thread_affinity(std::thread& thread, int core_id){
  cpu_set_t cpu_set;
  CPU_ZERO(&cpu_set);
  CPU_SET(core_id, &cpu_set);
  int res = pthread_setaffinity_np(thread.native_handle(), sizeof(cpu_set_t), &cpu_set);
  if(res != 0) {
    std::cerr << "failed to set thread affinity with error code: " << res << std::endl;
  }
  return;
}

void set_thread_priority(std::thread& thread, int policy, int priority) {
  pthread_t nativeHandle = thread.native_handle();
  struct sched_param param;
  param.sched_priority = priority;
  int ret = pthread_setschedparam(nativeHandle, policy, &param);

  if (ret != 0) {
    std::cerr << "Failed to set thread priority: " << ret << std::endl;
  }
}

int main() {
  cpu_set_t cpu_set;
  CPU_ZERO(&cpu_set);
  CPU_SET(4, &cpu_set);
  if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu_set) != 0) {
    std::cerr << "Failed to set main thread affinity" << std::endl;
  }

  std::cout << "Starting CV thread..." << std::endl;
  std::thread cv_thread(base_loop);
  set_thread_affinity(cv_thread, 2);
  std::cout << "CV thread started on core 1." << std::endl;
  user_interface();
  cv_thread.detach();
  return 0;
}