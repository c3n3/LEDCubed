#ifndef HELPFUL_FUNCTIONS
#define HELPFUL_FUNCTIONS
#include "Arduino.h"
#include "Basic_Functions.h"
#include "types.h"
class help
{
public:
    static uint16_t directionalCubeArray(uint8_t firstCord, uint8_t secondCord, uint8_t thirdCord, directions direction, boolean setLED = false, uint16_t color = 0);

    static void moveRow(uint8_t firstCoord, uint8_t secondCoord, directions viewPoint, uint16_t specificColor = 1, boolean collective = false, uint8_t start = 0, uint8_t end = 11, uint16_t color = 1);

    // delete all of a color on the entire cube
    static void eradicate(uint16_t color);

    //TODO: delete this thing if safe
    static void setRandomLED(uint8_t leds, directions direction, uint16_t color, boolean threeD = false);

    //no up or down yet
    static void angledMove(uint8_t rise, uint8_t run, directions direction, uint16_t color);

    // TODO: use a thought of c - 'a' to get this not huge function
    static uint8_t getFontIndex(char c);

    // draws a char c at the coordinates in the direction of the viewPoint with the color
    static void drawChar(char c, int x1, int y1, int z1, directions viewpoint, uint16_t color);

    // funciton to let continuous typing of characters on the cube, (it wraps chars around as space fills up)
    // static void typeChars(char c);

    // draws a box based on the 6 coordinates (Two Points in the cube) and the color (This thing definitley needs rewritting)
    static void DrawFigure(int x1, int y1, int z1, int x2, int y2, int z2, uint16_t color);

    // used to display scores of a game
    static void gameOverScore(int score);
};
#endif