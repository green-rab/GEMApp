/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: dummy_service01.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 19.09.2021
 **/

#ifndef DUMMY_SERVICE_01_H
#define DUMMY_SERVICE_01_H

#include "../include/gema.h"

#include <chrono>


#define TEST_TIME_SAMPLES 1000


/**
    ## CLASS T_dummy_service01(..) - Dummy service 01 for development ##
**/
class T_dummy_service01 {
    private:
        int test_serviceCalls;

        std::chrono::steady_clock::time_point test_timeStart;
        double test_timestamps[TEST_TIME_SAMPLES];

    public:
        T_dummy_service01();
        ~T_dummy_service01();

        // calls
        void execute(t_GEMA_data &newData);

        // only for test-cases
        t_GEMA_data data;
        void test_reset();
        int test_getServiceCalls();
        double test_getServiceTimestamp(int sample);
};


#endif
