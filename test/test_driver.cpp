/**
 * # GEMA - Generic Embedded Main Application #
 * 
 * - file: test_gpio.cpp
 * 
 * - https://gitlab.com/green-rab
 * - Markus Schmidt, Germany, created: 16.08.2021
 **/

#include "CppUTest/TestHarness.h"
// #include "CppUTestExt/MockSupport.h"

#include <string>
#include <sstream>
using namespace std;

#include "../include/driver.h"
#include "../include/global.h"

#include "spy/spy_utilsOutput.h"
#include "spy/spy_gpio.h"


/**
    ## TESTGROUP tg_config(..) - Test-group (tg) for 'config.h' including following testcases (tc) ##
**/
TEST_GROUP(tg_config) {
    // CUT code-under-test
    T_driver *cut_driver;

    void setup() {
        // init CUT
        cut_driver = new T_driver();
    }

    void teardown() {
        delete cut_driver;

        // mock().clear();
    }
};


/**
    Parameters for driver-layer are defined in the config.h by the user, using #define.

    Every single value has to be read as 'string' and checked for its standard-configuration,
    (definition for development).

    - TEST tc_config_rawDevice(..)
    - TEST tc_config_rawGpio05(..)
    - TEST tc_config_rawGpio06(..)
    - TEST tc_config_rawGpio12(..)
    - TEST tc_config_rawGpio13(..)
    - TEST tc_config_rawGpio26(..)
**/
TEST(tg_config, tc_config_rawDevice) {
    // init local variables
    string ret_configRaw;

    // preconditions

    // a.1: read 'device' constant in config.h
    ret_configRaw = cut_driver->getConfig_device_raw();
    printf("str_test CONFIG_DEVICE:  <%s>\n", ret_configRaw.c_str());

    // exp.1: check 'device' is a valid string
    CHECK_FALSE(ret_configRaw.compare("") == 0);
    CHECK_FALSE(ret_configRaw.compare("NONE") == 0);
    CHECK(ret_configRaw.compare("RASPBERRY_PI") == 0);
}
TEST(tg_config, tc_config_rawGpio05) {
    // init local variables
    string ret_configRaw;

    // preconditions

    // a.1: read 'gpio05' constant in config.h
    ret_configRaw = cut_driver->getConfig_gpio05_raw();
    printf("str_test CONFIG_GPIO_05: <%s>\n", ret_configRaw.c_str());

    // exp.1: check 'gpio05' is a valid string
    CHECK_FALSE(ret_configRaw.compare("") == 0);
    CHECK_FALSE(ret_configRaw.compare("UNUSED") == 0);
    CHECK(ret_configRaw.compare("INPUT") == 0);
    CHECK_FALSE(ret_configRaw.compare("OUTPUT") == 0);
}
TEST(tg_config, tc_config_rawGpio06) {
    // init local variables
    string ret_configRaw;

    // preconditions
 
    // a.1: read 'gpio06' constant in config.h
    ret_configRaw = cut_driver->getConfig_gpio06_raw();
    printf("str_test CONFIG_GPIO_06: <%s>\n", ret_configRaw.c_str());

    // exp.1: check 'gpio06' is a valid string
    CHECK_FALSE(ret_configRaw.compare("") == 0);
    CHECK_FALSE(ret_configRaw.compare("UNUSED") == 0);
    CHECK(ret_configRaw.compare("INPUT") == 0);
    CHECK_FALSE(ret_configRaw.compare("OUTPUT") == 0);
}
TEST(tg_config, tc_config_rawGpio12) {
    // init local variables
    string ret_configRaw;

    // preconditions

    // a.1: read 'gpio12' constant in config.h
    ret_configRaw = cut_driver->getConfig_gpio12_raw();
    printf("str_test CONFIG_GPIO_12: <%s>\n", ret_configRaw.c_str());

    // exp.1: check 'gpio12' is a valid string
    CHECK_FALSE(ret_configRaw.compare("") == 0);
    CHECK_FALSE(ret_configRaw.compare("UNUSED") == 0);
    CHECK_FALSE(ret_configRaw.compare("INPUT") == 0);
    CHECK(ret_configRaw.compare("OUTPUT") == 0);
}
TEST(tg_config, tc_config_rawGpio13) {
    // init local variables
    string ret_configRaw;

    // preconditions

    // a.1: read 'gpio13' constant in config.h
    ret_configRaw = cut_driver->getConfig_gpio13_raw();
    printf("str_test CONFIG_GPIO_13: <%s>\n", ret_configRaw.c_str());

    // exp.1: check 'gpio13' is a valid string
    CHECK_FALSE(ret_configRaw.compare("") == 0);
    CHECK_FALSE(ret_configRaw.compare("UNUSED") == 0);
    CHECK(ret_configRaw.compare("INPUT") == 0);
    CHECK_FALSE(ret_configRaw.compare("OUTPUT") == 0);
}
TEST(tg_config, tc_config_rawGpio26) {
    // init local variables
    string ret_configRaw;

    // preconditions

    // a.1: read 'gpio26' constant in config.h
    ret_configRaw = cut_driver->getConfig_gpio26_raw();
    printf("str_test CONFIG_GPIO_26: <%s>\n", ret_configRaw.c_str());

    // exp.1: check 'gpio26' is a valid string
    CHECK_FALSE(ret_configRaw.compare("") == 0);
    CHECK_FALSE(ret_configRaw.compare("UNUSED") == 0);
    CHECK(ret_configRaw.compare("INPUT") == 0);
    CHECK_FALSE(ret_configRaw.compare("OUTPUT") == 0);
}


