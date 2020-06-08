#ifndef MENU
#define MENU
#include "../../LED_Cube_library/LED_Cube_Library.h"
#include "Asleep.h"
class Menu
{
private:
    Asleep* asleep;
    App** apps;
    App** screenSaverApps;
    uint8_t max;
public:
    Menu(App**, uint8_t, App**, uint8_t);
    void run();
};
#endif