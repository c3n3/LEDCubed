#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#ifndef TYPEDEF_H
#include "typedef.h"
#endif
#if defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE
/**************************************************************************
 *
 *
 *
 *  Functions to aid animations/games below
 *
 *
 *
 **************************************************************************/


//Coordinates and RGB values and buffer. RGB range 0-255
void set_led( uint8_t, uint8_t, uint8_t, uint16_t, uint16_t, uint16_t);

/***************************************************************************
 *

 *
 ***************************************************************************/

// will not destroy the program if you set a nonexistant LED
void protected_set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

// a delay function that accounts for pressing the escape key
char d(uint16_t t);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//packs a rgb color into one number
uint16_t pk_color(uint16_t r, uint16_t g, uint16_t b);


/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

// red goes up to 31
//blue to 31
//green up to 63
uint16_t pk_low(uint16_t r, uint16_t g, uint16_t b);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

// a packed coordinate
uint16_t pk_coord(uint8_t x, uint8_t y, uint8_t z);


/***************************************************************************
 *
 *   Shifter Function used by the main switch to display the current state
 *
 ***************************************************************************/

uint8_t shifter(uint8_t k, directions more, mainStates state);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//self explainatory
void clearCube();

//void adressToCoordinate

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//houses the data for the whole cube (wrapper function for the px_buf array )
uint16_t LEDArray(uint8_t x, uint8_t y, uint8_t z);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//Set led with packed color value
void set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//Set led with packed color value by address
void setAddressLED( uint16_t address, uint16_t c);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

// set led by packed coordinates and packed color
void setPackedPackedLED(uint16_t coord, uint16_t c);


/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//this function switches which orientation you may look at the cube,
// very very useful function, allows writting other helper functions in terms of a direction so that you dont have to have 6 types of the same function for each direction
// the  coordinates go as follows, the face you look at for each direction, the reletive 'z' coordinate is the third one, the reletive 'x' is either the true z or x direction, and the second coordinate is always the reletive 'y'
uint16_t directionalCubeArray(uint8_t firstCord, uint8_t secondCord, uint8_t thirdCord, directions direction, boolean setLED = false, uint16_t color = 0);

/***************************************************************************
 *
 *   Unfinished Function below
 *
 ***************************************************************************/

void rotate(uint16_t t);

/***************************************************************************
 *
 *   Move Row function, (This is a stupid ugly function)
 *   firstCoord and secondCoord determine which row will be shifted in accordance with the specified viewPoint
 *   viewPoint determines which plane will be looked at for the two coordinates to shift there row
 *   specificColor tells it which color it should shift in the cube default is 1, this will shift all colors
 *   collective determines whether this function is allowed to 'push' a lit LED off the cube or not
 *   start is at which index the function will start shifting, Default 0 for the beginning of any row
 *   end is the index the function will stop
 *   color will change the color of any shifted led, Default 1 will not change the color of shifted leds
 *
 ***************************************************************************/

void moveRow(uint8_t firstCoord, uint8_t secondCoord,  directions viewPoint,  uint16_t specificColor = 1, boolean collective = false, uint8_t start = 0, uint8_t end = 11, uint16_t color = 1);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void eradicate(uint16_t color);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void setRandomLED(uint8_t leds, directions direction, uint16_t color, boolean threeD = false);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//no up or down yet
void angledMove(uint8_t rise, uint8_t run, directions direction, uint16_t color);

 /***************************************************************************
  *
  *   Font Functions
  *
  ***************************************************************************/

 // input a char or number and get the index in the font array for that item
uint8_t getFontIndex(char c);

// draws a char c at the coordinates in the direction of the viewPoint with the color
void drawChar(char c, int x1, int y1, int z1, directions viewpoint, uint16_t color);

// funciton to let continuous typing of characters on the cube, (it wraps chars around as space fills up)
void typeChars(char c);

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

// draws a box based on the 6 coordinates (Two Points in the cube) and the color (This thing definitley needs rewritting)
void DrawFigure(int x1, int y1, int z1, int x2, int y2, int z2, uint16_t color);

/***************************************************************************
 *
 *   Special helper function to be used to display scores of a game
 *
 ***************************************************************************/


void gameOverScore(int score);

#endif