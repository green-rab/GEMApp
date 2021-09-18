/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: resgpio.h
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 13.08.2021
 **/

#ifndef RES_GPIO_H
#define RES_GPIO_H


/**
    ## CLASS T_res_gpio(..) - Driver-Layer control GPIO ressources ##
**/
class T_res_gpio {
    private:

    public:
        T_res_gpio();
        ~T_res_gpio();

        virtual bool init(int num, bool asOutput);
        virtual bool deinit(int num);

        virtual bool getStateInit(int num, bool &state_init);
        virtual bool getStateDirection(int num, bool &state_direction);

        virtual bool read(int num, bool &value);
        virtual bool write(int num, bool value);
};


#endif
