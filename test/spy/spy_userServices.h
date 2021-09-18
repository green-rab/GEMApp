/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: spy_userServices.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

#ifndef SPY_USER_SERVICES_H
#define SPY_USER_SERVICES_H

// #include "../../include/res_gpio.h"


/**
    ## Constants ##
**/
#define CNT_SERVICES 2


/**
    ## CLASS T_spy_userServices(..) - SPY for user-services ##
**/
class T_spy_userServices {
    private:
        int serviceCalls[CNT_SERVICES];

    public:
        T_spy_userServices();
        ~T_spy_userServices();
        
        void userService_01();
        void userService_02();

        // only for test-cases
        int test_getServiceCalls(int service);
};


#endif
