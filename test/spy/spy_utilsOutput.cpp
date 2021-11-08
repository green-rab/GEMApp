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
#include <string>


char * T_spy_utilsOutput::buffer = NULL;
int T_spy_utilsOutput::bufferSize = 0;
int T_spy_utilsOutput::bufferOffset = 0;
int T_spy_utilsOutput::bufferUsed = 0;


/**
    ## T_spy_utilsOutput :: Constructor ##
**/
T_spy_utilsOutput::T_spy_utilsOutput(int size) {
    create(size);
}


/**
    ## T_spy_utilsOutput :: Destructor ##
**/
T_spy_utilsOutput::~T_spy_utilsOutput() {
    destroy();
}


/**
    ## T_spy_utilsOutput :: create(..) - Create a new empty buffer with specified size ##
**/
void T_spy_utilsOutput::create(int size) {
    destroy();

    bufferSize = size + 1;
    buffer = (char *)calloc(bufferSize, sizeof(char));
    bufferOffset = 0;
    bufferUsed = 0;
    buffer[0] = '\0';
}


/**
    ## T_spy_utilsOutput :: destroy() - Destroy current buffer ##
**/
void T_spy_utilsOutput::destroy() {
    if(buffer == 0) return;

    free(buffer);
    buffer = 0;
}


/**
    ## T_spy_utilsOutput :: printf(..) - Output as 'printf' ##
**/
int T_spy_utilsOutput::printf(const char * format, ...) {
    int writtenSize;
    va_list arguments;
    va_start(arguments, format);

    writtenSize = vsnprintf(buffer + bufferOffset, bufferSize - bufferUsed, format, arguments);

    bufferOffset += writtenSize;
    bufferUsed += writtenSize;

    return 1;
}


/**
    ## T_spy_utilsOutput :: printf(..) - Output as 'system' ##
**/
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


/**
    ## T_spy_utilsOutput :: getBuffer() - Return actual buffer ##
**/
const char* T_spy_utilsOutput::getBuffer() {
    return buffer;
}


/**
    ## T_spy_utilsOutput :: checkBuffer(..) - Check for specified text if included in buffer ##
**/
bool T_spy_utilsOutput::checkBuffer(const char * text) {
    std::string strBuffer(buffer);
    std::string strText(text);

    if(strBuffer.find(strText) != std::string::npos) {
        return true;
    }

    return false;
}
