/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: driver.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 16.08.2021
 **/

#include <string>
using namespace std;

#include "../include/config.h"

#include "../include/global.h"
#include "../include/driver.h"


/**
    ## Instanced classes ##
**/
T_res_gpio RES_GPIO = T_res_gpio();


/**
    ## T_driver :: Constructor ##
**/
T_driver::T_driver() {
    // set class pointers
    res_gpio = &RES_GPIO;

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
    ## T_driver :: Destructor ##
**/
T_driver::~T_driver() {
}


/**
    ## PRIVATE T_driver :: *_rawImpl() - Return config raw-value ##
    
    - getConfig_device_rawImpl()
    - getConfig_gpio05_rawImpl()
    - getConfig_gpio06_rawImpl()
    - getConfig_gpio12_rawImpl()
    - getConfig_gpio13_rawImpl()
    - getConfig_gpio26_rawImpl()
**/
string T_driver::getConfig_device_rawImpl() { return strname_device(CONFIG_DEVICE); }
string T_driver::getConfig_gpio05_rawImpl() { return strname_gpio05(CONFIG_GPIO_05); }
string T_driver::getConfig_gpio06_rawImpl() { return strname_gpio06(CONFIG_GPIO_06); }
string T_driver::getConfig_gpio12_rawImpl() { return strname_gpio12(CONFIG_GPIO_12); }
string T_driver::getConfig_gpio13_rawImpl() { return strname_gpio13(CONFIG_GPIO_13); }
string T_driver::getConfig_gpio26_rawImpl() { return strname_gpio26(CONFIG_GPIO_26); }


/**
    ## PRIVATE T_driver :: getGpioEnum() - Return config-value for GPIO from config-string ##
**/
T_enum_driverGpio T_driver::getGpioEnum(string strConfig) {
    if(strConfig == "INPUT") {
        return INPUT;
    } else if(strConfig == "OUTPUT") {
        return OUTPUT;
    }

    return UNUSED;
}


/**
    ## PRIVATE T_driver :: checkConfig() - Check for a valid config.h ##
**/
bool T_driver::checkConfig() {
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
    ## PRIVATE T_driver :: initGpio() - Initialize GPIOs ##
**/
bool T_driver::initGpio() {
    // local variables
    T_enum_driverGpio gpio_config;

    // gpio 05
    gpio_config = getConfig_gpio05();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(res_gpio->init(05, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 05 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            return false;
        }
    }

    // gpio 06
    gpio_config = getConfig_gpio06();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(res_gpio->init(06, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 06 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            res_gpio->deinit(05);
            return false;
        }
    }

    // gpio 12
    gpio_config = getConfig_gpio12();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(res_gpio->init(12, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 12 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            res_gpio->deinit(05);
            res_gpio->deinit(06);
            return false;
        }
    }

    // gpio 13
    gpio_config = getConfig_gpio13();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(res_gpio->init(13, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 13 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            res_gpio->deinit(05);
            res_gpio->deinit(06);
            res_gpio->deinit(12);
            return false;
        }
    }

    // gpio 26
    gpio_config = getConfig_gpio26();
    if(gpio_config == INPUT || gpio_config == OUTPUT) {
        if(res_gpio->init(26, (gpio_config == OUTPUT)) == true) {
            callPrintf(".. GPIO 26 - set as %s\n", (gpio_config == INPUT) ? "INPUT" : "OUTPUT");
        } else {
            res_gpio->deinit(05);
            res_gpio->deinit(06);
            res_gpio->deinit(12);
            res_gpio->deinit(13);
            return false;
        }
    }

    return true;
}


/**
    ## T_driver :: getConfig_device() - Return config-value for host-device ##
**/
T_enum_driverDevice T_driver::getConfig_device() {
    string device = (*getConfig_device_raw)();

    if(device == "RASPBERRY_PI") {
        return RASPBERRY_PI;
    }

    return NONE;
}


/**
    ## T_driver :: getConfig_gpio*() - Return config-value for GPIO ##

    - getConfig_gpio05()
    - getConfig_gpio06()
    - getConfig_gpio12()
    - getConfig_gpio13()
    - getConfig_gpio26()
**/
T_enum_driverGpio T_driver::getConfig_gpio05() { return getGpioEnum((*getConfig_gpio05_raw)()); }
T_enum_driverGpio T_driver::getConfig_gpio06() { return getGpioEnum((*getConfig_gpio06_raw)()); }
T_enum_driverGpio T_driver::getConfig_gpio12() { return getGpioEnum((*getConfig_gpio12_raw)()); }
T_enum_driverGpio T_driver::getConfig_gpio13() { return getGpioEnum((*getConfig_gpio13_raw)()); }
T_enum_driverGpio T_driver::getConfig_gpio26() { return getGpioEnum((*getConfig_gpio26_raw)()); }


/**
    ## T_driver :: init() - Initialize all hardware ressources ##
**/
bool T_driver::init() {
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
    ## T_driver :: reset() - Resets all hardware ressources ##
**/
bool T_driver::reset() {
    callPrintf("-> Device successfully reseted\n");

    state = INIT;

    return true;
}


/**
    ## T_driver :: getState() - Return actual state ##
**/
T_enum_driverState T_driver::getState() {
    return state;
}


/**
    ## T_driver :: gpioRead(..) - Read a single GPIO ##
**/
bool T_driver::gpioRead(int num) {
    bool value = false;

    bool gpio_state;
    bool ret_gpio_state = res_gpio->getStateInit(num, gpio_state);
    if(!(ret_gpio_state == true && gpio_state == true)) {
        return false;
    }

    bool gpio_dir;
    bool ret_gpio_dir = res_gpio->getStateDirection(num, gpio_dir);
    if(!(ret_gpio_dir == true && gpio_dir == false)) {
        return false;
    }

    if(!(res_gpio->read(num, value) == true)) {
        return false;
    }

    return value;
}


/**
    ## T_driver :: gpioWrite(..) - Write a single GPIO ##
**/
bool T_driver::gpioWrite(int num, bool value) {
    bool gpio_state;
    bool ret_gpio_state = res_gpio->getStateInit(num, gpio_state);
    if(!(ret_gpio_state == true && gpio_state == true)) {
        return false;
    }

    bool gpio_dir;
    bool ret_gpio_dir = res_gpio->getStateDirection(num, gpio_dir);
    if(!(ret_gpio_dir == true && gpio_dir == true)) {
        return false;
    }

    if(!(res_gpio->write(num, value) == true)) {
        return false;
    }
    // res_gpio->write(num, value);

    return true;
}
