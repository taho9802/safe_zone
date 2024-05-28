#include <iostream>
#include <thread>
#include <pthread.h>
#include "../include/user_interface/User_Interface.hpp"
#include "../include/utils/App_State.hpp"
#include "../include/capture/Real_Time_Capture.hpp"

App_Mode app_state;

void setThreadPriority(std::thread& thread, int policy, int priority) {
    pthread_t nativeHandle = thread.native_handle();
    struct sched_param param;
    param.sched_priority = priority;

    if (pthread_setschedparam(nativeHandle, policy, &param)) {
        std::cerr << "Failed to set thread priority" << std::endl;
    }
}

int main() {
    std::cout << "Starting user interface thread...";
    std::thread ui_thread(user_interface);
    std::cout << "  Done." << std::endl;

    std::cout << "Starting cv loop thread...";
    std::thread cv_thread(base_loop);
    std::cout << "  Done." << std::endl;

    // Set the cv_thread priority to highest
    int policy = SCHED_FIFO;
    int priority = sched_get_priority_max(policy);
    setThreadPriority(cv_thread, policy, priority);

    ui_thread.join();
    cv_thread.join();

    return 0;
}