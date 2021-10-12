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

    public:
        T_service(T_driver *inst_driver);
        ~T_service();

        // link to driver-layer
        T_driver *ptr_driver;

        // status running (= true)
        bool run_scheduleSync10ms;

        // stop running (-> set to true)
        bool stop_scheduleSync10ms;

        // tasks
        void task_scheduleSync10ms(uint16_t n_times);

        // initialization
        bool init_scheduleSync10ms(uint16_t n_times = 1);
        bool init_scheduleSync100ms();

        // cancels
        bool cancel_scheduleSync10ms();
};


#endif
