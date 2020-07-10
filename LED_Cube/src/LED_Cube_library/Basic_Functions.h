#ifndef BASIC_FUNCTIONS
#define BASIC_FUNCTIONS
#include "Arduino.h"
#include "globals.h"
#include "../../TLC_lib.h"
#include "../../MUX_lib.h"

//Pixel buffer storing each LED color as a 16 bit value ( RRRRRGGGGGGBBBBB )
extern volatile uint16_t    px_buf[NUM_LEDS];   

//Coordinates and RGB values and buffer. RGB range 0-255
void set_led( uint8_t x, uint8_t y, uint8_t z, uint16_t r, uint16_t g, uint16_t b);

// will not destroy the program if you set a nonexistant LED
void protected_set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c);

// a delay function that accounts for pressing the escape key; maybe try to use an exception for this; no idea if c++ arduino can utilise exceptions
char d(uint16_t t);

//packs a rgb color into one number
uint16_t pk_color(uint16_t r, uint16_t g, uint16_t b);

// red goes up to 31
// blue to 31
// green up to 63
uint16_t pk_low(uint16_t r, uint16_t g, uint16_t b);

// a packed coordinate
uint16_t pk_coord(uint8_t x, uint8_t y, uint8_t z);

//self explainatory
void clearCube();

//houses the data for the whole cube (wrapper function for the px_buf array )
uint16_t LEDArray(uint8_t x, uint8_t y, uint8_t z);

//Set led with packed color value
void set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c);

//Set led with packed color value by address
void setAddressLED( uint16_t address, uint16_t c);

// set led by packed coordinates and packed color
void setPackedPackedLED(uint16_t coord, uint16_t c);

#endif