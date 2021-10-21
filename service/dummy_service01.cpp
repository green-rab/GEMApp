/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: dummy_service01.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 19.09.2021
 **/

#include "dummy_service01.h"


/**
    ## T_dummy_service01 :: Constructor ##
**/
T_dummy_service01::T_dummy_service01() {
    test_reset();
}


/**
    ## T_dummy_service01 :: Destructor ##
**/
T_dummy_service01::~T_dummy_service01() {
}


/**
    ## T_dummy_service01 :: execute() - Run the service ##
**/
void T_dummy_service01::execute(t_GEMA_data &data) {
    if(test_serviceCalls == 0) {
        test_timeStart = std::chrono::steady_clock::now();
    }
    if(test_serviceCalls < TEST_TIME_SAMPLES) {
        test_timestamps[test_serviceCalls] = std::chrono::duration<double>(std::chrono::steady_clock::now() - test_timeStart).count();
    }

    test_serviceCalls++;

    dataRead = data;
    data = dataWrite;

    // printf("i: %d ; data: %d ; newData: %d\n", test_serviceCalls, data.GPIO_05, newData.GPIO_05);
}


/**
    ## T_dummy_service01 :: test_reset(..) - For test only: Reset dummy to init values ##
**/
void T_dummy_service01::test_reset() {
    test_serviceCalls = 0;

    dataRead  = {};
    dataWrite = {};
}


/**
    ## T_dummy_service01 :: test_getServiceCalls(..) - For test only: Return count of calls ##
**/
int T_dummy_service01::test_getServiceCalls() {
    return test_serviceCalls;
}


/**
    ## T_dummy_service01 :: test_getServiceTimestamp(..) - For test only: Return timestamp of specific call ##
**/
double T_dummy_service01::test_getServiceTimestamp(int sample) {
    if(sample >= TEST_TIME_SAMPLES) {
        return -1;
    }

    return test_timestamps[sample];
}
