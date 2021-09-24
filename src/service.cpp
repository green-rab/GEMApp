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

#include "../include/global.h"
#include "../include/gema.h"
#include "../include/service.h"

#include <time.h>


/**
    ## T_service :: Constructor ##
**/
T_service::T_service() {
}


/**
    ## T_service :: Destructor ##
**/
T_service::~T_service() {
}


/**
    ## T_service :: init_scheduleSync10ms() - Initialize sync 10 ms ##
**/
bool T_service::init_scheduleSync10ms() {
    callPrintf("Schedule sync 10 ms initialization.. successful\n");

    struct timespec t_sleep_10ms = {0, 10000000L};  //10 ms
    int cnt = 0;

    while(cnt < 15) {
        execute_sync10ms();

        nanosleep(&t_sleep_10ms, NULL);
        cnt++;
    };

    return true;
}


/**
    ## T_service :: init_scheduleSync100ms() - Initialize sync 100 ms ##
**/
bool T_service::init_scheduleSync100ms() {
    callPrintf("Schedule sync 100 ms initialization.. successful\n");

    return true;
}
