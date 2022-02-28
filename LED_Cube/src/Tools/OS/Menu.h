#ifndef MENU
#define MENU
#include "../../LED_Cube_library/LED_Cube_Library.h"
#include "Asleep.h"

/**
 * @brief This is the menu app which runs the selections of sub apps so that they can run themselves
 * 
 */
class Menu
{
private:

    // the asleep object as a pointer cus why not, it'll live fo eva anyway
    Asleep* asleep;

    // array of apps
    AppCtor* apps;

    // this is the screen savers to be used with the Asleep screen saver app (This can probably be moved to the constructor of the Asleep class, but I am lazy right now)
    AppCtor* screenSaverApps;

    // the size of the above array, no idea why I called it max
    uint8_t max;
public:
    /**
     * @brief Construct a new Menu object
     * 
     * @param apps the apps users of the cube can select
     * @param sizeApps size of apps array
     * @param screenSavers array of screen saver apps
     * @param sizeSavers this is the size of the savers array
     */
    Menu(AppCtor* apps, uint8_t sizeApps, AppCtor* screenSavers, uint8_t sizeSavers);

    // the run function that loops till the end of time (aka when the electrons stop flowing)
    void run();
};
#endif