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

#include <thread>
#include <chrono>
#include <vector>

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

    // call startup methods - fill vectors for ressources
    execute_sync10ms_startup(); 
}
// bool T_service::run_scheduleSync10ms = false;  // because static
// bool T_service::stop_scheduleSync10ms = false; // because static


/**
    ## T_service :: Destructor ##
**/
T_service::~T_service() {
    cancel_scheduleSync10ms();

    while(T_service::run_scheduleSync10ms);

    // free vector memory
    std::vector<e_GEMA_resGpio>().swap(execute_sync10ms_INPUTS);
    std::vector<e_GEMA_resGpio>().swap(execute_sync10ms_OUTPUTS);
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

    auto timeStart = std::chrono::steady_clock::now();
    auto timeWait = std::chrono::milliseconds(10);
    auto timeNext = timeStart + timeWait;

    // execution loop
    while(stop_scheduleSync10ms == false && (count < n_times || n_times == 0)) {
        std::this_thread::sleep_until(timeNext);
        timeNext += timeWait;

        if(stop_scheduleSync10ms == false) {
            // --> read inputs
            for(auto input = execute_sync10ms_INPUTS.begin(); input != execute_sync10ms_INPUTS.end(); input++) {
                switch(*input) {
                case GPIO_05:
                    data.GPIO_05 = ptr_driver->gpioRead(05);
                    break;
                case GPIO_06:
                    data.GPIO_06 = ptr_driver->gpioRead(06);
                    break;
                case GPIO_12:
                    data.GPIO_12 = ptr_driver->gpioRead(12);
                    break;
                case GPIO_13:
                    data.GPIO_13 = ptr_driver->gpioRead(13);
                    break;
                case GPIO_26:
                    data.GPIO_26 = ptr_driver->gpioRead(26);
                    break;

                default:
                    break;
                }
            };
            // data.GPIO_05 = ptr_driver->gpioRead(05);
            // data.GPIO_06 = ptr_driver->gpioRead(06);
            // // data.GPIO_12 = ptr_driver->gpioRead(12);
            // data.GPIO_13 = ptr_driver->gpioRead(13);
            // data.GPIO_26 = ptr_driver->gpioRead(26);

            // execute user services
            execute_sync10ms(data);

            // <-- write back outputs
            // ptr_driver->gpioWrite(05, data.GPIO_05);
            // ptr_driver->gpioWrite(06, data.GPIO_06);
            ptr_driver->gpioWrite(12, data.GPIO_12);
            // ptr_driver->gpioWrite(13, data.GPIO_13);
            // ptr_driver->gpioWrite(26, data.GPIO_26);
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
    std::thread thread_10ms(&T_service::task_scheduleSync10ms, this, n_times);
    thread_10ms.detach();

    return true;
}


/**
    ## T_service :: status_scheduleSync10ms() - Status of sync 10 ms is running ##
**/
bool T_service::status_scheduleSync10ms() {
    return run_scheduleSync10ms;
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
