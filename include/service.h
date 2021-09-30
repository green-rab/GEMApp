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
        bool running_scheduleSync10ms;

        static void task_scheduleSync10ms();

        void timer_start(std::function<void(void)> func, unsigned int interval, uint16_t n_times, bool &status);

    public:
        T_service();
        ~T_service();

        // initialization
        bool init_scheduleSync10ms(uint16_t i_times = 1);
        bool init_scheduleSync100ms();
};


#endif
