/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: spy_userService.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 19.09.2021
 **/

#ifndef SPY_USERSERVICE_01_H
#define SPY_USERSERVICE_01_H

#include "../../userServices/dummy_service.h"
#include "../../include/gema.h"

#include <chrono>


#define TEST_TIME_SAMPLES 1000


/**
    ## CLASS T_spy_userService(..) - SPY for T_dummy_service ##
**/
class T_spy_userService : public T_dummy_service {
    private:
        int test_serviceCalls;

        std::chrono::steady_clock::time_point test_timeStart;
        double test_timestamps[TEST_TIME_SAMPLES];

    public:
        T_spy_userService();
        ~T_spy_userService();

        // calls
        void execute(t_GEMA_data &ndata);

        // only for test-cases
        t_GEMA_data dataRead;
        t_GEMA_data dataWrite;
        void test_reset();
        int test_getServiceCalls();
        double test_getServiceTimestamp(int sample);
};


#endif
