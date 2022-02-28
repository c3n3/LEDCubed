#include "Snake.h"
#include "../../Tools/TypingEngine/TypeEngine.h"
#include "../../../src/Tools/Input/Input.h"

void Snake::end(int score)
{
    for (int p = 0; p < 3; p++)
    {

        for (int k = 0; k < 12; k++)
        {
            for (int j = 0; j < 12; j++)
            {
                for (int i = 0; i < 12; i++)
                {
                    set_led_pk(i, j, k, 0xF800);
                }
            }
        }
        d(250);
        clearCube();
        d(250);
    }
    TypeEngine::drawChar('0' + (score % 10), 4,6,1,Relativistic::FORWARD, 0xFFFF);
    TypeEngine::drawChar('0' + ((score / 10) % 10), 0,6,1,Relativistic::FORWARD, 0xFFFF);
}

uint16_t Snake::colorShifter(uint16_t currentColor)
{
    boolean state = false;
    uint8_t r = (currentColor & 0xF800) >> 11;
    uint16_t g = (currentColor & 0x07E0) >> 5;
    uint16_t b = (currentColor & 0x001F);
    if (state)
    {
        if (b != 31)
        {
            b++;
        }
        else if (r != 63)
        {
            r++;
        }
        else
        {
            state = true;
        }
    }
    else
    {
        if (b != 0)
        {
            b--;
        }
        else if (r != 0)
        {
            r--;
        }
        else
        {
            state = false;
        }
    }
    return pk_low(r, g, b);
}

void Snake::MoveLED(uint8_t x, uint8_t y, uint8_t z, uint16_t currentColor, bool gainLength)
{
    currentColor = colorShifter(currentColor);

    if (LEDArray(x + 1, y, z) == currentColor)
    {
        set_led_pk(x, y, z, currentColor);
        MoveLED(x + 1, y, z, currentColor, gainLength);
    }
    else if (LEDArray(x - 1, y, z) == currentColor)
    {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x - 1, y, z, currentColor, gainLength);
    }
    else if (LEDArray(x, y + 1, z) == currentColor)
    {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x, y + 1, z, currentColor, gainLength);
    }
    else if (LEDArray(x, y - 1, z) == currentColor)
    {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x, y - 1, z, currentColor, gainLength);
    }
    else if (LEDArray(x, y, z + 1) == currentColor)
    {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x, y, z + 1, currentColor, gainLength);
    }
    else if (LEDArray(x, y, z - 1) == currentColor)
    {
        set_led_pk(x, y, z, currentColor);
        //uses underflow
        if (z - 1 < 12)
        {
            MoveLED(x, y, z - 1, currentColor, gainLength);
        }
    }
    else if (gainLength)
    {
        set_led_pk(x, y, z, currentColor);
    }
    else
    {
        set_led_pk(x, y, z, 0);
    }
}

