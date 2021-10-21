/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: gema.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

#ifndef GEMA_H
#define GEMA_H

#include <vector>


/**
    ## Enum for startup ressource definition ##
**/
enum e_GEMA_resGpio {
    GPIO_05,
    GPIO_06,
    GPIO_12,
    GPIO_13,
    GPIO_26
};


/**
    ## Datatype ##
**/
struct t_GEMA_data {
    bool GPIO_05;
    bool GPIO_06;
    bool GPIO_12;
    bool GPIO_13;
    bool GPIO_26;
};


/**
    ## Global varibales ##
**/
extern std::vector<e_GEMA_resGpio> execute_sync10ms_INPUTS;
extern std::vector<e_GEMA_resGpio> execute_sync10ms_OUTPUTS;


/**
    ## Prototypes ##
**/
void execute_sync10ms_startup();
void execute_sync10ms_shutdown();
void execute_sync10ms(t_GEMA_data &data);


#endif
