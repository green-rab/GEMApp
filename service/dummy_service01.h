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


/**
    ## CLASS T_dummy_service01(..) - Dummy service 01 for development ##
**/
class T_dummy_service01 {
    private:
        int test_serviceCalls;

    public:
        T_dummy_service01();
        ~T_dummy_service01();

        // calls
        void execute();

        // only for test-cases
        void test_reset();
        int test_getServiceCalls();
};


#endif
