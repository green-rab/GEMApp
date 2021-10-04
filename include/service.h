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


/**
    ## CLASS T_service(..) - Service-Layer main-file ##
**/
class T_service {
    private:

    public:
        // static properties
        static bool run_scheduleSync10ms;
        static bool stop_scheduleSync10ms;
        static void task_scheduleSync10ms(uint16_t n_times);

        T_service();
        ~T_service();

        // initialization
        bool init_scheduleSync10ms(uint16_t n_times = 1);
        bool cancel_scheduleSync10ms();

        bool init_scheduleSync100ms();
};


#endif
