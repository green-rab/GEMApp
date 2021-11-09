/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: test_esb.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 08.11.2021
 **/

#include "CppUTest/TestHarness.h"
// #include "CppUTestExt/MockSupport.h"

#include <string>
#include <sstream>
using namespace std;

#include "../../include/global.h"
#include "../../include/unit/ctrlDriver.h"
#include "../../include/unit/esb.h"

#include "../spy/spy_utilsOutput.h"


/**
    ## TESTGROUP tg_esb(..) - Test-group (tg) for 'esb' including following testcases (tc) ##
**/
TEST_GROUP(tg_esb) {
    // CUT code-under-test
    T_ESB *cut_esb;

    // SPYs
    T_spy_utilsOutput *spy_utilsOutput;

    void setup() {
        // init SPYs
        spy_utilsOutput = new T_spy_utilsOutput(1000);

        // init STUBs
        // ...
    
        // init CUT
        cut_esb = new T_ESB(1, NULL);

        // set function pointers
        UT_PTR_SET(callPrintf, spy_utilsOutput->printf);
    }

    void teardown() {
        delete cut_esb;
        cut_esb = nullptr;

        delete spy_utilsOutput;
        spy_utilsOutput = nullptr;

        // mock().clear();
    }
};


/**
    Check info messages on startup and teardown.

    - TEST tc_esb_msgWelcome(..)
    - TEST tc_esb_msgGoodbye(..)
**/
TEST(tg_esb, tc_esb_msgWelcome) {
    // init local variables
    int ret_run = -1;
    ostringstream test_stream;

    // preconditions
    test_stream.str("");
    test_stream.clear();
    test_stream << APP_SHORTNAME << " - " << APP_FULLNAME << ", version " << APP_VERSION << endl;

    // a.1: call run for initialization
    ret_run = cut_esb->run();

    // exp.1: check welcome message
    CHECK_EQUAL(0, ret_run);
    // STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
    CHECK_EQUAL(true, spy_utilsOutput->checkBuffer(test_stream.str().c_str()));
}
TEST(tg_esb, tc_esb_msgGoodbye) {
    // init local variables
    int ret_run = -1;
    ostringstream test_stream;

    // preconditions
    test_stream.str("");
    test_stream.clear();
    test_stream << APP_SHORTNAME << " is terminating... - TESTMODE-session" << endl;

    // a.1: call run for initialization
    ret_run = cut_esb->run();

    // exp.1: check goodbye message
    CHECK_EQUAL(0, ret_run);
    // STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
    CHECK_EQUAL(true, spy_utilsOutput->checkBuffer(test_stream.str().c_str()));
}


/**
    Initialize all layers and objects.

    - TEST tc_esb_initDriver(..)
    - TEST tc_esb_initService(..)
**/
TEST(tg_esb, tc_esb_initDriver) {
    // init local variables
    int ret_run = -1;

    // preconditions
    CHECK_EQUAL(false, cut_esb->getState_ctrlDriver());

    // a.1: call run for initialization
    ret_run = cut_esb->run();

    // exp.1: check driver state
    CHECK_EQUAL(0, ret_run);
    CHECK_EQUAL(true, cut_esb->getState_ctrlDriver());
}
TEST(tg_esb, tc_esb_initService) {
    // init local variables
    int ret_run = -1;

    // preconditions
    CHECK_EQUAL(false, cut_esb->getState_ctrlService());

    // a.1: call run for initialization
    ret_run = cut_esb->run();

    // exp.1: check driver state
    CHECK_EQUAL(0, ret_run);
    CHECK_EQUAL(true, cut_esb->getState_ctrlService());
}
