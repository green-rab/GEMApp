/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: driver_enum.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 16.08.2021
 **/

#ifndef DRIVER_ENUM_H
#define DRIVER_ENUM_H


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


#endif
