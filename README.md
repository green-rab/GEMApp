# GEMApp #

[[Overview](#overview)] [[Step by Step](#stepByStep)] [[Look inside](#lookInside)] [[Link to RabbitPro](#rabbitPro)] 

The **Generic Embedded Main Application** is kind of a basic software written in C++ for embedded boards like the Raspberry Pi. The goal is to decouple the part of initializing hardware-resources from the application code to let you focus on the implementation of your functionality.

![](pictures/GEMApp_concept.png)

<a name="overview"></a>
## Overview ##

Remarks:

- Please keep in mind it is a first **DEBUG** demo version with very limited functionality.

Version history:

<table width='800pt'>
	<tr>
		<th align="center">Version</th>
		<th align="left">New features</th>
		<th align="left">Resolved bugs</th>
	</tr>
	<tr></tr>
	<tr>
		<td align="center" valign="top">v0.1</td>
		<td align="left" valign="top">first version with limited hardware-resources<br>GPIOs supported: 05, 06, 12, 13, 26</td>
		<td align="left" valign="top">-</td>
	</tr>
</table>

Supported devices:

<table width='800pt'>
	<tr>
		<td align="left" valign="top">Raspberry Pi 4</td>
	</tr>
</table>

_Other devices are not tested at the moment but it should be working on several RPi's_

Supported hardware-resources:

<table width='800pt'>
	<tr>
		<td align="left" valign="top">GPIOs <I>(only following numbers: 05, 06, 12, 13, 26)</I></td>
	</tr>
</table>

Open points:

- [ ] Complete initialization for all gpio-resources
- [ ] Add communication interfaces

<a name="stepByStep"></a>
## Step by Step - How to use GEMApp for your own project ##

Checkout or clone the repository. You have to edit the following files to configure your desired hardware-resources and add your application code. It is explained in detail during the next steps:
- config.h
- gemapp.cpp

Add the following files to your code:
- gemapp.h

Place your source files into the folder 'userServices'

That's it! ..I have tried to keep it as simple as possible 

### 1. Edit config.h for your desired configuration ###

Open 'include/config.h' and choose your desired configuration for the hardware-resources. Therefore you have to edit the #define statements and choose one of the keywords INPUT, OUTPUT or UNUSED for every line.

```cpp
#define CONFIG_GPIO_05 INPUT
#define CONFIG_GPIO_06 INPUT
#define CONFIG_GPIO_12 OUTPUT
#define CONFIG_GPIO_13 UNUSED
#define CONFIG_GPIO_26 UNUSED
```

### 2. Include gemapp.h for the data type to your code ###

Add 'include/gemapp.h' to your code. It specifies a type that is handed over by reference and includes the actual read hardware-inputs. By writing to the reference you can write to the hardware-outputs that are handled after your code has finished.

```cpp
struct t_GEMApp_data {
    bool GPIO_05;
    bool GPIO_06;
    bool GPIO_12;
    bool GPIO_13;
    bool GPIO_26;
};
```


### 3. Copy your code to folder userServices ###

Copy your source files to the folder 'userServices'. You can have a look to the files 'dummy_service.cpp' and 'dummy_service.h' as an example.

### 4. Edit gemapp.cpp to register your runnables ###

Open 'source/gemapp.cpp' and declare your header-files:

```cpp
#include "../userServices/dummy_service.h"
```

If needed you can specify local variables (here 'dummy_service' is used and it is a class):

```cpp
T_dummy_service *dummy_service;
```

At the moment you can only choose a cyclic execution with a cycle time of 10 ms. Add the execution routine of your class or your function that has to be called in the following section:

```cpp
void execute_sync10ms(t_GEMApp_data &data) {
    dummy_service->execute(data);
}
```

Please add your used hardware-resources in the startup-section. Optionally you can add something for your code at startup and shutdown e.g. initialization of your class:

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

### 5. Compile and execute ###

For compiling please call make with parameter 'rpi': _(without parameter 'rpi' you are in a debug-session and build will fail)_

```bash
make rpi
```

If compile is successful done you can run your application:

```bash
bin/rpi/gemapp
```

<a name="lookInside"></a>
## Look inside - How does GEMApp works under the hood ##

The architecture of GEMApp is separated into three main parts:

- Enterprise Service Bus (ESB) _(source/esb.cpp)_
- Driver-Layer for hardware-resources _(source/ctrlDriver.cpp)_
- Service-Layer for user functionality _(source/ctrlService.cpp)_

The ESB is the main scheduler that initializes all abstraction layers, 'driver-layer' for hardware-resources and 'service-layer' for handling user application code.

_(Please note that all pictures are simplified and not fully detailed)_

### 1. Driver-Layer ###

The driver-layer initializes the whole hardware-resources. Therefore only one init function has to be called. The desired configuration is read from the 'config.h' and internally checked and interpreted. An invalid configuration throws back an error.

For all types of resources (GPIO, SPI, ...) drivers are implemented. All drivers are initialized by the ESB as own instances, too.

![](pictures/GEMApp_driverLayer.png)

### 2. Service-Layer ###

The service-layer is called after all hardware-resources are successfully initialized. It schedules the user functionality. Therefor it initializes an asynchronous timer with an interval of 10 ms that is called periodically. In future more timers oder event based schedulers are possible.

The function 'task_scheduleSync10ms' executes the user specified code following three steps every cyclic call:

1. Read all input values (e.g. GPIOs). The values are read by using the interface of the driver-layer. All values are stored in a struct with the name 'data'.
2. Call function execute_sync10ms(..) with the input values stored in data. The function has to be prepared by the user and calls directly user-specific functions or classes with 'data' as input parameter
3. Write back the returned values stored in 'data'. Therefore the driver-layer is called again to set the new output values (e.g. GPIOs)

![](pictures/GEMApp_serviceLayer.png)

<a name="rabbitPro"></a>
## Link to RabbitPro - What's coming next ##

The project GEMApp is a spinoff of my main project **RabbitPro** that will be a rapid prototyping environment to enable system development with a graphical programming interface.

The basic idea is to recycle functions that you have written ones and store the code in a library. Your solution connects functions in a graphical way and can be scaled to one or more devices. Finally single steps for configuration explained her are automatically done for you.

... First implementation already works. More is coming soon ...