/**
    ## STUBs for test config.h ##
**/
string stub_device;
string getConfig_device_rawStub() { return stub_device; }

string stub_gpio05;
string getConfig_gpio05_rawStub() { return stub_gpio05; }
string stub_gpio06;
string getConfig_gpio06_rawStub() { return stub_gpio06; }
string stub_gpio12;
string getConfig_gpio12_rawStub() { return stub_gpio12; }
string stub_gpio13;
string getConfig_gpio13_rawStub() { return stub_gpio13; }
string stub_gpio26;
string getConfig_gpio26_rawStub() { return stub_gpio26; }


/**
    ## TESTGROUP tg_driver(..) - Test-group (tg) for 'driver' including following testcases (tc) ##
**/
TEST_GROUP(tg_driver) {
    // CUT code-under-test
    T_driver *cut_driver;

    // SPYs
    T_spy_utilsOutput *spy_utilsOutput;
    T_spy_gpio        *spy_gpio;

    void setup() {
        // init SPYs
        spy_utilsOutput = new T_spy_utilsOutput(1000);
        spy_gpio        = new T_spy_gpio();

        // init STUBs
        stub_device = "NONE";
        stub_gpio05 = "UNUSED";
        stub_gpio06 = "UNUSED";
        stub_gpio12 = "UNUSED";
        stub_gpio13 = "UNUSED";
        stub_gpio26 = "UNUSED";
    
        // init CUT
        cut_driver = new T_driver();

        // set function pointers
        // UT_PTR_SET(cut_driver->getConfig_device_raw, &getConfig_device_rawStub);
        cut_driver->getConfig_device_raw = &getConfig_device_rawStub;

        // UT_PTR_SET(cut_driver->getConfig_gpio05_raw, &getConfig_gpio05_rawStub);
        // UT_PTR_SET(cut_driver->getConfig_gpio06_raw, &getConfig_gpio06_rawStub);
        // UT_PTR_SET(cut_driver->getConfig_gpio12_raw, &getConfig_gpio12_rawStub);
        // UT_PTR_SET(cut_driver->getConfig_gpio13_raw, &getConfig_gpio13_rawStub);
        // UT_PTR_SET(cut_driver->getConfig_gpio26_raw, &getConfig_gpio26_rawStub);
        cut_driver->getConfig_gpio05_raw = &getConfig_gpio05_rawStub;
        cut_driver->getConfig_gpio06_raw = &getConfig_gpio06_rawStub;
        cut_driver->getConfig_gpio12_raw = &getConfig_gpio12_rawStub;
        cut_driver->getConfig_gpio13_raw = &getConfig_gpio13_rawStub;
        cut_driver->getConfig_gpio26_raw = &getConfig_gpio26_rawStub;

        UT_PTR_SET(callPrintf, spy_utilsOutput->printf);

        // UT_PTR_SET(cut_driver->res_gpio, spy_gpio);
        cut_driver->res_gpio = spy_gpio;
    }

    void teardown() {
        delete cut_driver;
        cut_driver = NULL;

        delete spy_gpio;
        spy_gpio = NULL;

        delete spy_utilsOutput;
        spy_utilsOutput = NULL;

        // mock().clear();
    }

    void stub_setAllGpiosAsInput_RPi() {
        stub_device = "RASPBERRY_PI";

        stub_gpio05 = "INPUT";
        stub_gpio06 = "INPUT";
        stub_gpio12 = "INPUT";
        stub_gpio13 = "INPUT";
        stub_gpio26 = "INPUT";
    }

    void stub_setAllGpiosAsOutput_RPi() {
        stub_device = "RASPBERRY_PI";

        stub_gpio05 = "OUTPUT";
        stub_gpio06 = "OUTPUT";
        stub_gpio12 = "OUTPUT";
        stub_gpio13 = "OUTPUT";
        stub_gpio26 = "OUTPUT";
    }

    void check_allGpiosAreNotInitalized() {
        bool ret_gpio_init = false;

        CHECK_EQUAL(true, cut_driver->res_gpio->getStateInit(5, ret_gpio_init));
        CHECK_EQUAL(false, ret_gpio_init);
        CHECK_EQUAL(true, cut_driver->res_gpio->getStateInit(6, ret_gpio_init));
        CHECK_EQUAL(false, ret_gpio_init);
        CHECK_EQUAL(true, cut_driver->res_gpio->getStateInit(12, ret_gpio_init));
        CHECK_EQUAL(false, ret_gpio_init);
        CHECK_EQUAL(true, cut_driver->res_gpio->getStateInit(13, ret_gpio_init));
        CHECK_EQUAL(false, ret_gpio_init);
        CHECK_EQUAL(true, cut_driver->res_gpio->getStateInit(26, ret_gpio_init));
        CHECK_EQUAL(false, ret_gpio_init);
    }
};


