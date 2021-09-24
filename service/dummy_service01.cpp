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
    test_serviceCalls = 0;
}


/**
    ## T_dummy_service01 :: Destructor ##
**/
T_dummy_service01::~T_dummy_service01() {
}


/**
    ## T_dummy_service01 :: execute() - Run the service ##
**/
void T_dummy_service01::execute() {
    test_serviceCalls++;
}


/**
    ## T_dummy_service01 :: test_reset(..) - For test only: Reset dummy to init values ##
**/
void T_dummy_service01::test_reset() {
    test_serviceCalls = 0;
}


/**
    ## T_dummy_service01 :: test_getServiceCalls(..) - For test only: Return count of calls ##
**/
int T_dummy_service01::test_getServiceCalls() {
    return test_serviceCalls;
}
