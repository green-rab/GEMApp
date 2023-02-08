/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: gemapp.cpp
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 18.09.2021
 **/

#include <stdlib.h>
#include <vector>
using namespace std;

#include "../include/gemapp.h"


/**
    ## PLEASE DO NOT CHANGE - Global variables for ressource definition ##
**/
vector<e_GEMApp_resGpio> execute_sync10ms_INPUTS  = {};
vector<e_GEMApp_resGpio> execute_sync10ms_OUTPUTS = {};


/**
    ## User header-files for classes and functions ##
**/
#include "../userServices/dummy_service.h"


/**
    ## User instances of classes and functions ##
**/
T_dummy_service *dummy_service;


/**
    ## Execution synchronously every 10 ms ##
**/
void execute_sync10ms_startup() {
    dummy_service = new T_dummy_service();

    execute_sync10ms_INPUTS.push_back(GPIO_05);
    execute_sync10ms_INPUTS.push_back(GPIO_06);
    execute_sync10ms_INPUTS.push_back(GPIO_13);
    execute_sync10ms_INPUTS.push_back(GPIO_26);

    execute_sync10ms_OUTPUTS.push_back(GPIO_12);
}

void execute_sync10ms_shutdown() {
    if(dummy_service) {
        delete dummy_service;
    }
    dummy_service = nullptr;
}

void execute_sync10ms(t_GEMApp_data &data) {
    dummy_service->execute(data);
}
