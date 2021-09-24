/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: gema.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.09.2021
 **/

#include "../service/dummy_service01.h"

#include <stdlib.h>


T_dummy_service01 dummy_service01 = T_dummy_service01();


void execute_sync10ms() {
    dummy_service01.execute();
}
