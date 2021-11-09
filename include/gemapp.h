/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: gemapp.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

#ifndef GEMAPP_H
#define GEMAPP_H

#include <vector>
using namespace std;


/**
    ## Enum for startup ressource definition ##
**/
enum e_GEMApp_resGpio {
    GPIO_05,
    GPIO_06,
    GPIO_12,
    GPIO_13,
    GPIO_26
};


/**
    ## Datatype ##
**/
struct t_GEMApp_data {
    bool GPIO_05;
    bool GPIO_06;
    bool GPIO_12;
    bool GPIO_13;
    bool GPIO_26;
};


/**
    ## Global varibales ##
**/
extern vector<e_GEMApp_resGpio> execute_sync10ms_INPUTS;
extern vector<e_GEMApp_resGpio> execute_sync10ms_OUTPUTS;


/**
    ## Prototypes ##
**/
void execute_sync10ms_startup();
void execute_sync10ms_shutdown();
void execute_sync10ms(t_GEMApp_data &data);


#endif
