/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: spy_driver.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 07.10.2021
 **/

#ifndef SPY_DRIVER_H
#define SPY_DRIVER_H

#include "../../include/driver.h"


/**
    ## Constants ##
**/
#define CNT_GPIOS 100


/**
    ## CLASS T_spy_driver(..) - SPY for T_driver ##
**/
class T_spy_driver : public T_driver {
    private:
        bool gpioValue[CNT_GPIOS];

    public:
        T_spy_driver();
        ~T_spy_driver();

        bool gpioRead(int num);
        bool gpioWrite(int num, bool value);

        // only for test-cases
        void test_reset();
        void test_setReadValue(int num, bool val);
        bool test_getWriteValue(int num);
};


#endif
