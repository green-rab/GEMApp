/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: drvGpio.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 13.08.2021
 **/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
using namespace std;

#include "../../include/global.h"
#include "../../include/unit/drvGpio.h"


/**
    ## T_drvGpio :: Constructor ##
**/
T_drvGpio::T_drvGpio() {
}


/**
    ## T_drvGpio :: Destructor ##
**/
T_drvGpio::~T_drvGpio() {
}


/**
    ## T_drvGpio :: init(..) - Init one gpio as input or output ##
**/
bool T_drvGpio::init(int num, bool asOutput) {
    char path[100];
    char writeValue[100];

    ofstream fileExport;
    ofstream fileDirection;
    ofstream fileValue;

    size_t lenNum = 1;
    if(num > 9) {
        lenNum = 2;
    }

    #ifdef TESTMODE
    return true;
    #endif

    // file EXPORT
    fileExport.open("/sys/class/gpio/export");
    if(!fileExport.is_open()) {
        callPrintf(".. export is_open() failed!\n");
        return false;
    }

    snprintf(writeValue, 1+lenNum, "%d", num);
    fileExport << writeValue;
    if(!fileExport.good()) {
        callPrintf(".. export good() failed!\n");
        return false;
    }

    fileExport.close();
    usleep(delayFileClose);

    // file DIRECTION
    snprintf(path, 31+lenNum, "/sys/class/gpio/gpio%d/direction", num);
    fileDirection.open(path);
    if(!fileDirection.is_open()) {
        callPrintf(".. direction is_open() failed!\n");
        return false;
    }
    
    if(asOutput == true) {
        fileDirection << "out";
    } else {
        fileDirection << "in";
    }
    if(!fileDirection.good()) {
        callPrintf(".. direction good() failed!\n");
        return false;
    }

    fileDirection.close();
    usleep(delayFileClose);

    // file VALUE (if set as output)
    if(asOutput == true) {
        snprintf(path, 27+lenNum, "/sys/class/gpio/gpio%d/value", num);
        fileValue.open(path);
        if(!fileValue.is_open()) {
            callPrintf(".. value is_open() failed!\n");
            return false;
        }

        fileValue << "0";
        if(!fileValue.good()) {
            callPrintf(".. value good() failed!\n");
            return false;
        }

        fileValue.close();
        usleep(delayFileClose);
    }

    return true;
}


/**
    ## T_drvGpio :: deinit(..) - Release one gpio ##
**/
bool T_drvGpio::deinit(int num) {
    char writeValue[100];

    ofstream fileUnexport;

    size_t lenNum = 1;
    if(num > 9) {
        lenNum = 2;
    }

    #ifdef TESTMODE
    return true;
    #endif

    // file UNEXPORT
    fileUnexport.open("/sys/class/gpio/unexport");
    if(!fileUnexport.is_open()) {
        return false;
    }

    snprintf(writeValue, 1+lenNum, "%d", num);
    fileUnexport << writeValue;
    if(!fileUnexport.good()) {
        return false;
    }

    fileUnexport.close();
    usleep(delayFileClose);

    return true;
}


/**
    ## T_drvGpio :: getStateInit(..) - Get state of gpio is initialized or not ##
**/
bool T_drvGpio::getStateInit(int num, bool &state_init) {
    char path[100];

    ifstream fileDirection;

    size_t lenNum = 1;
    if(num > 9) {
        lenNum = 2;
    }

    // set standard return-value
    state_init = false;

    #ifdef TESTMODE
    return true;
    #endif

    // file DIRECTION (to test if GPIO is available)
    snprintf(path, 31+lenNum, "/sys/class/gpio/gpio%d/direction", num);
    fileDirection.open(path);
    if(fileDirection.is_open()) {
        state_init = true;

        fileDirection.close();
        //usleep(delayFileClose);
    }

    return true;
}


/**
    ## T_drvGpio :: getStateDirection(..) - Get state of gpio is input (false) or output (true) ##
**/
bool T_drvGpio::getStateDirection(int num, bool &state_direction) {
    char path[100];
    char readvalue[100];

    ifstream fileDirection;

    size_t lenNum = 1;
    if(num > 9) {
        lenNum = 2;
    }

    // set standard return-value
    state_direction = false;

    #ifdef TESTMODE
    return true;
    #endif

    // file DIRECTION
    snprintf(path, 31+lenNum, "/sys/class/gpio/gpio%d/direction", num);
    fileDirection.open(path);
    if(!fileDirection.is_open()) {
        return false;
    }

    fileDirection >> readvalue;
    if(!strcmp(readvalue, "out")) {
        state_direction = true;
    } else if(!strcmp(readvalue, "in")) {
        state_direction = false;
    } else {
        return false;
    }
    if(!fileDirection.good()) {
        return false;
    }

    fileDirection.close();
    //usleep(delayFileClose);

    return true;
}


/**
    ## T_drvGpio :: read(..) - Read one gpio input ##
**/
bool T_drvGpio::read(int num, bool &value) {
    char path[100];
    char readValue[100];

    ifstream fileValue;

    // set standard return-value
    value = false;

    size_t lenNum = 1;
    if(num > 9) {
        lenNum = 2;
    }

    #ifdef TESTMODE
    return true;
    #endif

    // file VALUE
    snprintf(path, 27+lenNum, "/sys/class/gpio/gpio%d/value", num);
    fileValue.open(path);
    if(!fileValue.is_open()) {
        return false;
    }

    fileValue >> readValue;
    if(!strcmp(readValue, "1")) {
        value = true;
    } else if(!strcmp(readValue, "0")) {
        value = false;
    } else {
        return false;
    }
    if(!fileValue.good()) {
        return false;
    }

    fileValue.close();
    //usleep(delayFileClose);

    return true;
}


/**
    ## T_drvGpio :: write(..) - Write one gpio output ##
**/
bool T_drvGpio::write(int num, bool value) {
    char path[100];

    ofstream fileValue;

    size_t lenNum = 1;
    if(num > 9) {
        lenNum = 2;
    }

    #ifdef TESTMODE
    return true;
    #endif

    // file VALUE
    snprintf(path, 27+lenNum, "/sys/class/gpio/gpio%d/value", num);
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

    fileValue.close();
    //usleep(delayFileClose);

    return true;
}
