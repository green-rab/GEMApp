/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: test_main.cpp
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 12.08.2021
 **/

#include "CppUTest/TestHarness.h"
// #include "CppUTestExt/MockSupport.h"

#include "../include/global.h"

#include "spy/spy_utilsOutput.h"


/**
    ## TESTGROUP tg_main(..) - Test-group (tg) for 'main' including following testcases (tc) ##
**/
TEST_GROUP(tg_main) {
    // CUT code-under-test
    // ...

    // SPYs
    T_spy_utilsOutput *spy_utilsOutput;

    void setup() {
        // init SPYs
        spy_utilsOutput = new T_spy_utilsOutput(1000);

        // init STUBs
        // ...
    
        // init CUT
        // ...

        // set function pointers
        UT_PTR_SET(callPrintf, spy_utilsOutput->printf);
    }

    void teardown() {
        delete spy_utilsOutput;
        spy_utilsOutput = nullptr;

        // mock().clear();
    }
};


/**
    Check compiling works.

    - TEST tc_main_compile(..)
**/
TEST(tg_main, tc_main_compile) {
    CHECK("Failed to compile");
}


/**
    Check util-spies are working for test-execution

    - TEST tc_main_utilsOutput(..)
**/
TEST(tg_main, tc_main_utilsOutput) {
    // init local variables

    // preconditions
    spy_utilsOutput->create(20); // call is optional

    // a.1: output text 'Hello World'
    spy_utilsOutput->printf("Hello World\n");

    // exp.1: check text is read by spy
    STRCMP_EQUAL("Hello World\n", spy_utilsOutput->getBuffer());
}
