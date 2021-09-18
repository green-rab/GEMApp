/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: test_service.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

#include "CppUTest/TestHarness.h"
// #include "CppUTestExt/MockSupport.h"

#include <string>
#include <sstream>
using namespace std;

#include "../include/service.h"
#include "../include/global.h"

#include "spy/spy_utilsOutput.h"
#include "spy/spy_userServices.h"


/**
    ## TESTGROUP tg_service(..) - Test-group (tg) for 'service' including following testcases (tc) ##
**/
TEST_GROUP(tg_service) {
    // CUT code-under-test
    T_service *cut_service;

    // SPYs
    T_spy_utilsOutput  *spy_utilsOutput;
    T_spy_userServices *spy_userServices;

    void setup() {
        // init SPYs
        spy_utilsOutput  = new T_spy_utilsOutput(1000);
        spy_userServices = new T_spy_userServices();

        // init STUBs
    
        // init CUT
        cut_service = new T_service();

        // set function pointers
        // cut_service->dummy_service01_raw = spy_userServices->userService_01;
        // cut_service->dummy_service02_raw = spy_userServices->userService_02;
        // cut_driver->res_gpio = spy_gpio;

        UT_PTR_SET(callPrintf, spy_utilsOutput->printf);
    }

    void teardown() {
        delete cut_service;
        cut_service = NULL;

        delete spy_userServices;
        spy_userServices = NULL;

        delete spy_utilsOutput;
        spy_utilsOutput = NULL;

        // mock().clear();
    }

    // static void userService_01() { spy_userServices->userService_01(); };
    // static void userService_02() { spy_userServices->userService_02(); };
};


/**
    Every initialization function for sheduling can be called and is executed successful (in normal way).

    - TEST tc_service_initScheduleSync10ms(..)
    - TEST tc_service_initScheduleSync100ms(..)
**/
TEST(tg_service, tc_service_initScheduleSync10ms) {
    // init local variables
    bool ret_init = false;
    ostringstream test_stream;

    // preconditions

    // a.1: call init function
    ret_init = cut_service->init_scheduleSync10ms();

    // exp.1: check return and output test
    CHECK_EQUAL(true, ret_init);

    test_stream.str("");
    test_stream.clear();
    test_stream << "Schedule sync 10 ms initialization.. successful\n";
    STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
}
TEST(tg_service, tc_service_initScheduleSync100ms) {
    // init local variables
    bool ret_init = false;
    ostringstream test_stream;

    // preconditions

    // a.1: call init function
    ret_init = cut_service->init_scheduleSync100ms();

    // exp.1: check return and output test
    CHECK_EQUAL(true, ret_init);

    test_stream.str("");
    test_stream.clear();
    test_stream << "Schedule sync 100 ms initialization.. successful\n";
    STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
}


/**
    If 'Schedule sync 10 ms' is intialized execution of user-routines have to be done every 10 ms
    until an abort is called.

    - TEST tc_service_sync10ms_executeOnce(..)
    - TEST tc_service_sync10ms_executePeriodically(..)
    - TEST tc_service_sync10ms_abort(..)
**/
TEST(tg_service, tc_service_sync10ms_executeOnce) {
    // init local variables
    bool ret_init = false;

    // preconditions

    // exp.0: check initialization state
    CHECK_EQUAL(0, spy_userServices->test_getServiceCalls(1));

    // a.1: call init function
    ret_init = cut_service->init_scheduleSync10ms();

    // exp.1: check return and service is called
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(1, spy_userServices->test_getServiceCalls(1));
}
TEST(tg_service, tc_service_sync10ms_executePeriodically) {
}
TEST(tg_service, tc_service_sync10ms_abort) {
}


/**
    At the beginning of every execution all GPIO-inputs have to be read and all GPIO-outputs
    have to be written back at the end of execution.

    - TEST tc_service_sync10ms_GPIO(..)
    - TEST tc_service_sync100ms_GPIO(..)
**/
