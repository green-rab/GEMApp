# GEMApp #

The **Generic Embedded Main Application** is kind of a basic software for embedded boards like the Raspberry Pi, BeagleBone, etc. The goal is to decouple the part of initializing the hardware-ressources and cyclic call of the application code to let you focus on the real functionality.

Therefore you only have to prepare the config.h, add your source files (C++) to the userSerices-directory and register them in the gemapp.cpp. Please follow detailed the description in the HowTo-section.

*Actual version:* **0.1**

## Supported hardware ##

Devices:

- Raspberry Pi 4 _(other devices not tested at the moment but it should be working on most RPi's)_

Hardware ressources:

- GPIOs _(at the moment only following numbers: 05, 06, 12, 13, 26 - will be completed soon)_

## HowTo ##

### Clone repository ###

```bash
git clone https://github.com/green-rab/GEMApp.git
```

### Edit configuration ###

Open 'include/config.h' and edit the #define's:

```cpp
#define CONFIG_GPIO_05 INPUT
#define CONFIG_GPIO_06 INPUT
#define CONFIG_GPIO_12 OUTPUT
#define CONFIG_GPIO_13 UNUSED
#define CONFIG_GPIO_26 UNUSED
```

Every GPIO can have the mode INPUT, OUTPUT or UNUSED. At the moment no more GPIOs and other hardware-ressources are available.

### Include types to your code ###

Add 'include/gemapp.h' to your code. It specifies a type that is handed over by reference and includes the actual read hardware-inputs:

```cpp
struct t_GEMApp_data {
    bool GPIO_05;
    bool GPIO_06;
    bool GPIO_12;
    bool GPIO_13;
    bool GPIO_26;
};
```

In your code you have to directly manipulate the hardware-outputs that are then automatically written by GEMApp.

### Integrate your source-files ###

Copy your files to the folder 'userServices'. You can have a look at the files 'dummy_service' for an example.

Open 'source/gemapp.cpp' and declare your header-files:

```cpp
#include "../userServices/dummy_service.h"
```

If needed you can specify local variables (dummy_service is used as a class):

```cpp
T_dummy_service *dummy_service;
```

Then at the moment you can only choose a cyclic execution with a cycle of 10 ms. At the execution routine of your class or the function that has to be called in the following section:

```cpp
void execute_sync10ms(t_GEMApp_data &data) {
    dummy_service->execute(data);
}
```

Please add your used hardware-ressources in the startup-section. Optionally you can add something for your code at startup and shutdown e.g. initialization of your class:

```cpp
void execute_sync10ms_startup() {
    dummy_service = new T_dummy_service();

    execute_sync10ms_INPUTS.push_back(GPIO_05);
    execute_sync10ms_INPUTS.push_back(GPIO_06);
    execute_sync10ms_INPUTS.push_back(GPIO_13);
    execute_sync10ms_INPUTS.push_back(GPIO_26);

    execute_sync10ms_OUTPUTS.push_back(GPIO_12);
}

void execute_sync10ms_shutdown() {
    if(dummy_service) {
        delete dummy_service;
    }
    dummy_service = nullptr;
}
```

### Compile and execute your application ###

For compiling please do:

```bash
make rpi
```

The 'rpi' is very important without you are in a debug-session at build will fail, because it cannot find CppUTest.

If compiling is successful you can run your application:

```bash
bin/rpi/gemapp
```

Thats it! :)

## Look inside GEMApp ##

![GEMApp concept](https://lucid.app/publicSegments/view/85b31837-cd69-4143-89e4-9f37333d53a8/image.png "Concept")

## Version history ##

| Version | Date | Description |
| --- | --- | --- |
| 0.1     | tbd  | basic gpio, tested on RPi 4 |
