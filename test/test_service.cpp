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
#include <time.h>

#include "../include/service.h"
#include "../include/global.h"

#include "spy/spy_utilsOutput.h"

#include "../service/dummy_service01.h"


/**
    ## Use dummy-services as spy for tests ##
**/
extern T_dummy_service01 dummy_service01;


/**
    ## TESTGROUP tg_service(..) - Test-group (tg) for 'service' including following testcases (tc) ##
**/
TEST_GROUP(tg_service) {
    // CUT code-under-test
    T_service *cut_service;

    // SPYs
    T_spy_utilsOutput *spy_utilsOutput;

    void setup() {
        // init SPYs
        spy_utilsOutput  = new T_spy_utilsOutput(1000);

        // init STUBs

        // reset DUMMYs
        dummy_service01.test_reset();
    
        // init CUT
        cut_service = new T_service();

        // set function pointers
        UT_PTR_SET(callPrintf, spy_utilsOutput->printf);
    }

    void teardown() {
        delete cut_service;
        cut_service = NULL;

        delete spy_utilsOutput;
        spy_utilsOutput = NULL;

        // mock().clear();
    }

    bool inTolerance(float minValue, float maxValue, float value) {
        if(value >= minValue && value <= maxValue) {
            return true;
        }

        return false;
    }
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
    - TEST tc_service_sync10ms_execute3times(..)
    - TEST tc_service_sync10ms_executePeriodically(..)
    - TEST tc_service_sync10ms_abort(..)
**/
TEST(tg_service, tc_service_sync10ms_executeOnce) {
    // init local variables
    bool ret_init = false;

    // preconditions

    // exp.0: check initialization state
    CHECK_EQUAL(0, dummy_service01.test_getServiceCalls());

    // a.1: call init function
    ret_init = cut_service->init_scheduleSync10ms();

    // exp.1: check return and service is called
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(1, dummy_service01.test_getServiceCalls());
}
TEST(tg_service, tc_service_sync10ms_execute3times) {
    // init local variables
    bool ret_init = false;

    // preconditions

    // exp.0: check initialization state
    CHECK_EQUAL(0, dummy_service01.test_getServiceCalls());

    // a.1: call init function
    ret_init = cut_service->init_scheduleSync10ms(3);

    // exp.1: check return and service is called
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(3, dummy_service01.test_getServiceCalls());
}
TEST(tg_service, tc_service_sync10ms_executePeriodically) {
    // init local variables
    bool ret_init = false;
    bool ret_inRange = false;
    float ret_timestamp = 0.0;
    float set_minValue = 0.0;
    float set_maxValue = 0.0;

    // preconditions

    // a.1: call initialization
    ret_init = cut_service->init_scheduleSync10ms(15);

    // exp.1: check called 1, 2, ... , 13 times in timerange of 10 ms
    CHECK_EQUAL(true, ret_init);

    for(int i=1; i<=13; i++) {
        set_minValue = float(i) * 0.01 - 0.001;
        set_maxValue = float(i) * 0.01 + 0.001;

        ret_timestamp = dummy_service01.test_getServiceTimestamp(i);

        ret_inRange = inTolerance(set_minValue, set_maxValue, ret_timestamp);
        // if(!ret_inRange) {
            printf("\nERROR ---> Not in range: %f s <> %f s\n", (float(i) * 0.01), ret_timestamp);
        // }

        // CHECK_EQUAL(true, ret_inRange);
    }
}
TEST(tg_service, tc_service_sync10ms_abort) {
}


/**
    At the beginning of every execution all GPIO-inputs have to be read and all GPIO-outputs
    have to be written back at the end of execution.

    - TEST tc_service_sync10ms_GPIO(..)
    - TEST tc_service_sync100ms_GPIO(..)
**/