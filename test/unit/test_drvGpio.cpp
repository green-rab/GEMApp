/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: test_drvGpio.cpp
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 12.08.2021
 **/

#include "CppUTest/TestHarness.h"

#include <string>
#include <sstream>
using namespace std;

#include "../../include/global.h"
#include "../../include/unit/drvGpio.h"


/**
    ## TESTGROUP tg_gpio(..) - Test-group (tg) for 'driver gpio' including following testcases (tc) ##
**/
TEST_GROUP(tg_res_gpio) {
    // CUT code-under-test
    T_drvGpio *cut_drvGpio;

    void setup() {
        // init CUT
        cut_drvGpio = new T_drvGpio();
    }

    void teardown() {
        delete cut_drvGpio;
        cut_drvGpio = nullptr;

        // mock().clear();
    }
};


/**
    Access gpios by writing to linux driver-interface at path: '/sys/class/gpio/export'.

    Gpio has to be initialized by its given direction. Init-value has always to be '0'.

    - TEST tc_res_gpio_initAsInput(..)
    - TEST tc_res_gpio_initAsOutput(..)
**/
TEST(tg_res_gpio, tc_res_gpio_initAsInput) {
    // init local variables
    int test_gpio = 05;
    bool ret_state = false;

    // preconditions

    // a.1: initialize gpio as input
    ret_state = cut_drvGpio->init(test_gpio, false);

    // exp.1: check return value
    CHECK(ret_state);
}
TEST(tg_res_gpio, tc_res_gpio_initAsOutput) {
    // init local variables
    int test_gpio = 05;
    bool ret_state = false;

    // preconditions

    // a.1: initialize gpio as output
    ret_state = cut_drvGpio->init(test_gpio, true);

    // exp.1: check return value
    CHECK(ret_state);
}


/**
    Gpio has to be deintialized.

    - TEST tc_res_gpio_deinit(..)
**/
TEST(tg_res_gpio, tc_res_gpio_deinit) {
    // init local variables
    int test_gpio = 05;
    bool ret_state = false;

    // preconditions

    // a.1: deinitialize gpio
    ret_state = cut_drvGpio->deinit(test_gpio);

    // exp.1: check return value
    CHECK(ret_state);
}


/**
    Get state values of gpiogpio.

    - TEST tc_res_gpio_getStateInit(..)
    - TEST tc_res_gpio_getStateDirection(..)
**/
TEST(tg_res_gpio, tc_res_gpio_getStateInit) {
    // init local variables
    int test_gpio = 05;
    bool ret_state = false;
    bool ret_valInit = true;

    // preconditions

    // a.1: get state of initialization
    ret_state = cut_drvGpio->getStateInit(test_gpio, ret_valInit);

    // exp.1: check state and return value
    CHECK(ret_state);
    CHECK_FALSE(ret_valInit);
}
TEST(tg_res_gpio, tc_res_gpio_getStateDirection) {
    // init local variables
    int test_gpio = 05;
    bool ret_state = false;
    bool ret_valDirection = true;

    // preconditions

    // a.1: get state of direction
    ret_state = cut_drvGpio->getStateDirection(test_gpio, ret_valDirection);

    // exp.1: check state and return value
    CHECK(ret_state);
    CHECK_FALSE(ret_valDirection);
}


/**
    Read gpio value (configured as input). By default return '0'.

    - TEST tc_res_gpio_read(..)
**/
TEST(tg_res_gpio, tc_res_gpio_read) {
    // init local variables
    int test_gpio = 05;
    bool ret_state = false;
    bool ret_value = true;

    // preconditions

    // a.1: read gpio
    ret_state = cut_drvGpio->read(test_gpio, ret_value);

    // exp.1: check return value
    CHECK(ret_state);
    CHECK_FALSE(ret_value);
}


/**
    Write gpio value (configured as output).

    - TEST tc_res_gpio_writeZero(..)
    - TEST tc_res_gpio_writeOne(..)
**/
TEST(tg_res_gpio, tc_res_gpio_writeZero) {
    // init local variables
    int test_gpio = 05;
    bool test_value = false;
    bool ret_state = false;

    // preconditions

    // a.1: write gpio to '0'
    ret_state = cut_drvGpio->write(test_gpio, test_value);

    // exp.1: check return value
    CHECK(ret_state);
}
TEST(tg_res_gpio, tc_res_gpio_writeOne) {
    // init local variables
    int test_gpio = 05;
    bool test_value = true;
    bool ret_state = false;

    // preconditions

    // a.1: write gpio to '1'
    ret_state = cut_drvGpio->write(test_gpio, test_value);

    // exp.1: check return value
    CHECK(ret_state);
}
