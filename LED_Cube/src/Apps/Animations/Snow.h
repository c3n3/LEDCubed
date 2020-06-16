#ifndef SNOW
#define SNOW
#include "../../../src/LED_Cube_library/Basic_Functions.h"
#include "../../../src/LED_Cube_library/Helpful_Functions.h"
#include "../App.h"

class Snow: public App
{
public:
    const String title = "Snow";
    void run(uint32_t time = 0, bool timed = false);
};

void Snow::run(uint32_t time, bool timed)
{
    uint32_t timer = millis();
    uint32_t timerTotal = millis();

    while (!timed || millis() - timerTotal < time)
    {
        char c;
        if (keyboard.available())
        {
            c = keyboard.read();
            if (c == PS2_ESC)
            {
                break;
            }
        }

        if (millis() - timer > 260)
        {
            //int color = rand() % 64000;
            int count = 0;

            //delay(260);
            for (int i = 0; i < 12; i++)
            {
                for (int f = 0; f < 12; f++)
                {
                    count = 0;
                    for (int g = 0; g < 4; g++)
                    {
                        if (LEDArray(i, g, f) != 0)
                        {
                            count += 1;
                        }
                        if (count == 4)
                        {
                            set_led_pk(i, g, f, 0);
                        }
                    }
                }
            }

            for (int i = 0; i < 12; i++)
            {
                for (int j = 0; j < 12; j++)
                {
                    if (rand() % 25 != 1)
                    {
                        help::moveRow(j, i, DOWN, 1, true);
                    }
                    else
                    {
                        help::moveRow(j, i, DOWN, 1, false);
                    }
                }
            }
            int num = rand() % 12;
            int num1 = rand() % 12;
            int num2 = rand() % 12;
            set_led_pk(num, 11, num2, white);
            set_led_pk(num1, 11, num, white);
            set_led_pk(num2, 11, num1, white);
            timer += 260;
        }
    }
    clearCube();
}

#endif