/**
    The followings tests are using a spy for the user-configuration in 'config.h' for controllable output.

    The raw-values of the 'config.h' are read as 'string'. The single strings have to be interpreted as
    enum-values for the used hardware-device and the hardware-ressources, e.g. the mode of the GPIOs.
    Therefore enum values have to be defined in 'driver_enum.h'.

    - TEST tc_driver_configEnumDevice(..)
    - TEST tc_driver_configEnumGpios(..)
**/
TEST(tg_driver, tc_driver_configEnumDevice) {
    // init local variables
    T_enum_driverDevice ret_device;

    // preconditions

    // a.1: set stub 'NONE' and call function
    stub_device = "NONE";
    ret_device = cut_driver->getConfig_device();

    // exp.1: check device is read as NONE
    CHECK_EQUAL(NONE, ret_device);

    // a.2: set stub 'RASPBERRY_PI' and call function
    stub_device = "RASPBERRY_PI";
    ret_device = cut_driver->getConfig_device();

    // exp.2: check device is read as RASPBERRY_PI
    CHECK_EQUAL(RASPBERRY_PI, ret_device);

    // a.3: set stub 'RASPBERRY_P' (no valid entry) and call function
    stub_device = "RASPBERRY_P";
    ret_device = cut_driver->getConfig_device();

    // exp.3: check device is read as NONE (not equal a valid device)
    CHECK_EQUAL(NONE, ret_device);

    // a.4: set stub 'xyz' (no valid entry) and call function
    stub_device = "xyz";
    ret_device = cut_driver->getConfig_device();

    // exp.4: check device is read as NONE (not equal a valid device)
    CHECK_EQUAL(NONE, ret_device);

    // a.5: set stub '' (empty string) and call function
    stub_device = "";
    ret_device = cut_driver->getConfig_device();

    // exp.5: check device is read as NONE (not equal a valid device)
    CHECK_EQUAL(NONE, ret_device);
}
TEST(tg_driver, tc_driver_configEnumGpios) {
    // init local variables
    const int cnt = 5;
    T_enum_driverGpio ret_gpio05;
    T_enum_driverGpio ret_gpio06;
    T_enum_driverGpio ret_gpio12;
    T_enum_driverGpio ret_gpio13;
    T_enum_driverGpio ret_gpio26;

    // init test-data
    string data_stub_gpio[cnt] = {"UNUSED", "INPUT", "OUTPUT", "xyz", ""};
    T_enum_driverGpio exp_gpio[cnt] = {UNUSED, INPUT, OUTPUT, UNUSED, UNUSED};

    // preconditions

    for(int i=0; i<cnt; i++) {
        // a.x: set stub and call function for decode string to enum-value
        stub_gpio05 = data_stub_gpio[i];
        stub_gpio06 = data_stub_gpio[i];
        stub_gpio12 = data_stub_gpio[i];
        stub_gpio13 = data_stub_gpio[i];
        stub_gpio26 = data_stub_gpio[i];
        
        ret_gpio05 = cut_driver->getConfig_gpio05();
        ret_gpio06 = cut_driver->getConfig_gpio06();
        ret_gpio12 = cut_driver->getConfig_gpio12();
        ret_gpio13 = cut_driver->getConfig_gpio13();
        ret_gpio26 = cut_driver->getConfig_gpio26();

        // exp.x: check gpio is read with correct enum-value
        CHECK_EQUAL(exp_gpio[i], ret_gpio05);
        CHECK_EQUAL(exp_gpio[i], ret_gpio06);
        CHECK_EQUAL(exp_gpio[i], ret_gpio12);
        CHECK_EQUAL(exp_gpio[i], ret_gpio13);
        CHECK_EQUAL(exp_gpio[i], ret_gpio26);
    }
}


