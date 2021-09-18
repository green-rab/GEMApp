/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: spy_userServices.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

#include "spy_userServices.h"


/**
    ## T_spy_userServices :: Constructor ##
**/
T_spy_userServices::T_spy_userServices() {
    for(int i = 0; i<CNT_SERVICES; i++) {
        serviceCalls[i] = 0;
    }
}


/**
    ## T_spy_userServices :: Destructor ##
**/
T_spy_userServices::~T_spy_userServices() {
}


/**
    ## T_spy_userServices :: userService_01() - Dummy user-service 01 ##
**/
void T_spy_userServices::userService_01() {
    serviceCalls[0]++;
}


/**
    ## T_spy_userServices :: userService_02() - Dummy user-service 02 ##
**/
void T_spy_userServices::userService_02() {
    serviceCalls[1]++;
}


/**
    ## T_spy_userServices :: test_getServiceCalls(..) - For test only: Return count of calls ##
**/
int T_spy_userServices::test_getServiceCalls(int service) {
    if(service >= (CNT_SERVICES + 1)) {
        return -1;
    }

    return serviceCalls[--service];
}
