#include "Relativistic.h"




void Relativistic::toStandard(ui8& x, ui8& y, ui8& z, Directions direction) {
    // This is the the flip
    uint8_t temp;
    switch (direction)
    {
        case UP:
            temp = y;
            y = z;
            z = 11 - temp;
            break;
        case LEFT:
            temp = x;
            x = 11 - z;
            z = temp;
            break;
        case BACKWARD:
            x = 11 - x;
            z = 11 - z;
            break;
        case RIGHT:
            temp = x;
            x = z;
            z = 11 - temp;
            break;
        case DOWN:
            temp = y;
            y = 11 - z;
            z = temp;
            break;
        default:
            break;
    }
}


void Relativistic::toRelative(ui8& x, ui8& y, ui8& z, Directions direction) {
    switch (direction)
    { // turns out we can just use the toStandard in reverse to acheive this
        case UP:
            toStandard(x, y, z, DOWN);
            break;
        case LEFT:
            toStandard(x, y, z, RIGHT);
            break;
        case BACKWARD:
            toStandard(x, y, z, BACKWARD);
            break;
        case RIGHT:
            toStandard(x, y, z, LEFT);
            break;
        case DOWN:
            toStandard(x, y, z, UP);
            break;
        default:
            break;
    }
}

uint16_t Relativistic::LED(ui8 x, ui8 y, ui8 z, Directions& direction) {
    toStandard(x, y, z, direction);
    return LEDArray(x, y, z);
}

void Relativistic::setLED(ui8 x, ui8 y, ui8 z, Directions direction, uint16_t color) {
    toStandard(x, y, z, direction);
    set_led_pk(x, y, z, color);
}

void Relativistic::protectedSetLED(ui8 x, ui8 y, ui8 z, Directions direction, uint16_t color) {
    toStandard(x, y, z, direction);
    protected_set_led_pk(x, y, z, color);
}

//this function switches which orientation you may look at the cube,
// very very useful function, allows writing other helper functions in terms of a direction so that you dont have to have 6 types of the same function for each direction
// the  coordinates go as follows, the face you look at for each direction, the reletive 'z' coordinate is the depth from face, the reletive 'x' is the right and left axis across the face, and the second coordinate is always the reletive 'y'
uint16_t Relativistic::directionalCubeArray(const uint8_t &firstCord, const uint8_t &secondCord, const uint8_t &thirdCord, Directions direction, bool setLED, uint16_t color)
{
    if (setLED)
    {
        switch (direction)
        { //you can set leds
        case UP:
            set_led_pk(firstCord, thirdCord, secondCord, color);
            break;
        case FORWARD:
            set_led_pk(firstCord, secondCord, thirdCord, color);
            break;
        case LEFT:
            set_led_pk(11 - thirdCord, secondCord, firstCord, color);
            break;
        case BACKWARD:
            set_led_pk(11 - firstCord, secondCord, 11 - thirdCord, color);
            break;
        case RIGHT:
            set_led_pk(thirdCord, secondCord, 11 - firstCord, color);
            break;
        case DOWN:
            set_led_pk(firstCord, 11 - thirdCord, secondCord, color);
            break;
        default:
            break;
        }
        return 0;
    }
    else
    {
        switch (direction)
        { //or you can call the array for the cube, it returns the value
        case UP:
            return LEDArray(firstCord, thirdCord, secondCord);
            break;
        case FORWARD:
            return LEDArray(firstCord, secondCord, thirdCord);
            break;
        case LEFT:
            return LEDArray(11 - thirdCord, secondCord, firstCord);
            break;
        case BACKWARD:
            return LEDArray(11 - firstCord, secondCord, 11 - thirdCord);
            break;
        case RIGHT:
            return LEDArray(thirdCord, secondCord, 11 - firstCord);
            break;
        case DOWN:
            return LEDArray(firstCord, 11 - thirdCord, secondCord);
            break;

        default:
            break;
        }
    }
    return 0; // if people input nonsense, give them arbitrary nonsense
}