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
#include <chrono>

#include "../include/global.h"
#include "../include/gema.h"
#include "../include/service.h"


/**
    ## T_service :: Constructor ##
**/
T_service::T_service() {
}
bool T_service::run_scheduleSync10ms = false;  // because static
bool T_service::stop_scheduleSync10ms = false; // because static


/**
    ## T_service :: Destructor ##
**/
T_service::~T_service() {
    cancel_scheduleSync10ms();

    while(T_service::run_scheduleSync10ms);
}


/**
    ## PRIVATE T_service :: task_scheduleSync10ms(..) - Task for sync 10 ms ##
**/
void T_service::task_scheduleSync10ms(uint16_t n_times) {
    // static class variables
    T_service::run_scheduleSync10ms = true;
    T_service::stop_scheduleSync10ms = false;

    // local variables
    uint16_t count = 0;
    auto const start_time = std::chrono::steady_clock::now();
    auto const wait_time = std::chrono::milliseconds{10};
    auto next_time = start_time + wait_time;

    // execution loop
    while(T_service::stop_scheduleSync10ms == false && (count < n_times || n_times == 0)) {
        std::this_thread::sleep_until(next_time);
        next_time += wait_time;

        if(stop_scheduleSync10ms == false) {
            // --> todo: read inputs
            execute_sync10ms();
            // <-- todo: write back outputs
        }

        if(n_times != 0) count++;
    }

    T_service::run_scheduleSync10ms = false;
}


/**
    ## T_service :: init_scheduleSync10ms() - Initialize sync 10 ms ##
**/
bool T_service::init_scheduleSync10ms(uint16_t n_times) {
    callPrintf("Schedule sync 10 ms initialization.. successful\n");

    T_service::run_scheduleSync10ms = true;
    std::thread t_10ms(T_service::task_scheduleSync10ms, n_times);
    t_10ms.detach();

    return true;
}


/**
    ## T_service :: cancel_scheduleSync10ms() - Cancel sync 10 ms ##
**/
bool T_service::cancel_scheduleSync10ms() {
    T_service::stop_scheduleSync10ms = true;

    return true;
}


/**
    ## T_service :: init_scheduleSync100ms() - Initialize sync 100 ms ##
**/
bool T_service::init_scheduleSync100ms() {
    callPrintf("Schedule sync 100 ms initialization.. successful\n");

    return true;
}