/**
    If a valid hardware-device is selected and at least one hardware-ressource is defined
    the initialization has to be successful. In other case the initialization has to fail.

    - TEST tc_driver_initNone_noRessource(..)
    - TEST tc_driver_initRPi_noRessource(..)
    - TEST tc_driver_initRPi_oneGpio(..)
**/
TEST(tg_driver, tc_driver_initNone_noRessource) {
    // init local variables
    bool ret_init = false;
    ostringstream test_stream;

    // preconditions
    stub_device = "NONE";

    // exp.0: check state is init
    CHECK_EQUAL(INIT, cut_driver->getState());

    // a.1: call init function
    ret_init = cut_driver->init();

    // exp.1: check return and output test
    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());

    test_stream.str("");
    test_stream.clear();
    test_stream << "-> ABORT: Initialization as " << stub_device << " is not valid\n";
    STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
}
TEST(tg_driver, tc_driver_initRPi_noRessource) {
    // init local variables
    bool ret_init = false;
    ostringstream test_stream;

    // preconditions
    stub_device = "RASPBERRY_PI";

    // exp.0: check state is init
    CHECK_EQUAL(INIT, cut_driver->getState());

    // a.1: call init function
    ret_init = cut_driver->init();

    // exp.1: check return and output test
    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());

    test_stream.str("");
    test_stream.clear();
    test_stream << "-> ABORT: Initialization as " << stub_device << " with no hardware-ressource is not valid\n";
    STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
}
TEST(tg_driver, tc_driver_initRPi_oneGpio) {
    // init local variables
    bool ret_init = false;
    ostringstream test_stream;

    // preconditions
    stub_device = "RASPBERRY_PI";
    stub_gpio05 = "INPUT";

    // exp.0: check state is init
    CHECK_EQUAL(INIT, cut_driver->getState());

    // a.1: call init function
    ret_init = cut_driver->init();

    // exp.1: check return and output test
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    test_stream.str("");
    test_stream.clear();
    test_stream << "-> Initialization as " << stub_device << "...\n";
    test_stream << ".. GPIO 05 - set as " << stub_gpio05 << "\n";
    STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
}


/**
    If the device is already initialized a new initialization shall be denied. After a successful
    reset the initialization is available again.

    - TEST tc_driver_initTwice(..)
    - TEST tc_driver_reset(..)
**/
TEST(tg_driver, tc_driver_initTwice) {
    // init local variables
    bool ret_init = false;
    ostringstream test_stream;

    // preconditions
    stub_device = "RASPBERRY_PI";
    stub_gpio05 = "INPUT";
    cut_driver->init();
    spy_utilsOutput->create(100);

    // exp.0: check state is init
    CHECK_EQUAL(RUN, cut_driver->getState());

    // a.1: call init function again
    ret_init = cut_driver->init();

    // exp.1: check return and output test
    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    test_stream.str("");
    test_stream.clear();
    test_stream << "-> ERROR: Device already initialized\n";
    STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
}
TEST(tg_driver, tc_driver_reset) {
    // init local variables
    bool ret_init  = false;
    bool ret_reset = false;
    ostringstream test_stream;

    // preconditions
    stub_device = "RASPBERRY_PI";
    stub_gpio05 = "INPUT";
    cut_driver->init();
    spy_utilsOutput->create(100);

    // a.1: call reset function (-> release all hardware-ressources)
    ret_reset = cut_driver->reset();

    // exp.1: check state is INIT again
    CHECK_EQUAL(true, ret_reset);
    CHECK_EQUAL(INIT, cut_driver->getState());

    test_stream.str("");
    test_stream.clear();
    test_stream << "-> Device successfully reseted\n";
    STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());

    // a.2: call init function again
    ret_init = cut_driver->init();

    // exp.2: check state is RUN again
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    test_stream << "-> Initialization as " << stub_device << "...\n";
    test_stream << ".. GPIO 05 - set as " << stub_gpio05 << "\n";
    STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
}


