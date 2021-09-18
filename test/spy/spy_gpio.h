/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: spy_gpio.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 23.08.2021
 **/

#ifndef SPY_GPIO_H
#define SPY_GPIO_H

#include "../../include/res_gpio.h"


/**
    ## Constants ##
**/
#define CNT_GPIOS 100


/**
    ## ENUM T_enum_spy_gpioState(..) - State of single gpio ##
**/
enum T_enum_spy_gpioState {
    SPY_GPIO_UNUSED = 0,
    SPY_GPIO_RELEASED = 1,

    SPY_GPIO_INPUT = 10,
    SPY_GPIO_OUTPUT = 20
};


/**
    ## CLASS T_spy_gpio(..) - SPY for T_gpio ##
**/
class T_spy_gpio : public T_res_gpio {
    private:
        T_enum_spy_gpioState gpioState[CNT_GPIOS];
        bool gpioValue[CNT_GPIOS];
        bool gpioError[CNT_GPIOS];

    public:
        T_spy_gpio();
        ~T_spy_gpio();
        
        bool init(int num, bool asOutput);
        bool deinit(int num);

        bool getStateInit(int num, bool &state_init);
        bool getStateDirection(int num, bool &state_direction);

        bool read(int num, bool &value);
        bool write(int num, bool value);

        // only for test-cases
        void test_reset();
        void test_setError(int num);
        void test_setReadValue(int num, bool val);
        bool test_getWriteValue(int num);
        bool test_isReleased(int num);
};


#endif
