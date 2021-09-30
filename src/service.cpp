/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: service.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

// #include <string>
// using namespace std;

#include <time.h>
#include <thread>

#include "../include/global.h"
#include "../include/gema.h"
#include "../include/service.h"



#include <stdio.h>
#include <chrono>
#include <functional>

/**
    ## T_service :: Constructor ##
**/
T_service::T_service() {
    running_scheduleSync10ms = false;
}


/**
    ## T_service :: Destructor ##
**/
T_service::~T_service() {
}


/**
    ## PRIVATE T_service :: task_scheduleSync10ms() - Thread for sync 10 ms ##
**/
void T_service::task_scheduleSync10ms() {
    // struct timespec t_sleep_10ms = {0, 10000000L};  //10 ms
    // static sint cnt = 0;

    // cnt++;

    // while(cnt < 15) {
        execute_sync10ms();

    //     nanosleep(&t_sleep_10ms, NULL);
    //     cnt++;

        // printf("execute_sync10ms -> %d\n", cnt);
    // };
}


void T_service::timer_start(std::function<void(void)> func, unsigned int interval, uint16_t n_times, bool &status) {
    std::thread([func, interval, n_times, &status] {
    // std::thread timer1(func, interval, n_times, &status);
        auto timeStart = std::chrono::steady_clock::now();
        func();

        for(uint16_t i=1; i<n_times; i++) {
            auto timeGo = timeStart + std::chrono::milliseconds(interval * i);
            std::this_thread::sleep_until(timeGo);

            func();
        }

        status = false;
    }).detach();
}


/**
    ## T_service :: init_scheduleSync10ms() - Initialize sync 10 ms ##
**/
bool T_service::init_scheduleSync10ms(uint16_t n_times) {
    callPrintf("Schedule sync 10 ms initialization.. successful\n");

    running_scheduleSync10ms = true;
    timer_start(task_scheduleSync10ms, 10, n_times, running_scheduleSync10ms);
    // for(uint16_t i=0; i<n_times; i++) {
    //     thread_scheduleSync10ms();

    //     struct timespec t_sleep_10ms = {0, 10000000L};  //10 ms
    //     nanosleep(&t_sleep_10ms, NULL);
    // }

    while(running_scheduleSync10ms);

    return true;
}


/**
    ## T_service :: init_scheduleSync100ms() - Initialize sync 100 ms ##
**/
bool T_service::init_scheduleSync100ms() {
    callPrintf("Schedule sync 100 ms initialization.. successful\n");

    return true;
}
