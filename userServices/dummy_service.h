/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: dummy_service.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 21.10.2021
 **/

#ifndef DUMMY_SERVICE_H
#define DUMMY_SERVICE_H

#include "../include/gema.h"


/**
    ## CLASS T_dummy_service(..) - Dummy service for development ##
**/
class T_dummy_service {
    private:

    public:
        T_dummy_service();
        ~T_dummy_service();

        // calls
        virtual void execute(t_GEMA_data &ndata);
};


#endif