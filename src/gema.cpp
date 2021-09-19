/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: gema.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

// // implementation for get-functions (config.h)
// static void dummy_service01_rawImpl();
// static void dummy_service02_rawImpl();

// // function pointers for service-dummys
// void (*dummy_service01_raw)();
// void (*dummy_service02_raw)();

// // set function pointers
// dummy_service01_raw = &dummy_service01_rawImpl;
// dummy_service02_raw = &dummy_service02_rawImpl;

// /**
//     ## PRIVATE T_service :: *_rawImpl() - Dummy service-implementation ##
    
//     - dummy_service01_rawImpl()
//     - dummy_service02_rawImpl()
// **/
// void T_service::dummy_service01_rawImpl() {}
// void T_service::dummy_service02_rawImpl() {}

#include "../service/dummy_service01.h"

#include <stdlib.h>


T_dummy_service01 dummy_service01 = T_dummy_service01();


void execute_sync10ms() {
    dummy_service01.execute();
}