/**
    For every defined GPIO the intialization should be possible as INPUT and OUTPUT. GPIOs that
    are declared as UNUSED have to be ignored.

    - TEST tc_driver_initRPi_allGpio(..)
**/
TEST(tg_driver, tc_driver_initRPi_allGpio) {
    // init local variables
    const int     cnt = 12;
    ostringstream test_stream;
    bool          ret_gpio_init = false;
    bool          ret_gpio_dir  = false;
    bool          ret_init      = false;

    // init test-data
    string data_stub_gpio05[cnt] = {"INPUT", "OUTPUT", "",      "",       "",      "",       "",       "",      "",      "",       "INPUT", "OUTPUT" };
    bool check_gpio05_init[cnt]  = {true,    true,     false,   false,    false,   false,    false,   false,    false,   false,    true,    true     };
    bool check_gpio05_dir[cnt]   = {false,   true,     false,   false,    false,   false,    false,   false,    false,   false,    false,   true     };
    string data_stub_gpio06[cnt] = {"",      "",       "INPUT", "OUTPUT", "",      "",       "",       "",      "",      "",       "INPUT", "OUTPUT" };
    bool check_gpio06_init[cnt]  = {false,   false,    true,    true,     false,   false,    false,   false,    false,   false,    true,    true     };
    bool check_gpio06_dir[cnt]   = {false,   false,    false,   true,     false,   false,    false,   false,    false,   false,    false,   true     };
    string data_stub_gpio12[cnt] = {"",      "",       "",      "",       "INPUT", "OUTPUT", "",       "",      "",      "",       "INPUT", "OUTPUT" };
    bool check_gpio12_init[cnt]  = {false,   false,    false,   false,    true,    true,     false,   false,    false,   false,    true,    true     };
    bool check_gpio12_dir[cnt]   = {false,   false,    false,   false,    false,   true,     false,   false,    false,   false,    false,   true     };
    string data_stub_gpio13[cnt] = {"",      "",       "",      "",       "",      "",       "INPUT", "OUTPUT", "",      "",       "INPUT", "OUTPUT" };
    bool check_gpio13_init[cnt]  = {false,   false,    false,   false,    false,   false,    true,    true,     false,   false,    true,    true     };
    bool check_gpio13_dir[cnt]   = {false,   false,    false,   false,    false,   false,    false,   true,     false,   false,    false,   true     };
    string data_stub_gpio26[cnt] = {"",      "",       "",      "",       "",      "",       "",       "",      "INPUT", "OUTPUT", "INPUT", "OUTPUT" };
    bool check_gpio26_init[cnt]  = {false,   false,    false,   false,    false,   false,    false,   false,    true,    true,     true,    true     };
    bool check_gpio26_dir[cnt]   = {false,   false,    false,   false,    false,   false,    false,   false,    false,   true,     false,   true     };


    for(int i=0; i<cnt; i++) {
        // preconditions
        stub_device = "RASPBERRY_PI";

        stub_gpio05 = data_stub_gpio05[i];
        stub_gpio06 = data_stub_gpio06[i];
        stub_gpio12 = data_stub_gpio12[i];
        stub_gpio13 = data_stub_gpio13[i];
        stub_gpio26 = data_stub_gpio26[i];

        cut_driver->reset();

        spy_utilsOutput->create(1000);
        spy_gpio->test_reset();

        // exp.0: check state is init
        CHECK_EQUAL(INIT, cut_driver->getState());

        // a.x: call code-under-test
        ret_init = cut_driver->init();

        // exp.x: check expected results
        ret_gpio_init = cut_driver->res_gpio->getStateDirection(5, ret_gpio_dir);
        CHECK_EQUAL(check_gpio05_init[i], ret_gpio_init);
        CHECK_EQUAL(check_gpio05_dir[i], ret_gpio_dir);
        ret_gpio_init = cut_driver->res_gpio->getStateDirection(6, ret_gpio_dir);
        CHECK_EQUAL(check_gpio06_init[i], ret_gpio_init);
        CHECK_EQUAL(check_gpio06_dir[i], ret_gpio_dir);
        ret_gpio_init = cut_driver->res_gpio->getStateDirection(12, ret_gpio_dir);
        CHECK_EQUAL(check_gpio12_init[i], ret_gpio_init);
        CHECK_EQUAL(check_gpio12_dir[i], ret_gpio_dir);
        ret_gpio_init = cut_driver->res_gpio->getStateDirection(13, ret_gpio_dir);
        CHECK_EQUAL(check_gpio13_init[i], ret_gpio_init);
        CHECK_EQUAL(check_gpio13_dir[i], ret_gpio_dir);
        ret_gpio_init = cut_driver->res_gpio->getStateDirection(26, ret_gpio_dir);
        CHECK_EQUAL(check_gpio26_init[i], ret_gpio_init);
        CHECK_EQUAL(check_gpio26_dir[i], ret_gpio_dir);

        CHECK_EQUAL(true, ret_init);
        CHECK_EQUAL(RUN, cut_driver->getState());

        test_stream.str("");
        test_stream.clear();
        test_stream << "-> Initialization as " << stub_device << "...\n";
        if(!data_stub_gpio05[i].empty()) test_stream << ".. GPIO 05 - set as " << stub_gpio05 << "\n";
        if(!data_stub_gpio06[i].empty()) test_stream << ".. GPIO 06 - set as " << stub_gpio06 << "\n";
        if(!data_stub_gpio12[i].empty()) test_stream << ".. GPIO 12 - set as " << stub_gpio12 << "\n";
        if(!data_stub_gpio13[i].empty()) test_stream << ".. GPIO 13 - set as " << stub_gpio13 << "\n";
        if(!data_stub_gpio26[i].empty()) test_stream << ".. GPIO 26 - set as " << stub_gpio26 << "\n";
        STRCMP_EQUAL(test_stream.str().c_str(), spy_utilsOutput->getBuffer());
    }
}


