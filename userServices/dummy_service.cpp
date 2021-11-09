/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: dummy_service.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 21.10.2021
 **/

#include "dummy_service.h"


/**
    ## T_dummy_service :: Constructor ##
**/
T_dummy_service::T_dummy_service() {
}


/**
    ## T_dummy_service :: Destructor ##
**/
T_dummy_service::~T_dummy_service() {
}


/**
    ## T_dummy_service :: execute() - Run the service ##
**/
void T_dummy_service::execute(t_GEMApp_data &data) {
    data.GPIO_12 = (data.GPIO_05 & data.GPIO_06) | data.GPIO_13;
}
