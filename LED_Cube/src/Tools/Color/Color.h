#pragma once
#include "Arduino.h"
#include "../../LED_Cube_library/types.h"
#include "../../LED_Cube_library/Basic_Functions.h"

/**
 * @brief This is a color object, it ultamatly stores only one 2 byte integer, but incorperates a lot of great functionality. 
 * @brief Also there are many operator overloads to make using this object seem just like a normal number
 */
struct Color
{
public:
    uint16_t color;
    
    static const uint16_t white = 0xFFFF;

    /**
     * @brief Construct a new Color object
     * 
     * @param r ed
     * @param g reen
     * @param b lue
     */
    Color(ui8 r, ui8 g, ui8 b);

    /**
     * @brief Construct a new Color object
     * 
     * @param color 16-bit packed color rrrrrggggggbbbbb
     */
    Color(uint16_t color);

    // rgb are represeted by 255 - 0 scale, however the increments are not the same due to compression: Red as 5 bits, Green has 6 bits, and Blue has 5 bits.
    ui8 r();
    // rgb are represeted by 255 - 0 scale, however the increments are not the same due to compression: Red as 5 bits, Green has 6 bits, and Blue has 5 bits.
    ui8 g();
    // rgb are represeted by 255 - 0 scale, however the increments are not the same due to compression: Red as 5 bits, Green has 6 bits, and Blue has 5 bits.
    ui8 b();

    // so you can pass Colors as a uint16_t in function for ease of use
    operator uint16_t();

    // a very naive way to brighten colors, probably just needs to be re written with a better algo
    Color &operator++(int);

    // very very naive way to darken colors. Will not work well with colors equaling zero
    Color &operator--(int);

    // so you can write color = 0xFFFF; and it will work
    Color &operator=(uint16_t cIn);

    // a set color function (kinda useless)
    void setColor(uint16_t cin);

    // gets the real values of the colors ie the bits that represent the colors in increments of 1
    ui8 rReal();
    // gets the real values of the colors ie the bits that represent the colors in increments of 1
    ui8 gReal();
    // gets the real values of the colors ie the bits that represent the colors in increments of 1
    ui8 bReal();

    // used to set the r g b values of the Color on a 255 - 0 scale
    ui8 r(uint16_t cIn);
    // used to set the r g b values of the Color on a 255 - 0 scale
    ui8 g(uint16_t cIn);
    // used to set the r g b values of the Color on a 255 - 0 scale
    ui8 b(uint16_t cIn);

    // uses the real scale ie 5 bit red, 6 bit green, 5 bit blue
    ui8 rReal(uint16_t cIn);
    // uses the real scale ie 5 bit red, 6 bit green, 5 bit blue
    ui8 gReal(uint16_t cIn);
    // uses the real scale ie 5 bit red, 6 bit green, 5 bit blue
    ui8 bReal(uint16_t cIn);
};
