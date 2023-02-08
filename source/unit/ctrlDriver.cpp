/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: ctrlDriver.cpp
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 16.08.2021
 **/

#include <string>
using namespace std;

#include "../../include/config.h"

#include "../../include/global.h"
#include "../../include/unit/ctrlDriver.h"


/**
    ## T_ctrlDriver :: Constructor ##
**/
T_ctrlDriver::T_ctrlDriver(T_drvGpio *inst_drvGpio) {
    ptr_drvGpio = inst_drvGpio;

    // set function pointers
    getConfig_device_raw = &getConfig_device_rawImpl;
    getConfig_gpio05_raw = &getConfig_gpio05_rawImpl;
    getConfig_gpio06_raw = &getConfig_gpio06_rawImpl;
    getConfig_gpio12_raw = &getConfig_gpio12_rawImpl;
    getConfig_gpio13_raw = &getConfig_gpio13_rawImpl;
    getConfig_gpio26_raw = &getConfig_gpio26_rawImpl;

    state = INIT;
}


/**
    ## T_ctrlDriver :: Destructor ##
**/
T_ctrlDriver::~T_ctrlDriver() {
}


/**
    ## PRIVATE T_ctrlDriver :: *_rawImpl() - Return config raw-value ##
    
    - getConfig_device_rawImpl()
    - getConfig_gpio05_rawImpl()
    - getConfig_gpio06_rawImpl()
    - getConfig_gpio12_rawImpl()
    - getConfig_gpio13_rawImpl()
    - getConfig_gpio26_rawImpl()
**/
string T_ctrlDriver::getConfig_device_rawImpl() { return strname_device(CONFIG_DEVICE); }
string T_ctrlDriver::getConfig_gpio05_rawImpl() { return strname_gpio05(CONFIG_GPIO_05); }
string T_ctrlDriver::getConfig_gpio06_rawImpl() { return strname_gpio06(CONFIG_GPIO_06); }
string T_ctrlDriver::getConfig_gpio12_rawImpl() { return strname_gpio12(CONFIG_GPIO_12); }
string T_ctrlDriver::getConfig_gpio13_rawImpl() { return strname_gpio13(CONFIG_GPIO_13); }
string T_ctrlDriver::getConfig_gpio26_rawImpl() { return strname_gpio26(CONFIG_GPIO_26); }


/**
    ## PRIVATE T_ctrlDriver :: getGpioEnum() - Return config-value for GPIO from config-string ##
**/
T_enum_driverGpio T_ctrlDriver::getGpioEnum(string strConfig) {
    if(strConfig == "INPUT") {
        return INPUT;
    } else if(strConfig == "OUTPUT") {
        return OUTPUT;
    }

    return UNUSED;
}


/**
    ## PRIVATE T_ctrlDriver :: checkConfig() - Check for a valid config.h ##
**/
bool T_ctrlDriver::checkConfig() {
    if(getConfig_gpio05() != UNUSED
    || getConfig_gpio06() != UNUSED
    || getConfig_gpio12() != UNUSED
    || getConfig_gpio13() != UNUSED
    || getConfig_gpio26() != UNUSED) {
        return true;
    }

    return false;
}


/**
    ## PRIVATE T_ctrlDriver :: initGpio() - Initialize GPIOs ##
**/
bool T_ctrlDriver::initGpio() {
    // local variables
    T_enum_driverGpio gpio_config;

    // gpio 05
    gpio_config = getConfig_gpio05();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(ptr_drvGpio->init(05, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 05 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            return false;
        }
    }

    // gpio 06
    gpio_config = getConfig_gpio06();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(ptr_drvGpio->init(06, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 06 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            ptr_drvGpio->deinit(05);
            return false;
        }
    }

    // gpio 12
    gpio_config = getConfig_gpio12();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(ptr_drvGpio->init(12, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 12 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            ptr_drvGpio->deinit(05);
            ptr_drvGpio->deinit(06);
            return false;
        }
    }

    // gpio 13
    gpio_config = getConfig_gpio13();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(ptr_drvGpio->init(13, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 13 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            ptr_drvGpio->deinit(05);
            ptr_drvGpio->deinit(06);
            ptr_drvGpio->deinit(12);
            return false;
        }
    }

    // gpio 26
    gpio_config = getConfig_gpio26();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(ptr_drvGpio->init(26, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 26 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            ptr_drvGpio->deinit(05);
            ptr_drvGpio->deinit(06);
            ptr_drvGpio->deinit(12);
            ptr_drvGpio->deinit(13);
            return false;
        }
    }

    return true;
}


