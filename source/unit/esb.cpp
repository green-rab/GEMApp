/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: esb.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 08.11.2021
 **/

#include "../../include/unit/drvGpio.h"
#include "../../include/unit/ctrlDriver.h"
#include "../../include/unit/ctrlService.h"

#include "../../include/global.h"
#include "../../include/unit/esb.h"


/**
    ## T_ESB :: Constructor ##
**/
T_ESB::T_ESB(int argc, char** argv) {
    ptr_drvGpio     = nullptr;

    ptr_ctrlDriver  = nullptr;
    ptr_ctrlService = nullptr;
}


/**
    ## T_ESB :: Destructor ##
**/
T_ESB::~T_ESB() {
    // wait until last schedules are finished
    while(ptr_ctrlService->status_scheduleSync10ms() == true);

    // release CONTROL SERVICE
    delete ptr_ctrlService;
    ptr_ctrlService = nullptr;

    // release CONTROL DRIVER
    delete ptr_ctrlDriver;
    ptr_ctrlDriver = nullptr;

    // release DRIVER GPIO
    delete ptr_drvGpio;
    ptr_drvGpio = nullptr;
}


/**
    ## T_ESB :: run() - Start of execution ##
**/
int T_ESB::run() {
    // ouput info-text at startup
    char infoText[60];
    // getInfoText(infoText, sizeof(infoText));
    callPrintf("%s - %s, version %s\n", APP_SHORTNAME, APP_FULLNAME, APP_VERSION);

    // initialize DRIVER GPIO
    ptr_drvGpio = new T_drvGpio();

    // initialize CONTROL DRIVER
    ptr_ctrlDriver = new T_ctrlDriver(ptr_drvGpio);
    ptr_ctrlDriver->init();

    // initialize COTNTROL SERVICE
    ptr_ctrlService = new T_ctrlService(ptr_ctrlDriver);
    int n_times = 0;
    #ifdef TESTMODE
    n_times = 1;
    #endif
    ptr_ctrlService->init_scheduleSync10ms(n_times);

    #ifndef TESTMODE
    printf("Press <CTRL> <C> to cancel (has to be reworked) ...");
    while(1);
    #endif

    ptr_ctrlService->cancel_scheduleSync10ms();

    #ifdef TESTMODE
    callPrintf("%s is terminating... - TESTMODE-session\n", APP_SHORTNAME);
    #else
    callPrintf("%s is terminating...\n", APP_SHORTNAME);
    #endif

    return 0;
}


/**
    ## T_ESB :: getState_ctrlDriver() - Return state of instance for 'control driver' ##
**/
bool T_ESB::getState_ctrlDriver() {
    if(!ptr_ctrlDriver) {
        return false;
    }

    return (ptr_ctrlDriver->getState() == RUN);
}


/**
    ## T_ESB :: getState_ctrlService() - Return state of instance for 'control service' ##
**/
bool T_ESB::getState_ctrlService() {
    if(!ptr_ctrlService) {
        return false;
    }

    return (ptr_ctrlService->status_scheduleSync10ms());
}
