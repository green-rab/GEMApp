/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: dummy_service.h
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 21.10.2021
 **/

#ifndef DUMMY_SERVICE_H
#define DUMMY_SERVICE_H

#include "../include/gemapp.h"


/**
    ## CLASS T_dummy_service(..) - Dummy service for development ##
**/
class T_dummy_service {
    private:

    public:
        T_dummy_service();
        ~T_dummy_service();

        // calls
        virtual void execute(t_GEMApp_data &ndata);
};


#endif
