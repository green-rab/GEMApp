/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: ctrlService.h
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 18.09.2021
 **/

#ifndef CTRLSERVICE_H
#define CTRLSERVICE_H

#include "ctrlDriver.h"


/**
    ## CLASS T_ctrlService(..) - Service-Layer main-file ##
**/
class T_ctrlService {
    private:
        // link to driver-layer
        T_ctrlDriver *ptr_ctrlDriver;

        // status running (= true)
        bool run_scheduleSync10ms;

        // stop running (-> set to true)
        bool stop_scheduleSync10ms;

        // tasks
        void task_scheduleSync10ms(uint16_t n_times);

    public:
        T_ctrlService(T_ctrlDriver *inst_ctrlDriver);
        ~T_ctrlService();

        // initialization
        bool init_scheduleSync10ms(uint16_t n_times = 1);
        bool init_scheduleSync100ms();

        // status
        bool status_scheduleSync10ms();

        // cancels
        bool cancel_scheduleSync10ms();
};


#endif
