#ifndef ASLEEP
#define ASLEEP 0

// #ifndef GLOBALS
#include "../../LED_Cube_library/globals.h"
// #endif

// #ifndef APP
#include "../../Apps/App.h"
// #endif

class Asleep
{
private:
    App** apps;
    uint8_t max;
public:
    Asleep(App**, uint8_t);
    void go(uint32_t times = 0, bool nothing = false);
};
#endif