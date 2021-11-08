/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: esb.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 08.11.2021
 **/

#ifndef ESB_H
#define ESB_H

#include "driver.h"
#include "driver_enum.h"
#include "service.h"


/**
    ## CLASS T_ESB(..) - Enterprise Service Bus ##
**/
class T_ESB {
    private:
        T_driver  *ptr_driver;
        T_service *ptr_service;

    public:
        T_ESB(int argc, char** argv);
        ~T_ESB();

        int run();

        bool getState_driver();
        bool getState_service();
};


#endif