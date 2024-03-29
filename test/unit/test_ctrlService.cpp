/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: test_ctrlService.cpp
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 18.09.2021
 **/

#include "CppUTest/TestHarness.h"

#include <string>
#include <sstream>
#include <time.h>
using namespace std;

#include "../../include/global.h"
#include "../../include/gemapp.h"
#include "../../include/unit/ctrlService.h"

#include "../../userServices/dummy_service.h"

#include "../spy/spy_ctrlDriver.h"
#include "../spy/spy_userService.h"
#include "../spy/spy_utilsOutput.h"


/**
    ## Extern global variables ##
**/
extern T_dummy_service *dummy_service;


/**
    ## TESTGROUP tg_service(..) - Test-group (tg) for 'control service' including following testcases (tc) ##
**/
TEST_GROUP(tg_service) {
    // CUT code-under-test
    T_ctrlService *cut_ctrlService;

    // SPYs
    T_spy_ctrlDriver  *spy_ctrlDriver;
    T_spy_userService *spy_userService;
    T_spy_utilsOutput *spy_utilsOutput;

    // Save original pointers
    T_dummy_service   *dummy_service_ORG;
 
    void setup() {
        // init SPYs
        spy_ctrlDriver  = new T_spy_ctrlDriver(nullptr);
        spy_userService = new T_spy_userService();
        spy_utilsOutput = new T_spy_utilsOutput(1000);

        // init CUT
        cut_ctrlService = new T_ctrlService(spy_ctrlDriver);

        // set function pointers
        dummy_service_ORG = dummy_service;
        dummy_service     = spy_userService;

        UT_PTR_SET(callPrintf, spy_utilsOutput->printf);
    }

    void teardown() {
        dummy_service = dummy_service_ORG;

        delete cut_ctrlService;
        cut_ctrlService = nullptr;

        delete spy_userService;
        spy_userService = nullptr;

        delete spy_ctrlDriver;
        spy_ctrlDriver = nullptr;

        delete spy_utilsOutput;
        spy_utilsOutput = nullptr;
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

    // a.1: call init function
    ret_init = cut_ctrlService->init_scheduleSync10ms();

    // exp.1: check return and output test
    CHECK_EQUAL(true, ret_init);

    test_stream.str("");
    test_stream.clear();
    test_stream << "Schedule sync 10 ms initialization.. successful\n";
}
TEST(tg_service, tc_service_initScheduleSync100ms) {
    // init local variables
    bool ret_init = false;
    ostringstream test_stream;

    // a.1: call init function
    ret_init = cut_ctrlService->init_scheduleSync100ms();

    // exp.1: check return and output test
    CHECK_EQUAL(true, ret_init);

    test_stream.str("");
    test_stream.clear();
    test_stream << "Schedule sync 100 ms initialization.. successful\n";
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

    // exp.0: check initialization state
    CHECK_EQUAL(0, spy_userService->test_getServiceCalls());

    // a.1: call init function
    ret_init = cut_ctrlService->init_scheduleSync10ms();

    // exp.1: check return and service is called
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(1, spy_userService->test_getServiceCalls());
}
TEST(tg_service, tc_service_sync10ms_execute3times) {
    // init local variables
    bool ret_init = false;

    // exp.0: check initialization state
    CHECK_EQUAL(0, spy_userService->test_getServiceCalls());

    // a.1: call init function
    ret_init = cut_ctrlService->init_scheduleSync10ms(3);

    // exp.1: check return and service is called
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(3, spy_userService->test_getServiceCalls());
}
TEST(tg_service, tc_service_sync10ms_executePeriodically) {
    // init local variables
    bool ret_init = false;
    bool ret_inRange = false;
    float ret_timestamp = 0.0;
    float set_minValue = 0.0;
    float set_maxValue = 0.0;

    // a.1: call initialization
    ret_init = cut_ctrlService->init_scheduleSync10ms(15);

    // exp.1: check called 1, 2, ... , 13 times in timerange of 10 ms
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);

    for(int i=1; i<=13; i++) {
        set_minValue = float(i) * 0.01 - 0.003;
        set_maxValue = float(i) * 0.01 + 0.003;

        ret_timestamp = spy_userService->test_getServiceTimestamp(i);

        ret_inRange = inTolerance(set_minValue, set_maxValue, ret_timestamp);
        if(!ret_inRange) {
            printf("\nERROR ---> Not in range: %f s <> %f s\n", (float(i) * 0.01), ret_timestamp);
        }

        CHECK_EQUAL(true, ret_inRange);
    }
}
TEST(tg_service, tc_service_sync10ms_abort) {
    // init local variables
    bool ret_init = false;
    bool ret_cancel = false;

    // a.1: call init function with parameter 0 (endless loop)
    ret_init = cut_ctrlService->init_scheduleSync10ms(0);

    // exp.1: check return
    CHECK_EQUAL(true, ret_init);

    // a.2: call cancel function at 10rd service call
    while(spy_userService->test_getServiceCalls() < 10);
    ret_cancel = cut_ctrlService->cancel_scheduleSync10ms();

    // exp.2: check service is called and canceled
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_cancel);
    CHECK_EQUAL(10, spy_userService->test_getServiceCalls());
}


