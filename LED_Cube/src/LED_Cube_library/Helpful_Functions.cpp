#include "Helpful_Functions.h"


ui8 help::normalize(float& notNormal)
{
    ui8 normalized = (notNormal + 0.5);
    if (normalized - 1 > 10)
    {
        normalized = normalized > 200 ? 0 : 11; // that 200 is completely arbitrary, but it should work
    }
    return normalized;
}

/***************************************************************************
 *
 *   Move Row function, (This is a big function I know, It is very useful to compensate, also should be rewritten with recursion for possibly better performance)
 *   firstCoord and secondCoord determine which row will be shifted in accordance with the specified viewPoint
 *   viewPoint determines which plane will be looked at for the two coordinates to shift there row
 *   specificColor tells it which color it should shift in the cube default is 1, this will shift all colors
 *   collective determines whether this function is allowed to 'push' a lit LED off the cube or not
 *   start is at which index the function will start shifting, Default 0 for the beginning of any row
 *   end is the index the function will stop
 *   color will change the color of any shifted led, Default 1 will not change the color of shifted leds
 *
 ***************************************************************************/

void help::moveRow(uint8_t firstCoord, uint8_t secondCoord, Relativistic::Directions viewPoint, uint16_t specificColor, boolean collective, uint8_t start, uint8_t end, uint16_t color)
{
    if (!collective && end == 11)
    {
        Relativistic::directionalCubeArray(firstCoord, secondCoord, 11, viewPoint, true);
    }
    for (int i = 10 - (11 - end); i >= 0 + start; i--)
    {
        if (specificColor == 1)
        {
            if (Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint) != 0)
            {
                if (collective)
                {
                    if (Relativistic::directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint) == 0)
                    {
                        if (color == 1)
                        {
                            Relativistic::directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint));
                        }
                        else
                        {
                            Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true, color);
                        }
                        Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                    }
                }
                else
                {

                    if (color == 1)
                    {
                        Relativistic::directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint));
                    }
                    else
                    {
                        Relativistic::directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, color);
                    }
                    Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                }
            }
        }
        else
        {
            if (Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint) != 0 && Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint) == specificColor)
            {
                if (collective)
                {
                    if (Relativistic::directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint) != specificColor)
                    {
                        if (color == 1)
                        {
                            Relativistic::directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint, false));
                        }
                        else
                        {
                            Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true, color);
                        }
                        Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                    }
                }
                else
                {

                    if (color == 1)
                    {
                        Relativistic::directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint));
                    }
                    else
                    {
                        Relativistic::directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, color);
                    }
                    Relativistic::directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                }
            }
        }
    }
}

// delete all of a color on the entire cube
void help::eradicate(uint16_t color)
{
    for (uint8_t i = 0; i < 12; i++)
    {
        for (uint8_t j = 0; j < 12; j++)
        {
            for (uint8_t k = 0; k < 12; k++)
            {
                if (LEDArray(i, j, k) == color)
                {
                    set_led(i, j, k, 0, 0, 0);
                }
            }
        }
    }
}

//TODO: delete this thing if safe
void help::setRandomLED(uint8_t leds, Relativistic::Directions direction, uint16_t color, boolean threeD)
{
    if (!threeD)
    {
        for (uint8_t i = 0; i < leds; i++)
        {
            Relativistic::directionalCubeArray(rand() % 12, rand() % 12, 0, direction, true, color);
        }
    }
}

//no up or down yet
void help::angledMove(uint8_t rise, uint8_t run, Relativistic::Directions direction, uint16_t color)
{
    //rise
    for (uint8_t k = 0; k < rise; k++)
    {
        for (uint8_t i = 0; i < 12; i++)
        {
            for (uint8_t j = 0; j < 12; j++)
            {
                moveRow(i, j, Relativistic::UP, color);
            }
        }
    }
    //rise
    for (uint8_t k = 0; k < run; k++)
    {
        for (uint8_t i = 0; i < 12; i++)
        {
            for (uint8_t j = 0; j < 12; j++)
            {
                moveRow(i, j, direction, color);
            }
        }
    }
}

// draws a box based on the 6 coordinates (Two Points in the cube) and the color (This thing definitley needs rewritting)
void help::DrawFigure(int x1, int y1, int z1, int x2, int y2, int z2, uint16_t color)
{
    int xDist = abs(x1 - x2);
    int yDist = abs(y1 - y2);
    int zDist = abs(z1 - z2);
    if (x1 > x2)
    { //created in order to make the 'for' loops always accurate
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y1 > y2)
    { // created in order to make the 'for' loop always accurate
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }
    if (z1 > z2)
    { // created in order to make the 'for' loop always accurate
        int temp = z1;
        z1 = z2;
        z2 = temp;
    }
    if (xDist == 0)
    { // if the x coordinates are the same, the shape will be a square will a constant x value
        for (int i = y1; i <= y2; i++)
        {
            set_led_pk(x1, i, z1, color);
            //delay(200);
            set_led_pk(x1, i, z2, color);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++)
        {
            set_led_pk(x1, y1, i, color);
            //delay_pk(200);
            set_led_pk(x1, y2, i, color);
            //delay(200);
        }
    }
    else if (yDist == 0)
    { // if the y coordinates are the same, the shape will be a square will a constant y value
        for (int i = x1; i <= x2; i++)
        {
            set_led_pk(i, y1, z1, color);
            //delay_pk(200);
            set_led_pk(i, y1, z2, color);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++)
        {
            set_led_pk(x1, y1, i, color);
            //delay_pk(200);
            set_led_pk(x2, y1, i, color);
            //delay(200);
        }
    }
    else if (zDist == 0)
    { // if the z coordinates are the same, the shape will be a square will a constant z value
        for (int i = x1; i <= x2; i++)
        {
            set_led_pk(i, y1, z1, color);
            //delay_pk(200);
            set_led_pk(i, y2, z1, color);
            //delay(200);
        }
        for (int i = y1; i <= y2; i++)
        {
            set_led_pk(x1, i, z1, color);
            //delay+pk(200);
            set_led_pk(x2, i, z1, color);
            //delay(200);
        }
    }
    else
    { // if none of the x/y/z coordinates match the other points' x/y/z, then the shape will be a cube.
        for (int i = x1; i <= x2; i++)
        {
            set_led_pk(i, y1, z1, color);
            //delay_pk(200);
            set_led_pk(i, y2, z1, color);
            //delay_pk(200);
            set_led_pk(i, y1, z2, color);
            //delay_pk(200);
            set_led_pk(i, y2, z2, color);
            //delay(200);
        }
        for (int i = y1; i <= y2; i++)
        {
            set_led_pk(x1, i, z1, color);
            //delay_pk(200);
            set_led_pk(x2, i, z1, color);
            //delay_pk(200);
            set_led_pk(x1, i, z2, color);
            //delay_pk(200);
            set_led_pk(x2, i, z2, color);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++)
        {
            set_led_pk(x1, y1, i, color);
            //delay_pk(200);
            set_led_pk(x1, y2, i, color);
            //delay_pk(200);
            set_led_pk(x2, y1, i, color);
            //delay_pk(200);
            set_led_pk(x2, y2, i, color);
            //delay(200);
        }
    }
}