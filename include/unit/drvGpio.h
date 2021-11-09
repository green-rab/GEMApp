/**
 * # GEMApp - Generic Embedded Main Application #
 * 
 * - file: drvGpio.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 13.08.2021
 **/

#ifndef DRVGPIO_H
#define DRVGPIO_H


/**
    ## CLASS T_drvGpio(..) - Control of GPIO ressources ##
**/
class T_drvGpio {
    private:

    public:
        T_drvGpio();
        ~T_drvGpio();

        virtual bool init(int num, bool asOutput);
        virtual bool deinit(int num);

        virtual bool getStateInit(int num, bool &state_init);
        virtual bool getStateDirection(int num, bool &state_direction);

        virtual bool read(int num, bool &value);
        virtual bool write(int num, bool value);
};


#endif
