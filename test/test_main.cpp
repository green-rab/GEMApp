/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: test_main.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 12.08.2021
 **/

#include "CppUTest/TestHarness.h"
// #include "CppUTestExt/MockSupport.h"

#include "../include/main.h"
#include "../include/driver_enum.h"
#include "../include/global.h"

#include "spy/spy_driver.h"
#include "spy/spy_utilsOutput.h"

extern T_enum_driverState driverState;


/**
    ## TESTGROUP tg_main(..) - Test-group (tg) for 'main' including following testcases (tc) ##
**/
TEST_GROUP(tg_main) {
    // CUT code-under-test
    // T_service *cut_main;

    // SPYs
    T_spy_driver      *spy_driver;
    T_spy_utilsOutput *spy_utilsOutput;

    void setup() {
        // init SPYs
        spy_driver      = new T_spy_driver();
        spy_utilsOutput = new T_spy_utilsOutput(1000);

        // init STUBs
    
        // init CUT
        // ... tbd cut_service = new T_service(spy_driver);

        // set function pointers
        UT_PTR_SET(callPrintf, spy_utilsOutput->printf);
    }

    void teardown() {
        // delete cut_service;
        // cut_service = NULL;

        delete spy_driver;
        spy_driver = NULL;

        delete spy_utilsOutput;
        spy_utilsOutput = NULL;

        // mock().clear();
    }
};


/**
    Check compiling works a welcome message is printed if application is started.

    - TEST tc_main_compile(..)
    - TEST tc_main_utilsOutputPrintf(..)
    - TEST tc_main_infotext(..)

**/
TEST(tg_main, tc_main_compile) {
    CHECK("Failed to compile");
}
TEST(tg_main, tc_main_utilsOutputPrintf) {
    // init local variables

    // preconditions
    // spy_utilsOutput->create(20); - optional

    // a.1: output text 'Hello World'
    spy_utilsOutput->printf("Hello World\n");

    // exp.1: check text is read by spy
    STRCMP_EQUAL("Hello World\n", spy_utilsOutput->getBuffer());
}
TEST(tg_main, tc_main_infotext) {
    const char exp_text[] = "GEMA - Generic Embedded Main Application, version 0.0.1\n";

    char text[60];
    getInfoText(text, sizeof(text));

    STRCMP_EQUAL(exp_text, text);
}


/**
    ## TEST tc_main_driverInitialized(..) - Check driver-layer is initialized successfully ##
**/
TEST(tg_main, tc_main_driverInitialized) {
    int retVal = main_func(0, NULL);

    CHECK_EQUAL(0, retVal);
    // CHECK_EQUAL(RUN, driverState);
}
