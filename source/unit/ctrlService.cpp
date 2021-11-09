/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: ctrlService.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

#include <thread>
#include <chrono>
#include <vector>
using namespace std;

#include "../../include/gemapp.h"

#include "../../include/global.h"
#include "../../include/unit/ctrlService.h"


/**
    ## T_ctrlService :: Constructor ##
**/
T_ctrlService::T_ctrlService(T_ctrlDriver *inst_ctrlDriver) {
    ptr_ctrlDriver = inst_ctrlDriver;

    run_scheduleSync10ms = false;
    stop_scheduleSync10ms = false;

    // call startup methods - fill vectors for ressources and initialize instances
    execute_sync10ms_startup();
}


/**
    ## T_ctrlService :: Destructor ##
**/
T_ctrlService::~T_ctrlService() {
    cancel_scheduleSync10ms();

    // wait for all schedulers are finished
    while(T_ctrlService::run_scheduleSync10ms);

    // call shutdown method - free initialized instances
    execute_sync10ms_shutdown();

    // free vector memory
    vector<e_GEMApp_resGpio>().swap(execute_sync10ms_INPUTS);
    vector<e_GEMApp_resGpio>().swap(execute_sync10ms_OUTPUTS);
}


/**
    ## PRIVATE T_ctrlService :: task_scheduleSync10ms(..) - Task for sync 10 ms ##
**/
void T_ctrlService::task_scheduleSync10ms(uint16_t n_times) {
    // set state variables
    run_scheduleSync10ms = true;
    stop_scheduleSync10ms = false;

    // local variables
    uint16_t count = 0;
    t_GEMApp_data data = {};

    auto timeStart = chrono::steady_clock::now();
    auto timeWait = chrono::milliseconds(10);
    auto timeNext = timeStart + timeWait;

    // execution loop
    while(stop_scheduleSync10ms == false && (count < n_times || n_times == 0)) {
        this_thread::sleep_until(timeNext);
        timeNext += timeWait;

        if(stop_scheduleSync10ms == false) {
            // --> read inputs
            for(auto input = execute_sync10ms_INPUTS.begin(); input != execute_sync10ms_INPUTS.end(); input++) {
                switch(*input) {
                case GPIO_05:
                    data.GPIO_05 = ptr_ctrlDriver->gpioRead(05);
                    break;
                case GPIO_06:
                    data.GPIO_06 = ptr_ctrlDriver->gpioRead(06);
                    break;
                case GPIO_12:
                    data.GPIO_12 = ptr_ctrlDriver->gpioRead(12);
                    break;
                case GPIO_13:
                    data.GPIO_13 = ptr_ctrlDriver->gpioRead(13);
                    break;
                case GPIO_26:
                    data.GPIO_26 = ptr_ctrlDriver->gpioRead(26);
                    break;

                default:
                    break;
                }
            };

            // execute user services
            execute_sync10ms(data);

            // <-- write back outputs
            for(auto output = execute_sync10ms_OUTPUTS.begin(); output != execute_sync10ms_OUTPUTS.end(); output++) {
                switch(*output) {
                case GPIO_05:
                    ptr_ctrlDriver->gpioWrite(05, data.GPIO_05);
                    break;
                case GPIO_06:
                    ptr_ctrlDriver->gpioWrite(06, data.GPIO_06);
                    break;
                case GPIO_12:
                    ptr_ctrlDriver->gpioWrite(12, data.GPIO_12);
                    break;
                case GPIO_13:
                    ptr_ctrlDriver->gpioWrite(13, data.GPIO_13);
                    break;
                case GPIO_26:
                    ptr_ctrlDriver->gpioWrite(26, data.GPIO_26);
                    break;

                default:
                    break;
                }
            };
        }

        if(n_times != 0) count++;
    }

    // set state variables
    run_scheduleSync10ms = false;
}


/**
    ## T_ctrlService :: init_scheduleSync10ms() - Initialize sync 10 ms ##
**/
bool T_ctrlService::init_scheduleSync10ms(uint16_t n_times) {
    callPrintf("Schedule sync 10 ms initialization.. successful\n");

    run_scheduleSync10ms = true;
    thread thread_10ms(&T_ctrlService::task_scheduleSync10ms, this, n_times);
    thread_10ms.detach();

    return true;
}


/**
    ## T_ctrlService :: status_scheduleSync10ms() - Status of sync 10 ms is running ##
**/
bool T_ctrlService::status_scheduleSync10ms() {
    return run_scheduleSync10ms;
}


/**
    ## T_ctrlService :: cancel_scheduleSync10ms() - Cancel sync 10 ms ##
**/
bool T_ctrlService::cancel_scheduleSync10ms() {
    stop_scheduleSync10ms = true;

    return true;
}


/**
    ## T_ctrlService :: init_scheduleSync100ms() - Initialize sync 100 ms ##
**/
bool T_ctrlService::init_scheduleSync100ms() {
    callPrintf("Schedule sync 100 ms initialization.. NOT IMPLEMENTED\n");

    return true;
}
