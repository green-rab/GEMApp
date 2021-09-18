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

    execute_sync10ms();

    return true;
}


/**
    ## T_service :: init_scheduleSync100ms() - Initialize sync 100 ms ##
**/
bool T_service::init_scheduleSync100ms() {
    callPrintf("Schedule sync 100 ms initialization.. successful\n");

    return true;
}
