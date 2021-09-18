/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: global.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 18.08.2021
 **/

#ifndef GLOBAL_H
#define GLOBAL_H

#define TESTMODE

#define APP_SHORTNAME   "GEMA"
#define APP_FULLNAME    "Generic Embedded Main Application"

#define APP_VERSION     "0.0.1"


extern int (*callPrintf)(const char *, ...);
extern int (*callSystem)(const char *);

int callSystem_Impl(const char *);


#endif
