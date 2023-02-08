/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: ctrlDriver.h
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 16.08.2021
 **/

#ifndef CTRLDRIVER_H
#define CTRLDRIVER_H

#include "drvGpio.h"

#include <string>
using namespace std;


/**
    ## ENUM T_enum_driverState()..) - State of driver ##
**/
enum T_enum_driverState {
    INIT = 0,
    RUN = 10,
    ERROR = 20
};


/**
    ## ENUM T_enum_configDevice(..) - Supported host-devices ##
**/
enum T_enum_driverDevice {
    NONE = 0,

    RASPBERRY_PI = 1
};


/**
    ## ENUM T_enum_driverGpio(..) - Modes for GPIOs ##
**/
enum T_enum_driverGpio {
    UNUSED = 0,
    INPUT = 1,
    OUTPUT = 2
};


/**
    ## Conversion of constants from config.h to string ##
**/
#define str_device(CONFIG_DEVICE) #CONFIG_DEVICE
#define str_gpio05(CONFIG_GPIO_05) #CONFIG_GPIO_05
#define str_gpio06(CONFIG_GPIO_06) #CONFIG_GPIO_06
#define str_gpio12(CONFIG_GPIO_12) #CONFIG_GPIO_12
#define str_gpio13(CONFIG_GPIO_13) #CONFIG_GPIO_13
#define str_gpio26(CONFIG_GPIO_26) #CONFIG_GPIO_26

#define strname_device(name) str_device(name)
#define strname_gpio05(name) str_gpio05(name)
#define strname_gpio06(name) str_gpio06(name)
#define strname_gpio12(name) str_gpio12(name)
#define strname_gpio13(name) str_gpio13(name)
#define strname_gpio26(name) str_gpio26(name)


/**
    ## CLASS T_ctrlDriver(..) - Driver-Layer main-file ##
**/
class T_ctrlDriver {
    private:
        // link to hardware-ressources
        T_drvGpio *ptr_drvGpio;

        // state variables
        T_enum_driverState state;

        // implementation for get-functions (config.h)
        static string getConfig_device_rawImpl();
        static string getConfig_gpio05_rawImpl();
        static string getConfig_gpio06_rawImpl();
        static string getConfig_gpio12_rawImpl();
        static string getConfig_gpio13_rawImpl();
        static string getConfig_gpio26_rawImpl();

        // helper functions
        T_enum_driverGpio getGpioEnum(string strConfig);

        // initialization for HW-Ressources
        bool checkConfig();
        bool initGpio();

    public:
        T_ctrlDriver(T_drvGpio *inst_drvGpio);
        ~T_ctrlDriver();

        // function pointers for get-functions (config.h)
        string (*getConfig_device_raw)();
        string (*getConfig_gpio05_raw)();
        string (*getConfig_gpio06_raw)();
        string (*getConfig_gpio12_raw)();
        string (*getConfig_gpio13_raw)();
        string (*getConfig_gpio26_raw)();

        // get-functions for values from config.h
        T_enum_driverDevice getConfig_device();
        T_enum_driverGpio getConfig_gpio05();
        T_enum_driverGpio getConfig_gpio06();
        T_enum_driverGpio getConfig_gpio12();
        T_enum_driverGpio getConfig_gpio13();
        T_enum_driverGpio getConfig_gpio26();

        // basic functions for init, reset and get inernal values
        bool init();
        bool reset();

        T_enum_driverState getState();

        // HW-Ressource: GPIO
        virtual bool gpioRead(int num);
        virtual bool gpioWrite(int num, bool value);
};


#endif
