#pragma once
#include "../../LED_Cube_library/Basic_Functions.h"
#include "../../LED_Cube_library/types.h"
namespace Relativistic
{
    // direction of the thing
    enum Directions {UP, FORWARD, LEFT, BACKWARD, RIGHT, DOWN};

    // returns color of the specified LED
    uint16_t LED(ui8 x, ui8 y, ui8 z, Directions& direction);
    
    // set a relative LED coordinate to a color
    void setLED(ui8 x, ui8 y, ui8 z, Directions direction, uint16_t color);
    
    // set a relative LED coordinate to a color, but also make sure it is protected
    void protectedSetLED(ui8 x, ui8 y, ui8 z, Directions direction, uint16_t color);

    // This is a very, very useful function that creates relativistic coordinates that revolve around the viewing angle of direction parameter; This should be broken to two functions however
    uint16_t directionalCubeArray(const uint8_t& firstCord, const uint8_t& secondCord, const uint8_t& thirdCord, Directions direction, bool setLED = false, uint16_t color = 0);
    
    // Go from a standard coordinate to a relative coordinate
    void toRelative(ui8& x, ui8& y, ui8& z, Directions direction);

    // go from a relative coordinate to a standard one, 
    void toStandard(ui8& x, ui8& y, ui8& z, Directions direction);
};