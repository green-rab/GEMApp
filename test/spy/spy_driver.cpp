/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: spy_driver.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 07.10.2021
 **/

#include "spy_driver.h"


/**
    ## T_spy_driver :: Constructor ##
**/
T_spy_driver::T_spy_driver() {
    test_reset();
}


/**
    ## T_spy_driver :: Destructor ##
**/
T_spy_driver::~T_spy_driver() {
}


/**
    ## T_spy_driver :: gpioRead(..) - Read single GPIO-value ##
**/
bool T_spy_driver::gpioRead(int num) {
    return gpioValue[num];
}


/**
    ## T_spy_driver :: gpioWrite(..) - Write single GPIO-value ##
**/
bool T_spy_driver::gpioWrite(int num, bool value) {
    gpioValue[num] = value;

    return true;
}


/**
    ## T_spy_driver :: test_reset() - For test only: reset all stored values ##
**/
void T_spy_driver::test_reset() {
    for(int i = 0; i<CNT_GPIOS; i++) {
        gpioValue[i] = false;
    }
}


/**
    ## T_spy_driver :: test_setReadValue(..) - For test only: set read-value ##
**/
void T_spy_driver::test_setReadValue(int num, bool val) {
    if(num >= CNT_GPIOS) {
        return;
    }

    gpioValue[num] = val;
}


/**
    ## T_spy_driver :: test_getWriteValue(..) - For test only: get write-value ##
**/
bool T_spy_driver::test_getWriteValue(int num) {
    if(num >= CNT_GPIOS) {
        return false;
    }

    return gpioValue[num];
}