/**
    If one GPIO-intialization fails initialization has to abort and all already intialized GPIOs
    have to be released again.

    - TEST tc_driver_initRPi_failGpio05_input(..)
    - TEST tc_driver_initRPi_failGpio05_output(..)
    - TEST tc_driver_initRPi_failGpio06_input(..)
    - TEST tc_driver_initRPi_failGpio06_output(..)
    - TEST tc_driver_initRPi_failGpio12_input(..)
    - TEST tc_driver_initRPi_failGpio12_output(..)
    - TEST tc_driver_initRPi_failGpio13_input(..)
    - TEST tc_driver_initRPi_failGpio13_output(..)
    - TEST tc_driver_initRPi_failGpio26_input(..)
    - TEST tc_driver_initRPi_failGpio26_output(..)
**/
TEST(tg_driver, tc_driver_initRPi_failGpio05_input) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsInput_RPi();

    // a.1: set gpio 05 fails in spy and call init
    spy_gpio->test_setError(5);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}
TEST(tg_driver, tc_driver_initRPi_failGpio05_output) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsOutput_RPi();

    // a.1: set gpio 05 fails in spy and call init
    spy_gpio->test_setError(5);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}
TEST(tg_driver, tc_driver_initRPi_failGpio06_input) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsInput_RPi();

    // a.1: set gpio 06 fails in spy and call init
    spy_gpio->test_setError(6);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();
    CHECK_EQUAL(true, spy_gpio->test_isReleased(5));

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}
TEST(tg_driver, tc_driver_initRPi_failGpio06_output) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsOutput_RPi();

    // a.1: set gpio 06 fails in spy and call init
    spy_gpio->test_setError(6);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();
    CHECK_EQUAL(true, spy_gpio->test_isReleased(5));

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}
TEST(tg_driver, tc_driver_initRPi_failGpio12_input) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsInput_RPi();

    // a.1: set gpio 12 fails in spy and call init
    spy_gpio->test_setError(12);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();
    CHECK_EQUAL(true, spy_gpio->test_isReleased(5));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(6));

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}
TEST(tg_driver, tc_driver_initRPi_failGpio12_output) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsOutput_RPi();

    // a.1: set gpio 12 fails in spy and call init
    spy_gpio->test_setError(12);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();
    CHECK_EQUAL(true, spy_gpio->test_isReleased(5));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(6));

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}
TEST(tg_driver, tc_driver_initRPi_failGpio13_input) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsInput_RPi();

    // a.1: set gpio 13 fails in spy and call init
    spy_gpio->test_setError(13);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();
    CHECK_EQUAL(true, spy_gpio->test_isReleased(5));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(6));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(12));

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}
TEST(tg_driver, tc_driver_initRPi_failGpio13_output) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsOutput_RPi();

    // a.1: set gpio 13 fails in spy and call init
    spy_gpio->test_setError(13);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();
    CHECK_EQUAL(true, spy_gpio->test_isReleased(5));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(6));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(12));

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}
TEST(tg_driver, tc_driver_initRPi_failGpio26_input) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsInput_RPi();

    // a.1: set gpio 26 fails in spy and call init
    spy_gpio->test_setError(26);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();
    CHECK_EQUAL(true, spy_gpio->test_isReleased(5));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(6));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(12));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(13));

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}
TEST(tg_driver, tc_driver_initRPi_failGpio26_output) {
    // init local variables
    bool ret_init = false;

    // preconditions
    stub_setAllGpiosAsOutput_RPi();

    // a.1: set gpio 26 fails in spy and call init
    spy_gpio->test_setError(26);
    ret_init = cut_driver->init();

    // exp.1: check all relevant gpios are released
    check_allGpiosAreNotInitalized();
    CHECK_EQUAL(true, spy_gpio->test_isReleased(5));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(6));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(12));
    CHECK_EQUAL(true, spy_gpio->test_isReleased(13));

    CHECK_EQUAL(false, ret_init);
    CHECK_EQUAL(ERROR, cut_driver->getState());
}


