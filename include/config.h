/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: config.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 16.08.2021
 **/

#ifndef CONFIG_H
#define CONFIG_H


/**
    ## USER DEFINED PARAMTERS FOR DRIVER ##
**/

// #define CONFIG_DEVICE NONE
#define CONFIG_DEVICE RASPBERRY_PI

// #define CONFIG_GPIO_05 UNUSED
#define CONFIG_GPIO_05 INPUT
// #define CONFIG_GPIO_05 OUTPUT

#define CONFIG_GPIO_06 INPUT
#define CONFIG_GPIO_12 OUTPUT
#define CONFIG_GPIO_13 INPUT
#define CONFIG_GPIO_26 INPUT


#endif
