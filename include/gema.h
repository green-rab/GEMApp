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
    ## Prototypes ##
**/
void execute_sync10ms(t_GEMA_data &data);


#endif
