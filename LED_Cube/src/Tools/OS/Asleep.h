#ifndef ASLEEP
#define ASLEEP
#include "../../LED_Cube_library/globals.h"
#include "../../Apps/App.h"

/**
 * @brief This is bassically a screen saver for the cube, runs the given apps for a set amount of times
 * 
 */
class Asleep
{
private:
    // the apps as an array of pointers
    App** apps;

    // the size of the above array
    uint8_t size;
public:

    /**
     * @brief Construct a new Asleep object
     * 
     * @param arr the array of apps
     * @param size the size of the arr
     */
    Asleep(App** arr, uint8_t size);

    // this is the run function, bassically just goes through the apps 
    void go(uint32_t times = 0);
};
#endif