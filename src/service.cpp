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
T_service::T_service(T_driver *inst_driver) {
    ptr_driver = inst_driver;

    run_scheduleSync10ms = false;
    stop_scheduleSync10ms = false;
}
// bool T_service::run_scheduleSync10ms = false;  // because static
// bool T_service::stop_scheduleSync10ms = false; // because static


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
    // set state variables
    run_scheduleSync10ms = true;
    stop_scheduleSync10ms = false;

    // local variables
    uint16_t count = 0;
    t_GEMA_data data;

    auto const start_time = std::chrono::steady_clock::now();
    auto const wait_time = std::chrono::milliseconds{10};
    auto next_time = start_time + wait_time;

    // execution loop
    while(stop_scheduleSync10ms == false && (count < n_times || n_times == 0)) {
        std::this_thread::sleep_until(next_time);
        next_time += wait_time;

        if(stop_scheduleSync10ms == false) {
            // --> read inputs
            data.GPIO_05 = ptr_driver->gpioRead(05);

            // if(n_times == 2) {
            //     printf("execute -> data: %d\n", data.GPIO_05);
            // }

            // execute user services
            execute_sync10ms(data);

            // <-- write back outputs
            // ...
        }

        if(n_times != 0) count++;
    }

    // set state variables
    run_scheduleSync10ms = false;
}


/**
    ## T_service :: init_scheduleSync10ms() - Initialize sync 10 ms ##
**/
bool T_service::init_scheduleSync10ms(uint16_t n_times) {
    callPrintf("Schedule sync 10 ms initialization.. successful\n");

    run_scheduleSync10ms = true;
    // std::thread t_10ms(T_service::task_scheduleSync10ms, n_times);
    std::thread thread_10ms(&T_service::task_scheduleSync10ms, this, n_times);
    thread_10ms.detach();

    return true;
}


/**
    ## T_service :: cancel_scheduleSync10ms() - Cancel sync 10 ms ##
**/
bool T_service::cancel_scheduleSync10ms() {
    stop_scheduleSync10ms = true;

    return true;
}


/**
    ## T_service :: init_scheduleSync100ms() - Initialize sync 100 ms ##
**/
bool T_service::init_scheduleSync100ms() {
    callPrintf("Schedule sync 100 ms initialization.. successful\n");

    return true;
}
