/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: spy_utilsOutput.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 22.08.2021
 **/

#include "spy_utilsOutput.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * T_spy_utilsOutput::buffer = NULL;
int T_spy_utilsOutput::bufferSize = 0;
int T_spy_utilsOutput::bufferOffset = 0;
int T_spy_utilsOutput::bufferUsed = 0;


T_spy_utilsOutput::T_spy_utilsOutput(int size) {
    create(size);
}


T_spy_utilsOutput::~T_spy_utilsOutput() {
    destroy();
}


void T_spy_utilsOutput::create(int size) {
    destroy();

    bufferSize = size + 1;
    buffer = (char *)calloc(bufferSize, sizeof(char));
    bufferOffset = 0;
    bufferUsed = 0;
    buffer[0] = '\0';
}


void T_spy_utilsOutput::destroy() {
    if(buffer == 0) return;

    free(buffer);
    buffer = 0;
}


int T_spy_utilsOutput::printf(const char * format, ...) {
    int writtenSize;
    va_list arguments;
    va_start(arguments, format);

    writtenSize = vsnprintf(buffer + bufferOffset, bufferSize - bufferUsed, format, arguments);

    bufferOffset += writtenSize;
    bufferUsed += writtenSize;

    return 1;
}


int T_spy_utilsOutput::system(const char * command) {
    int writtenSize;

    // writtenSize = sprintf(buffer + bufferOffset, "%s", command);
    // writtenSize = vsnprintf(buffer + bufferOffset, bufferSize - bufferUsed, "%s", command);
    int tmpSize = sizeof(buffer);
    strncat(buffer, command, bufferSize-bufferUsed-1);
    writtenSize = tmpSize - sizeof(buffer);

    bufferOffset += writtenSize;
    bufferUsed += writtenSize;

    return 1;
}


const char* T_spy_utilsOutput::getBuffer() {
    return buffer;
}