/**
    If GPIO is succesfully initialized as input it has to be able to read.

    - TEST tc_driver_gpioRead(..)
**/
TEST(tg_driver, tc_driver_gpioRead) {
    // init local variables
    bool ret_init = false;
    bool ret_gpio05 = false;
    bool ret_gpio06 = false;

    // preconditions
    stub_setAllGpiosAsInput_RPi();
    ret_init = cut_driver->init();

    // exp.0: check initialization state
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    // a.1: set stub value for gpio 05 and call read
    spy_gpio->test_setReadValue(5, true);
    ret_gpio05 = cut_driver->gpioRead(5);

    // exp.1: check modified value
    CHECK_EQUAL(true, ret_gpio05);

    // a.2: set stub value for gpio 06 and call read
    spy_gpio->test_setReadValue(6, true);
    ret_gpio06 = cut_driver->gpioRead(6);

    // exp.2: check modified value
    CHECK_EQUAL(true, ret_gpio06);
}


/**
    If GPIO is read but it is not intialized it has to return 'false' as default.

    - TEST tc_driver_gpioRead_noInit(..)
**/
TEST(tg_driver, tc_driver_gpioRead_noInit) {
    // init local variables
    bool ret_init = false;
    bool ret_gpio06 = true;

    // preconditions
    stub_device = "RASPBERRY_PI";
    stub_gpio05 = "INPUT";
    ret_init = cut_driver->init();

    // exp.0: check initialization state
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    // a.1: set stub value for gpio 06 and call read (gpio is not initialzed)
    spy_gpio->test_setReadValue(6, true);
    ret_gpio06 = cut_driver->gpioRead(6);

    // exp.1: check modified value
    CHECK_EQUAL(false, ret_gpio06);
}


/**
    If GPIO is read but it is initialied as output it has to return 'false' as default.

    - TEST tc_driver_gpioRead_initAsOutput(..)
**/
TEST(tg_driver, tc_driver_gpioRead_initAsOutput) {
    // init local variables
    bool ret_init = false;
    bool ret_gpio06 = true;

    // preconditions
    stub_device = "RASPBERRY_PI";
    stub_gpio06 = "OUTPUT";
    ret_init = cut_driver->init();

    // exp.0: check initialization state
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    // a.1: set stub value for gpio 06 and call read (gpio is not initialzed)
    spy_gpio->test_setReadValue(6, true);
    ret_gpio06 = cut_driver->gpioRead(6);

    // exp.1: check modified value
    CHECK_EQUAL(false, ret_gpio06);
}


