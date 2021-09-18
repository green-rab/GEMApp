/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: res_gpio.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 13.08.2021
 **/

#include "../include/global.h"
#include "../include/res_gpio.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


/**
    ## T_res_gpio :: Constructor ##
**/
T_res_gpio::T_res_gpio() {
}


/**
    ## T_res_gpio :: Destructor ##
**/
T_res_gpio::~T_res_gpio() {
}


/**
    ## T_res_gpio :: init(..) - Init one gpio as input or output ##
**/
bool T_res_gpio::init(int num, bool asOutput) {
    // char command[100];
    
    // sprintf(command, "echo %d > /sys/class/gpio/export", num);
    // callSystem(command);

    // if(isOutput == true) {
    //     sprintf(command, "echo out > /sys/class/gpio/gpio%d/direction", num);
    // } else {
    //     sprintf(command, "echo in > /sys/class/gpio/gpio%d/direction", num);
    // }
    // callSystem(command);

    // sprintf(command, "echo 0 > /sys/class/gpio/gpio%d/value", num);
    // callSystem(command);

    char path[100];
    char writeValue[100];

    ofstream fileExport;
    ofstream fileDirection;
    ofstream fileValue;

    #ifdef TESTMODE
    return true;
    #endif

    // file EXPORT
    fileExport.open("/sys/class/gpio/export");
    if(!fileExport.is_open()) {
        return false;
    }

    sprintf(writeValue, "%d", num);
    fileExport << writeValue;
    if(!fileExport.good()) {
        return false;
    }

    fileExport.close();

    // file DIRECTION
    sprintf(path, "/sys/class/gpio/gpio%d/direction", num);
    fileDirection.open(path);
    if(!fileDirection.is_open()) {
        return false;
    }
    
    if(asOutput == true) {
        fileDirection << "out";
    } else {
        fileDirection << "in";
    }
    if(!fileDirection.good()) {
        return false;
    }

    fileDirection.close();

    // file VALUE
    sprintf(path, "/sys/class/gpio/gpio%d/value", num);
    fileValue.open(path);
    if(!fileValue.is_open()) {
        return false;
    }

    fileValue << "0";
    if(!fileValue.good()) {
        return false;
    }

    fileValue.close();

    return true;
}


/**
    ## T_res_gpio :: deinit(..) - Release one gpio ##
**/
bool T_res_gpio::deinit(int num) {
    char writeValue[100];

    ofstream fileUnexport;

    #ifdef TESTMODE
    return true;
    #endif

    // file UNEXPORT
    fileUnexport.open("/sys/class/gpio/unexport");
    if(!fileUnexport.is_open()) {
        return false;
    }

    sprintf(writeValue, "%d", num);
    fileUnexport << writeValue;
    if(!fileUnexport.good()) {
        return false;
    }

    fileUnexport.close();

    return true;
}


/**
    ## T_res_gpio :: getStateInit(..) - Get state of gpio is initialized or not ##
**/
bool T_res_gpio::getStateInit(int num, bool &state_init) {
    char path[100];

    ifstream fileDirection;

    // set standard return-value
    state_init = false;

    #ifdef TESTMODE
    return true;
    #endif

    // file DIRECTION (to test if GPIO is available)
    sprintf(path, "/sys/class/gpio/gpio%d/direction", num);
    fileDirection.open(path);
    if(fileDirection.is_open()) {
        state_init = true;

        fileDirection.close();
    }

    return true;
}


/**
    ## T_res_gpio :: getStateDirection(..) - Get state of gpio is input (false) or output (true) ##
**/
bool T_res_gpio::getStateDirection(int num, bool &state_direction) {
    char path[100];
    char readvalue[100];

    ifstream fileDirection;

    // set standard return-value
    state_direction = false;

    #ifdef TESTMODE
    return true;
    #endif

    // file DIRECTION
    sprintf(path, "/sys/class/gpio/gpio%d/direction", num);
    fileDirection.open(path);
    if(!fileDirection.is_open()) {
        return false;
    }

    fileDirection >> readvalue;
    if(strcmp(readvalue, "out")) {
        state_direction = true;
    } else if(strcmp(readvalue, "in")) {
        state_direction = false;
    } else {
        return false;
    }
    if(!fileDirection.good()) {
        return false;
    }

    fileDirection.close();

    return true;
}


/**
    ## T_res_gpio :: read(..) - Read one gpio input ##
**/
bool T_res_gpio::read(int num, bool &value) {
    char path[100];
    char readValue[100];

    ifstream fileValue;

    // set standard return-value
    value = false;

    #ifdef TESTMODE
    return true;
    #endif

    // file VALUE
    sprintf(path, "/sys/class/gpio/gpio%d/value", num);
    fileValue.open(path);
    if(!fileValue.is_open()) {
        return false;
    }

    fileValue >> readValue;
    if(strcmp(readValue, "1")) {
        value = true;
    } else if(strcmp(readValue, "0")) {
        value = false;
    } else {
        return false;
    }
    if(!fileValue.good()) {
        return false;
    }

    fileValue.close();

    return true;
}


/**
    ## T_res_gpio :: write(..) - Write one gpio output ##
**/
bool T_res_gpio::write(int num, bool value) {
    char path[100];

    ofstream fileValue;

    // set standard return-value
    value = false;

    #ifdef TESTMODE
    return true;
    #endif

    // file VALUE
    sprintf(path, "/sys/class/gpio/gpio%d/value", num);
    fileValue.open(path);
    if(!fileValue.is_open()) {
        return false;
    }

    if(value == true) {
        fileValue << "1";
    } else {
        fileValue << "0";
    }
    if(!fileValue.good()) {
        return false;
    }

    return true;
}
