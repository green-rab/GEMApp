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

#include <stdio.h>
#include <string.h>


/**
    ## Global properties ##
**/
T_driver driver;
T_enum_driverState driverState;


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
    driver.init();
    driverState = driver.getState();

    // initialize SERVICE
    // ...

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
