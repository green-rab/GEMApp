/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: global.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.08.2021
 **/

#include <stdarg.h>
#include <stdio.h>
#include <cstdlib>

#include "../include/global.h"


int (*callPrintf)(const char * format, ...) = printf;
int (*callSystem)(const char * command) = callSystem_Impl;

int callSystem_Impl(const char * command) {
    #ifndef TESTMODE
    return system(command);
    #endif

    return 0;
}
