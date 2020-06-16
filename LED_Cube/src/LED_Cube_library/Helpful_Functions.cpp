#include "Helpful_Functions.h"
//this function switches which orientation you may look at the cube,
// very very useful function, allows writting other helper functions in terms of a direction so that you dont have to have 6 types of the same function for each direction
// the  coordinates go as follows, the face you look at for each direction, the reletive 'z' coordinate is the depth from face, the reletive 'x' is the right and left axis across the face, and the second coordinate is always the reletive 'y'
uint16_t help::directionalCubeArray(const uint8_t &firstCord, const uint8_t &secondCord, const uint8_t &thirdCord, directions direction, bool setLED, uint16_t color)
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

ui8 help::normalize(float& notNormal)
{
    ui8 normalized = (notNormal + 0.5);
    if (normalized - 1 > 10)
    {
        normalized = normalized > 200 ? 0 : 11; // that 200 is completely arbitrary, but it should work
    }
    return normalized;
}

void help::switchToDirectionalCoord(ui8& nonRelativeX, ui8& nonRelativeY, ui8& nonRelativeZ, directions direction)
{
    // This is the the flip
    uint8_t temp;
    switch (direction)
    {
    case UP:
        temp = nonRelativeY;
        nonRelativeY = nonRelativeZ;
        nonRelativeZ = temp;
        break;
    case LEFT:
        temp = nonRelativeX;
        nonRelativeX = 11 - nonRelativeZ;
        nonRelativeZ = temp;
        break;
    case BACKWARD:
        nonRelativeX = 11 - nonRelativeX;
        nonRelativeZ = 11 - nonRelativeZ;
        break;
    case RIGHT:
        temp = nonRelativeX;
        nonRelativeX = nonRelativeZ;
        nonRelativeZ = 11 - temp;
        break;
    case DOWN:
        temp = nonRelativeY;
        nonRelativeY = 11 - nonRelativeZ;
        nonRelativeZ = temp;
        break;
    default:
        break;
    }
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

void help::moveRow(uint8_t firstCoord, uint8_t secondCoord, directions viewPoint, uint16_t specificColor, boolean collective, uint8_t start, uint8_t end, uint16_t color)
{
    if (!collective && end == 11)
    {
        directionalCubeArray(firstCoord, secondCoord, 11, viewPoint, true);
    }
    for (int i = 10 - (11 - end); i >= 0 + start; i--)
    {
        if (specificColor == 1)
        {
            if (directionalCubeArray(firstCoord, secondCoord, i, viewPoint) != 0)
            {
                if (collective)
                {
                    if (directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint) == 0)
                    {
                        if (color == 1)
                        {
                            directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, directionalCubeArray(firstCoord, secondCoord, i, viewPoint));
                        }
                        else
                        {
                            directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true, color);
                        }
                        directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                    }
                }
                else
                {

                    if (color == 1)
                    {
                        directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, directionalCubeArray(firstCoord, secondCoord, i, viewPoint));
                    }
                    else
                    {
                        directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, color);
                    }
                    directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                }
            }
        }
        else
        {
            if (directionalCubeArray(firstCoord, secondCoord, i, viewPoint) != 0 && directionalCubeArray(firstCoord, secondCoord, i, viewPoint) == specificColor)
            {
                if (collective)
                {
                    if (directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint) != specificColor)
                    {
                        if (color == 1)
                        {
                            directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, directionalCubeArray(firstCoord, secondCoord, i, viewPoint, false));
                        }
                        else
                        {
                            directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true, color);
                        }
                        directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                    }
                }
                else
                {

                    if (color == 1)
                    {
                        directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, directionalCubeArray(firstCoord, secondCoord, i, viewPoint));
                    }
                    else
                    {
                        directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, color);
                    }
                    directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
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
void help::setRandomLED(uint8_t leds, directions direction, uint16_t color, boolean threeD)
{
    if (!threeD)
    {
        for (uint8_t i = 0; i < leds; i++)
        {
            directionalCubeArray(rand() % 12, rand() % 12, 0, direction, true, color);
        }
    }
}

//no up or down yet
void help::angledMove(uint8_t rise, uint8_t run, directions direction, uint16_t color)
{
    //rise
    for (uint8_t k = 0; k < rise; k++)
    {
        for (uint8_t i = 0; i < 12; i++)
        {
            for (uint8_t j = 0; j < 12; j++)
            {
                moveRow(i, j, UP, color);
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