App::Resut Snake::run(uint32_t time, bool timed)
{
    boolean start = false;
    uint16_t color = 0xFFFF;
    boolean toggle = false;
    uint8_t x = 5;
    uint8_t y = 5;
    uint8_t z = 4;
    uint8_t x2 = 5;
    uint8_t y2 = 3;
    uint8_t z2 = 6;
    uint16_t speed = 500;
    uint16_t length = 4;
    uint16_t length2 = 4;
    Relativistic::Directions direction = Relativistic::FORWARD;
    uint32_t foodTimer = millis();
    uint32_t moveTimer = millis();
    boolean addLength = false;
    coord_t food[NUM_FOOD];
    boolean endGame = false;
    uint32_t timer = millis();
    App::Resut res = App::STOP;
    clearCube();
    while (!timed || millis() - timer < time)
    {
        char c = ']';

        if (Input::available())
        {
            c = Input::read();
            if (c == PS2_ESC)
            {
                res = App::KEYBOARD_STOP;
                break;
            }

            // so that the snake cannot eat itself prevent motion in the reverse direction
            if (c == PS2_LEFTARROW && direction == Relativistic::RIGHT)
            {
                c = ']';
            }
            else if (c == PS2_RIGHTARROW && direction == Relativistic::LEFT)
            {
                c = ']';
            }
            else if (c == PS2_DOWNARROW && direction == Relativistic::FORWARD)
            {
                c = ']';
            }
            else if (c == PS2_UPARROW && direction == Relativistic::BACKWARD)
            {
                c = ']';
            }
            else if ((c == '1' || c == 'r') && direction == Relativistic::DOWN)
            {
                c = ']';
            }
            else if ((c == '0' || c == 'f') && direction == Relativistic::UP)
            {
                c = ']';
            }
        }

        if (!start)
        {
            clearCube();
            for (int i = 0; i < 4; i++)
            {
                set_led_pk(5, 5, 4 - i, color);
                color = colorShifter(color);
            }
            for (int i = 0; i < NUM_FOOD; i++)
            {
                while (true)
                {
                    food[i].x = rand() % 12;
                    food[i].y = rand() % 12;
                    food[i].z = rand() % 12;
                    if (LEDArray(food[i].x, food[i].y, food[i].z) == 0)
                    {
                        break;
                    }
                }
            }
            start = true;
        }

        if (millis() - foodTimer > 900)
        {
            if (toggle)
            {
                for (int i = 0; i < NUM_FOOD; i++)
                {
                    set_led_pk(food[i].x, food[i].y, food[i].z, 0xF830);
                }
                toggle = !toggle;
            }
            else
            {
                for (int i = 0; i < NUM_FOOD; i++)
                {
                    set_led_pk(food[i].x, food[i].y, food[i].z, 0x031F);
                }
                toggle = !toggle;
            }
            foodTimer += 900;
        }

        switch (c)
        {
        case PS2_LEFTARROW:
            direction = Relativistic::LEFT;
            break;
        case PS2_RIGHTARROW:
            direction = Relativistic::RIGHT;
            break;
        case '0':
        case 'f':
            direction = Relativistic::DOWN;
            break;
        case 'r':
        case '1':
            direction = Relativistic::UP;
            break;
        case PS2_DOWNARROW:
            direction = Relativistic::BACKWARD;
            break;
        case PS2_UPARROW:
            direction = Relativistic::FORWARD;
            break;
        default:
            break;
        }

        x2 = x;
        y2 = y;
        z2 = z;

        if (millis() - moveTimer > speed && !endGame)
        {
            if (length >= 7 && speed > 300)
            {
                speed -= 90;
                length = 0;
            }
            if (!(x == 12 || z == 12 || y == 12))
            {
                switch (direction)
                {
                case Relativistic::FORWARD:
                    z++;
                    break;
                case Relativistic::BACKWARD:
                    z--;
                    break;
                case Relativistic::UP:
                    y++;
                    break;
                case Relativistic::DOWN:
                    y--;
                    break;
                case Relativistic::LEFT:
                    x--;
                    break;
                case Relativistic::RIGHT:
                    x++;
                    break;
                default:
                    break;
                }

                for (int i = 0; i < NUM_FOOD; i++)
                {
                    if (food[i].x == x && food[i].y == y && food[i].z == z)
                    {
                        while (true)
                        {
                            food[i].x = rand() % 12;
                            food[i].y = rand() % 12;
                            food[i].z = rand() % 12;
                            addLength = true;
                            if (LEDArray(food[i].x, food[i].y, food[i].z) == 0)
                            {
                                length++;
                                length2++;
                                break;
                            }
                        }
                    }
                }
                if (((LEDArray(x, y, z) == 0 || addLength) == false) || (x - 1 >= 11 || y - 1 >= 11 || z - 1 >= 11))
                {
                    endGame = true;
                    end(length2 - 4);
                }
                else
                {
                    set_led_pk(x, y, z, 0xFFFF);

                    MoveLED(x2, y2, z2, 0xFFFF, addLength);
                    addLength = false;
                    moveTimer += speed;
                }
            }
        }
    }
    clearCube();
    return res;
}
