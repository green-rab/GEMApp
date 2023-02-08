/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: spy_drvGpio.cpp
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 23.08.2021
 **/

#include "spy_drvGpio.h"


/**
    ## T_spy_drvGpio :: Constructor ##
**/
T_spy_drvGpio::T_spy_drvGpio() {
    test_reset();
}


/**
    ## T_spy_drvGpio :: Destructor ##
**/
T_spy_drvGpio::~T_spy_drvGpio() {
}


/**
    ## T_spy_drvGpio :: init(..) - Initialize a single GPIO ##
**/
bool T_spy_drvGpio::init(int num, bool asOutput) {
    if(num >= CNT_GPIOS) {
        return false;
    }

    if(gpioError[num]) {
        return false;
    }

    if(!asOutput) {
        gpioState[num] = SPY_GPIO_INPUT;
    } else {
        gpioState[num] = SPY_GPIO_OUTPUT;
    }

    return true;
}


/**
    ## T_spy_drvGpio :: deinit(..) - Deinitialize a single GPIO ##
**/
bool T_spy_drvGpio::deinit(int num) {
    if(num >= CNT_GPIOS) {
        return false;
    }

    gpioState[num] = SPY_GPIO_RELEASED;

    return true;
}


/**
    ## T_spy_drvGpio :: getStateInit(..) - Return the state of initialization of a single GPIO ##
**/
bool T_spy_drvGpio::getStateInit(int num, bool &state_init) {
    state_init = false;

    if(num >= CNT_GPIOS) {
        return false;
    }

    // printf("getStateInput: %d\n", gpios[num]);
    if(gpioState[num] == SPY_GPIO_INPUT ||  gpioState[num] == SPY_GPIO_OUTPUT) {
        state_init = true;
    }

    return true;
}


/**
    ## T_spy_drvGpio :: getStateDirection(..) - Return the mode of a single GPIO if it is initialized ##
**/
bool T_spy_drvGpio::getStateDirection(int num, bool &state_direction) {
    state_direction = false;

    if(num >= CNT_GPIOS) {
        return false;
    }

    bool init;
    if(getStateInit(num, init) == false) {
        return false;
    }
    if(init == false) {
        return false;
    }

    if(gpioState[num] == SPY_GPIO_OUTPUT) {
        state_direction = true;
    }

    return true;
}


/**
    ## T_spy_drvGpio :: read(..) - Read single GPIO-value ##
**/
bool T_spy_drvGpio::read(int num, bool &value) {
    value = 0;

    if(num >= CNT_GPIOS) {
        return false;
    }

    value = gpioValue[num];

    if(gpioError[num]) {
        return false;
    }

    return true;
}


/**
    ## T_spy_drvGpio :: write(..) - Write single GPIO-value ##
**/
bool T_spy_drvGpio::write(int num, bool value) {
    if(num >= CNT_GPIOS) {
        return false;
    }

    if(gpioError[num]) {
        return false;
    }

    gpioValue[num] = value;

    return true;
}


/**
    ## T_spy_drvGpio :: test_reset() - For test only: reset all stored values ##
**/
void T_spy_drvGpio::test_reset() {
    for(int i = 0; i<CNT_GPIOS; i++) {
        gpioState[i] = SPY_GPIO_UNUSED;
        gpioValue[i] = false;
        gpioError[i] = false;
    }
}


/**
    ## T_spy_drvGpio :: test_setError(..) - For test only: set an gpio to fail ##
**/
void T_spy_drvGpio::test_setError(int num) {
    if(num >= CNT_GPIOS) {
        return;
    }

    gpioError[num] = true;
}


/**
    ## T_spy_drvGpio :: test_setReadValue(..) - For test only: set read-value ##
**/
void T_spy_drvGpio::test_setReadValue(int num, bool val) {
    if(num >= CNT_GPIOS) {
        return;
    }

    gpioValue[num] = val;
}


/**
    ## T_spy_drvGpio :: test_getWriteValue(..) - For test only: get write-value ##
**/
bool T_spy_drvGpio::test_getWriteValue(int num) {
    if(num >= CNT_GPIOS) {
        return false;
    }

    return gpioValue[num];
}


/**
    ## T_spy_drvGpio :: test_isReleased(..) - For test only: return if a gpio is released ##
**/
bool T_spy_drvGpio::test_isReleased(int num) {
    if(num >= CNT_GPIOS) {
        return false;
    }

    if(gpioState[num] == SPY_GPIO_RELEASED) {
        return true;
    }

    return false;
}
