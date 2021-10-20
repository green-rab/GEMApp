/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: gema.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

#include "../include/gema.h"

#include <stdlib.h>
#include <vector>

#include "../service/dummy_service01.h"


/**
    ## PLEASE DO NOT CHANGE - Global variables for ressource definition ##
**/
std::vector<e_GEMA_resGpio> execute_sync10ms_INPUTS  = {};
std::vector<e_GEMA_resGpio> execute_sync10ms_OUTPUTS = {};


/**
    ## User instances of classes and functions ##
**/
T_dummy_service01 dummy_service01 = T_dummy_service01();


/**
    ## Execution synchronously every 10 ms ##
**/
void execute_sync10ms_startup() {
    execute_sync10ms_INPUTS.push_back(GPIO_05);
    execute_sync10ms_INPUTS.push_back(GPIO_06);
    execute_sync10ms_INPUTS.push_back(GPIO_13);
    execute_sync10ms_INPUTS.push_back(GPIO_26);

    execute_sync10ms_OUTPUTS.push_back(GPIO_12);
}

void execute_sync10ms(t_GEMA_data &data) {
    dummy_service01.execute(data);
}
