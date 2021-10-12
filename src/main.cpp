/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: main.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 11.08.2021
 **/

#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestRegistry.h"

#include "../include/global.h"
#include "../include/main.h"

#include "../include/driver.h"
#include "../include/service.h"

#include <stdio.h>
#include <string.h>


/**
    ## Global properties ##
**/
T_driver driver = T_driver();
// T_driver *ptr_driver = NULL;
T_enum_driverState driverState;

// T_service service = T_service();
// T_service *ptr_service = NULL;


/**
    ## main(..) - Entry point of GEMA ##
**/
int main(int argc, char** argv) {
    int retValue = main_func(argc, argv);

    // cpputest - SetPointerPlugin
    #ifdef TESTMODE
    TestRegistry* r = TestRegistry::getCurrentRegistry();
    SetPointerPlugin ps("PointerStore");
    r->installPlugin(&ps);
    #endif

    // return successful, application terminated
    #ifdef TESTMODE
    callPrintf("GEMA terminated - TESTMODE-session\n");
    return CommandLineTestRunner::RunAllTests(argc, argv);
    #endif

    callPrintf("GEMA terminated\n");
    return retValue;
}
int main_func(int argc, char** argv) {
    // ouput info-text at startup
    char infoText[60];
    getInfoText(infoText, sizeof(infoText));
    callPrintf("%s", infoText);

    // initialize DRIVER
    // ptr_driver = new T_driver();
    driver.init();
    driverState = driver.getState();

    // initialize SERVICE
    // ...
    // service.init_scheduleSync10ms();
    // ptr_service = new T_service(ptr_driver);

    // while(T_service::run_scheduleSync10ms == true);

    // delete ptr_service;
    // ptr_service = NULL;

    // delete ptr_driver;
    // ptr_driver = NULL;

    return 0;
}


/**
    ## getInfoText(..) - Generate and return info-text for startup ##
**/
void getInfoText(char* infoText, int buffersize) {
    char tmp_infoText[100];
    sprintf(tmp_infoText, "%s - %s, version %s\n", APP_SHORTNAME, APP_FULLNAME, APP_VERSION);
    
    strncpy(infoText, tmp_infoText, buffersize-1);
    infoText[buffersize-1] = '\0';
}
