/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: spy_utilsOutput.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 23.08.2021
 **/

#ifndef SPY_UTILSOUTPUT_H
#define SPY_UTILSOUTPUT_H


/**
    ## CLASS T_spy_utilsOutput(..) - SPY to check calls of printf and system ##
**/
class T_spy_utilsOutput {
    private:
        static char * buffer;
        static int bufferSize;
        static int bufferOffset;
        static int bufferUsed;

    public:
        T_spy_utilsOutput(int size);
        ~T_spy_utilsOutput();

        void create(int size);
        void destroy();

        static int printf(const char * format, ...);
        static int system(const char * command);

        const char* getBuffer();
};


#endif
