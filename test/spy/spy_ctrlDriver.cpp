/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: spy_driver.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 07.10.2021
 **/

#include "spy_ctrlDriver.h"


/**
    ## T_spy_ctrlDriver :: Constructor ##
**/
T_spy_ctrlDriver::T_spy_ctrlDriver(T_drvGpio *inst_drvGpio) : T_ctrlDriver(inst_drvGpio) {
    test_reset();
}


/**
    ## T_spy_ctrlDriver :: Destructor ##
**/
T_spy_ctrlDriver::~T_spy_ctrlDriver() {
}


/**
    ## T_spy_ctrlDriver :: gpioRead(..) - Read single GPIO-value ##
**/
bool T_spy_ctrlDriver::gpioRead(int num) {
    return gpioValue[num];
}


/**
    ## T_spy_ctrlDriver :: gpioWrite(..) - Write single GPIO-value ##
**/
bool T_spy_ctrlDriver::gpioWrite(int num, bool value) {
    gpioValue[num] = value;

    return true;
}


/**
    ## T_spy_ctrlDriver :: test_reset() - For test only: reset all stored values ##
**/
void T_spy_ctrlDriver::test_reset() {
    for(int i = 0; i<CNT_GPIOS; i++) {
        gpioValue[i] = false;
    }
}


/**
    ## T_spy_ctrlDriver :: test_setReadValue(..) - For test only: set read-value ##
**/
void T_spy_ctrlDriver::test_setReadValue(int num, bool val) {
    if(num >= CNT_GPIOS) {
        return;
    }

    gpioValue[num] = val;
}


/**
    ## T_spy_ctrlDriver :: test_getWriteValue(..) - For test only: get write-value ##
**/
bool T_spy_ctrlDriver::test_getWriteValue(int num) {
    if(num >= CNT_GPIOS) {
        return false;
    }

    return gpioValue[num];
}
