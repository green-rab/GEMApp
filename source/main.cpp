/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: main.cpp
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 11.08.2021
 **/

#ifdef TESTMODE
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestRegistry.h"
#endif

#include "../include/global.h"
#include "../include/unit/esb.h"


/**
    ## main(..) - Entry point of GEMApp ##
**/
int main(int argc, char** argv) {
    T_ESB esb = T_ESB(argc, argv);

    // call esb to run application
    int ret = esb.run();

    // cpputest - restore pointers by SetPointerPlugin
    #ifdef TESTMODE
    TestRegistry* r = TestRegistry::getCurrentRegistry();
    SetPointerPlugin ps("PointerStore");
    r->installPlugin(&ps);
    #endif

    // cpputest - exit by TestRunner
    #ifdef TESTMODE
    return CommandLineTestRunner::RunAllTests(argc, argv);
    #endif

    return ret;
}
