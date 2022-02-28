#ifndef HELPFUL_FUNCTIONS
#define HELPFUL_FUNCTIONS
#include "Arduino.h"
#include "Basic_Functions.h"
#include "../Tools/RelativeCoordinates/Relativistic.h"
#include "types.h"
/**
 * @brief this contains functions that can be very useful for making animation, but dont quite make the bare metal Basic_Functions.h standard
 * 
 */
class help
{
public:

    // this is a very badly written useful function, check out the definition for a better description
    static void moveRow(uint8_t firstCoord, uint8_t secondCoord, Relativistic::Directions viewPoint, uint16_t specificColor = 1, boolean collective = false, uint8_t start = 0, uint8_t end = 11, uint16_t color = 1);

    // delete all of a color on the entire cube
    static void eradicate(uint16_t color);

    //TODO: delete this thing if safe
    static void setRandomLED(uint8_t leds, Relativistic::Directions direction, uint16_t color, bool threeD = false);

    //no up or down yet
    static void angledMove(uint8_t rise, uint8_t run, Relativistic::Directions direction, uint16_t color);

    // used to make float values into integers
    static ui8 normalize(float& notNormal);

    // draws a box based on the 6 coordinates (Two Points in the cube) and the color (This thing definitley needs rewritting)
    static void DrawFigure(int x1, int y1, int z1, int x2, int y2, int z2, uint16_t color);
};
#endif