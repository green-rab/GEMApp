/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: esb.h
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 08.11.2021
 **/

#ifndef ESB_H
#define ESB_H

#include "drvGpio.h"
#include "ctrlDriver.h"
#include "ctrlService.h"


/**
    ## CLASS T_ESB(..) - Enterprise Service Bus ##
**/
class T_ESB {
    private:
        // link to single units
        T_drvGpio     *ptr_drvGpio;

        T_ctrlDriver  *ptr_ctrlDriver;
        T_ctrlService *ptr_ctrlService;

    public:
        T_ESB(int argc, char** argv);
        ~T_ESB();

        int run();

        bool getState_ctrlDriver();
        bool getState_ctrlService();
};


#endif
