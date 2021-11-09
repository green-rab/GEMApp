/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: spy_ctrlDriver.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 07.10.2021
 **/

#ifndef SPY_CTRLDRIVER_H
#define SPY_CTRLDRIVER_H

#include "../../include/unit/ctrlDriver.h"
#include "../../include/unit/drvGpio.h"


/**
    ## Constants ##
**/
#define CNT_GPIOS 100


/**
    ## CLASS T_spy_ctrlDriver(..) - SPY for T_ctrlDriver ##
**/
class T_spy_ctrlDriver : public T_ctrlDriver {
    private:
        bool gpioValue[CNT_GPIOS];

    public:
        T_spy_ctrlDriver(T_drvGpio *inst_drvGpio);
        ~T_spy_ctrlDriver();

        bool gpioRead(int num);
        bool gpioWrite(int num, bool value);

        // only for test-cases
        void test_reset();
        void test_setReadValue(int num, bool val);
        bool test_getWriteValue(int num);
};


#endif