/**
    ## T_ctrlDriver :: getConfig_device() - Return config-value for host-device ##
**/
T_enum_driverDevice T_ctrlDriver::getConfig_device() {
    string device = (*getConfig_device_raw)();

    if(device == "RASPBERRY_PI") {
        return RASPBERRY_PI;
    }

    return NONE;
}


/**
    ## T_ctrlDriver :: getConfig_gpio*() - Return config-value for GPIO ##

    - getConfig_gpio05()
    - getConfig_gpio06()
    - getConfig_gpio12()
    - getConfig_gpio13()
    - getConfig_gpio26()
**/
T_enum_driverGpio T_ctrlDriver::getConfig_gpio05() { return getGpioEnum((*getConfig_gpio05_raw)()); }
T_enum_driverGpio T_ctrlDriver::getConfig_gpio06() { return getGpioEnum((*getConfig_gpio06_raw)()); }
T_enum_driverGpio T_ctrlDriver::getConfig_gpio12() { return getGpioEnum((*getConfig_gpio12_raw)()); }
T_enum_driverGpio T_ctrlDriver::getConfig_gpio13() { return getGpioEnum((*getConfig_gpio13_raw)()); }
T_enum_driverGpio T_ctrlDriver::getConfig_gpio26() { return getGpioEnum((*getConfig_gpio26_raw)()); }


/**
    ## T_ctrlDriver :: init() - Initialize all hardware ressources ##
**/
bool T_ctrlDriver::init() {
    bool ret_initGpio;

    if(state != INIT) {
        callPrintf("-> ERROR: Device already initialized\n");

        return false;
    }

    if(getConfig_device() == RASPBERRY_PI) {
        if(checkConfig()) {
            callPrintf("-> Initialization as RASPBERRY_PI...\n");

            ret_initGpio = initGpio();
            if(ret_initGpio == false) {
                callPrintf("-> ABORT: Initialization of all GPIOs failed\n");

                state = ERROR;
                return false;
            }

            state = RUN;
        } else {
            callPrintf("-> ABORT: Initialization as RASPBERRY_PI with no hardware-ressource is not valid\n");

            state = ERROR;
            return false;
        }
    } else {
        callPrintf("-> ABORT: Initialization as NONE is not valid\n");

        state = ERROR;
        return false;
    }

    return true;
}


/**
    ## T_ctrlDriver :: reset() - Resets all hardware ressources ##
**/
bool T_ctrlDriver::reset() {
    callPrintf("-> Device successfully reseted\n");

    state = INIT;

    return true;
}


/**
    ## T_ctrlDriver :: getState() - Return actual state ##
**/
T_enum_driverState T_ctrlDriver::getState() {
    return state;
}


/**
    ## T_ctrlDriver :: gpioRead(..) - Read a single GPIO ##
**/
bool T_ctrlDriver::gpioRead(int num) {
    bool value = false;

    bool gpio_state;
    bool ret_gpio_state = ptr_drvGpio->getStateInit(num, gpio_state);
    if(!(ret_gpio_state == true && gpio_state == true)) {
        return false;
    }

    bool gpio_dir;
    bool ret_gpio_dir = ptr_drvGpio->getStateDirection(num, gpio_dir);
    if(!(ret_gpio_dir == true && gpio_dir == false)) {
        return false;
    }

    if(!(ptr_drvGpio->read(num, value) == true)) {
        return false;
    }

    return value;
}


/**
    ## T_ctrlDriver :: gpioWrite(..) - Write a single GPIO ##
**/
bool T_ctrlDriver::gpioWrite(int num, bool value) {
    bool gpio_state;
    bool ret_gpio_state = ptr_drvGpio->getStateInit(num, gpio_state);
    if(!(ret_gpio_state == true && gpio_state == true)) {
        return false;
    }

    bool gpio_dir;
    bool ret_gpio_dir = ptr_drvGpio->getStateDirection(num, gpio_dir);
    if(!(ret_gpio_dir == true && gpio_dir == true)) {
        return false;
    }

    if(!(ptr_drvGpio->write(num, value) == true)) {
        return false;
    }

    return true;
}
