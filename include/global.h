/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: global.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.08.2021
 **/

#ifndef GLOBAL_H
#define GLOBAL_H

#define APP_SHORTNAME   "GEMApp"
#define APP_FULLNAME    "Generic Embedded Main Application"

#define APP_VERSION     "0.0.1"


/**
    ## Global function pointers ##
**/
extern int (*callPrintf)(const char *, ...);
extern int (*callSystem)(const char *);


/**
    ## Global function prototypes ##
**/
int callSystem_Impl(const char *);


#endif
