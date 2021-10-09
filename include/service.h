/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: service.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

#ifndef SERVICE_H
#define SERVICE_H

#include "driver.h"


/**
    ## CLASS T_service(..) - Service-Layer main-file ##
**/
class T_service {
    private:
        // link to driver-layer
        T_driver *ptr_driver;

    public:
        // static properties
        bool run_scheduleSync10ms;
        bool stop_scheduleSync10ms;

        // static methods
        void task_scheduleSync10ms(uint16_t n_times);

        T_service(T_driver *driver);
        ~T_service();

        // initialization
        bool init_scheduleSync10ms(uint16_t n_times = 1);
        bool cancel_scheduleSync10ms();

        bool init_scheduleSync100ms();
};


#endif
