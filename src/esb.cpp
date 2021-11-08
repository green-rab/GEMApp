/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: esb.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 08.11.2021
 **/

// #include <string>
// using namespace std;

// #include <thread>
// #include <chrono>
// #include <vector>

#include "../include/global.h"
// #include "../include/gema.h"
#include "../include/esb.h"

#include "../include/driver.h"
#include "../include/driver_enum.h"
#include "../include/service.h"


/**
    ## T_ESB :: Constructor ##
**/
T_ESB::T_ESB(int argc, char** argv) {
    ptr_driver  = nullptr;
    ptr_service = nullptr;
}


/**
    ## T_ESB :: Destructor ##
**/
T_ESB::~T_ESB() {
    // wait until last schedules are finished
    while(ptr_service->status_scheduleSync10ms() == true);

    // release SERVICE
    delete ptr_service;
    ptr_service = nullptr;

    // release DRIVER
    delete ptr_driver;
    ptr_driver = nullptr;
}


/**
    ## T_ESB :: run() - Start of execution ##
**/
int T_ESB::run() {
    // ouput info-text at startup
    char infoText[60];
    // getInfoText(infoText, sizeof(infoText));
    callPrintf("%s - %s, version %s\n", APP_SHORTNAME, APP_FULLNAME, APP_VERSION);

    // initialize DRIVER
    ptr_driver = new T_driver();
    ptr_driver->init();

    // initialize SERVICE
    ptr_service = new T_service(ptr_driver);
    int n_times = 0;
    #ifdef TESTMODE
    n_times = 1;
    #endif

    ptr_service->init_scheduleSync10ms(n_times);

    #ifndef TESTMODE
    system("pause");
    #endif

    ptr_service->cancel_scheduleSync10ms();

    #ifdef TESTMODE
    callPrintf("GEMA is terminating... - TESTMODE-session\n");
    #else
    callPrintf("GEMA is terminating...\n");
    #endif

    return 0;
}


/**
    ## T_ESB :: getState_driver() - Return state of instance for 'driver' ##
**/
bool T_ESB::getState_driver() {
    if(!ptr_driver) {
        return false;
    }

    return (ptr_driver->getState() == RUN);
}


/**
    ## T_ESB :: getState_service() - Return state of instance for 'service' ##
**/
bool T_ESB::getState_service() {
    if(!ptr_service) {
        return false;
    }

    return (ptr_service->status_scheduleSync10ms());
}
