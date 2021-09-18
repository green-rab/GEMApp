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
        T_service();
        ~T_service();

        // initialization
        bool init_scheduleSync10ms();
        bool init_scheduleSync100ms();
};


#endif