/**
    If GPIO is read but the request fails it has to return 'false' as default.

    - TEST tc_driver_gpioRead_fail(..)
**/
TEST(tg_driver, tc_driver_gpioRead_fail) {
    // init local variables
    bool ret_init = false;
    bool ret_gpio06 = true;

    // preconditions
    stub_device = "RASPBERRY_PI";
    stub_gpio06 = "INPUT";
    ret_init = cut_driver->init();

    // exp.0: check initialization state
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    // a.1: set stub value and error-mode for gpio 06 and call read (gpio is not initialzed)
    spy_gpio->test_setReadValue(6, true);
    spy_gpio->test_setError(6);
    ret_gpio06 = cut_driver->gpioRead(6);

    // exp.1: check modified value
    CHECK_EQUAL(false, ret_gpio06);
}


/**
    If GPIO is succesfully initialized as output it has to be able to write.

    - TEST tc_driver_gpioWrite(..)
**/
TEST(tg_driver, tc_driver_gpioWrite) {
    // init local variables
    bool ret_init = false;
    bool ret_gpio05 = false;
    bool ret_gpio06 = false;

    // preconditions
    stub_setAllGpiosAsOutput_RPi();
    ret_init = cut_driver->init();

    // exp.0: check initialization state
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    // a.1: call write for gpio 05
    ret_gpio05 = cut_driver->gpioWrite(5, true);

    // exp.1: check return and write value
    CHECK_EQUAL(true, ret_gpio05);
    CHECK_EQUAL(true, spy_gpio->test_getWriteValue(5));

    // a.2: call write for gpio 06
    ret_gpio06 = cut_driver->gpioWrite(6, false);

    // exp.2: check return and write value
    CHECK_EQUAL(true, ret_gpio06);
    CHECK_EQUAL(false, spy_gpio->test_getWriteValue(6));
}


/**
    If GPIO is written but it is not intialized it has to return 'false'.

    - TEST tc_driver_gpioWrite_noInit(..)
**/
TEST(tg_driver, tc_driver_gpioWrite_noInit) {
    // init local variables
    bool ret_init = false;
    bool ret_gpio06 = true;

    // preconditions
    stub_device = "RASPBERRY_PI";
    stub_gpio05 = "OUTPUT";
    ret_init = cut_driver->init();

    // exp.0: check initialization state
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    // a.1: call write for gpio 06 (gpio is not initialzed)
    ret_gpio06 = cut_driver->gpioWrite(6, true);

    // exp.1: check return value
    CHECK_EQUAL(false, ret_gpio06);
}


/**
    If GPIO is written but it is initialied as input it has to return 'false'.

    - TEST tc_driver_gpioWrite_initAsInput(..)
**/
TEST(tg_driver, tc_driver_gpioWrite_initAsInput) {
    // init local variables
    bool ret_init = false;
    bool ret_gpio06 = true;

    // preconditions
    stub_device = "RASPBERRY_PI";
    stub_gpio06 = "INPUT";
    ret_init = cut_driver->init();

    // exp.0: check initialization state
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    // a.1: set stub value for gpio 06 and call read (gpio is not initialzed)
    ret_gpio06 = cut_driver->gpioWrite(6, true);

    // exp.1: check modified value
    CHECK_EQUAL(false, ret_gpio06);
}


/**
    If GPIO is written but the request fails it has to return 'false'.

    - TEST tc_driver_gpioWrite_fail(..)
**/
TEST(tg_driver, tc_driver_gpioWrite_fail) {
    // init local variables
    bool ret_init = false;
    bool ret_gpio06 = true;

    // preconditions
    stub_device = "RASPBERRY_PI";
    stub_gpio06 = "OUTPUT";
    ret_init = cut_driver->init();

    // exp.0: check initialization state
    CHECK_EQUAL(true, ret_init);
    CHECK_EQUAL(RUN, cut_driver->getState());

    // a.1: set stub value and error-mode for gpio 06 and call read (gpio is not initialzed)
    spy_gpio->test_setError(6);
    ret_gpio06 = cut_driver->gpioWrite(6, true);

    // exp.1: check modified value
    CHECK_EQUAL(false, ret_gpio06);
}
