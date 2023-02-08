/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: global.h
 * 
 * - https://github.com/green-rab/GEMApp
 * - Markus Gutermann, Germany, created: 18.08.2021
 **/

#include <stdarg.h>
#include <stdio.h>
#include <cstdlib>

#include "../include/global.h"


/**
    ## Global function pointers ##
**/
int (*callPrintf)(const char * format, ...) = printf;
int (*callSystem)(const char * command) = callSystem_Impl;


/**
    ## Global functions ##
**/
int callSystem_Impl(const char * command) {
    #ifndef TESTMODE
    return system(command);
    #endif

    return 0;
}