/**
    At the beginning of every execution of 'Schedule sync 10 ms' all GPIO-inputs have to be read
    and all GPIO-outputs have to be written back at the end of execution.

    - TEST tc_service_sync10ms_oneInput(..)
    - TEST tc_service_sync10ms_oneOutput(..)
    - TEST tc_service_sync10ms_allGPIOs(..)
    - TEST tc_service_sync10ms_defineGpios(..)
    - TEST tc_service_sync10ms_useInputOnlyIfDefined(..)
    - TEST tc_service_sync10ms_useOutputOnlyIfDefined(..)
**/
TEST(tg_service, tc_service_sync10ms_oneInput) {
    // init local variables
    bool ret_init = false;

    // preconditions
    spy_ctrlDriver->test_setReadValue(05, true);

    // exp.0: check initialization state
    CHECK_EQUAL(false, spy_userService->dataRead.GPIO_05);

    // a.1: call init function for execution of service
    ret_init = cut_ctrlService->init_scheduleSync10ms(1);

    // exp.1: check value is successfully read
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(true, spy_userService->dataRead.GPIO_05);
}
TEST(tg_service, tc_service_sync10ms_oneOutput) {
    // init local variables
    bool ret_init = false;

    // preconditions
    spy_userService->dataWrite.GPIO_12 = true;

    // exp.0: check initialization state
    CHECK_EQUAL(false, spy_ctrlDriver->test_getWriteValue(12));

    // a.1: call init function for execution of service
    ret_init = cut_ctrlService->init_scheduleSync10ms(1);

    // exp.1: check value is successfully written
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(true, spy_ctrlDriver->test_getWriteValue(12));
}
TEST(tg_service, tc_service_sync10ms_allGPIOs) {
    // init local variables
    bool ret_init = false;

    // preconditions
    spy_ctrlDriver->test_setReadValue(05, true);
    spy_ctrlDriver->test_setReadValue(06, true);
    spy_ctrlDriver->test_setReadValue(13, true);
    spy_ctrlDriver->test_setReadValue(26, true);

    // exp.0: check initialization state
    CHECK_EQUAL(false, spy_userService->dataRead.GPIO_05);
    CHECK_EQUAL(false, spy_userService->dataRead.GPIO_06);
    CHECK_EQUAL(false, spy_userService->dataRead.GPIO_13);
    CHECK_EQUAL(false, spy_userService->dataRead.GPIO_26);

    CHECK_EQUAL(false, spy_userService->dataWrite.GPIO_12);

    // a.1: call init function for execution of service
    ret_init = cut_ctrlService->init_scheduleSync10ms(1);

    // exp.1: check values are successfully read
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(true, spy_userService->dataRead.GPIO_05);
    CHECK_EQUAL(true, spy_userService->dataRead.GPIO_06);
    CHECK_EQUAL(true, spy_userService->dataRead.GPIO_13);
    CHECK_EQUAL(true, spy_userService->dataRead.GPIO_26);

    // a.2: reset driver
    spy_ctrlDriver->test_reset();

    // exp.2: check reset state
    CHECK_EQUAL(false, spy_ctrlDriver->test_getWriteValue(12));

    // a.3: call init function again
    spy_userService->dataWrite.GPIO_12 = true;
    ret_init = cut_ctrlService->init_scheduleSync10ms(1);

    // exp.3: check values are successfully written
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(true, spy_ctrlDriver->test_getWriteValue(12));
}
TEST(tg_service, tc_service_sync10ms_defineGpios) {
    // init local variables
    bool ret_init    = false;
    int  cnt_inputs  = 0;
    int  cnt_outputs = 0;

    // exp.0: check inputs and outputs are filled
    CHECK_EQUAL(false, execute_sync10ms_INPUTS.empty());
    CHECK_EQUAL(false, execute_sync10ms_OUTPUTS.empty());

    // a.1: call init function
    cnt_inputs  = execute_sync10ms_INPUTS.size();
    cnt_outputs = execute_sync10ms_OUTPUTS.size();
    ret_init = cut_ctrlService->init_scheduleSync10ms(3);

    // exp.1: check size of vector is same as at startup
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(cnt_inputs,  execute_sync10ms_INPUTS.size());
    CHECK_EQUAL(cnt_outputs, execute_sync10ms_OUTPUTS.size());
}
TEST(tg_service, tc_service_sync10ms_useInputOnlyIfDefined) {
    // init local variables
    bool ret_init = false;

    // preconditions
    std::vector<e_GEMApp_resGpio>().swap(execute_sync10ms_INPUTS);
    execute_sync10ms_INPUTS.push_back(GPIO_05);
    spy_ctrlDriver->test_setReadValue(05, true);
    spy_ctrlDriver->test_setReadValue(06, true);

    // exp.0: check initialization state
    CHECK_EQUAL(false, spy_userService->dataRead.GPIO_05);
    CHECK_EQUAL(false, spy_userService->dataRead.GPIO_06);

    // a.1: call init function for execution of service
    ret_init = cut_ctrlService->init_scheduleSync10ms(1);

    // exp.1: check only one specified input is read
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(true, spy_userService->dataRead.GPIO_05);
    CHECK_EQUAL(false, spy_userService->dataRead.GPIO_06);

    // a.2: call init function again with second input
    spy_userService->test_reset();
    execute_sync10ms_INPUTS.push_back(GPIO_06);
    ret_init = cut_ctrlService->init_scheduleSync10ms(1);

    // exp.2: check both specified inputs are read
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(true, spy_userService->dataRead.GPIO_05);
    CHECK_EQUAL(true, spy_userService->dataRead.GPIO_06);
}
TEST(tg_service, tc_service_sync10ms_useOutputOnlyIfDefined) {
    // init local variables
    bool ret_init = false;

    // preconditions
    std::vector<e_GEMApp_resGpio>().swap(execute_sync10ms_OUTPUTS);
    execute_sync10ms_OUTPUTS.push_back(GPIO_12);
    spy_userService->dataWrite.GPIO_12 = true;
    spy_userService->dataWrite.GPIO_13 = true;

    // exp.0: check initialization state
    CHECK_EQUAL(false, spy_ctrlDriver->test_getWriteValue(12));
    CHECK_EQUAL(false, spy_ctrlDriver->test_getWriteValue(13));

    // a.1: call init function for execution of service
    ret_init = cut_ctrlService->init_scheduleSync10ms(1);

    // exp.1: check only one specified output is written
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(true, spy_ctrlDriver->test_getWriteValue(12));
    CHECK_EQUAL(false, spy_ctrlDriver->test_getWriteValue(13));

    // a.2: call init function again with second output
    spy_userService->test_reset();
    execute_sync10ms_OUTPUTS.push_back(GPIO_13);
    spy_userService->dataWrite.GPIO_12 = true;
    spy_userService->dataWrite.GPIO_13 = true;
    ret_init = cut_ctrlService->init_scheduleSync10ms(1);

    // exp.2: check both specified outputs are written
    while(cut_ctrlService->status_scheduleSync10ms() == true);
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(true, spy_ctrlDriver->test_getWriteValue(12));
    CHECK_EQUAL(true, spy_ctrlDriver->test_getWriteValue(13));
}
