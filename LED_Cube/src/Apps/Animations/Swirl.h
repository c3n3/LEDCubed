#ifndef SWIRL
#define SWIRL
#include "../../../src/LED_Cube_library/Basic_Functions.h"
#include "../../../src/LED_Cube_library/Helpful_Functions.h"
#include "../App.h"
class Swirl: public App
{
public:
    const String title = "Swril";
    void run(uint32_t time = 0, bool timed = false);
};

void Swirl::run(uint32_t time, bool timed)
{
    boolean start = false;
    clearCube();
    uint32_t swirlTimer = millis();
    uint32_t timer = millis();

    while (!timed || millis() - timer < time)
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
        if (!start)
        {
            for (int i = 0; i < 12; i++)
            {
                help::directionalCubeArray(i, i, 11, FORWARD, true, 0xF000);
                help::directionalCubeArray(i, i, 11, BACKWARD, true, 0xFF00);
                help::directionalCubeArray(i, i, 11, LEFT, true, 0xFFFF);
                help::directionalCubeArray(i, i, 11, RIGHT, true, 0xF00F);
            }
            for (int i = 1; i < 11; i++)
            {
                help::directionalCubeArray(i, 11 - i, 10, FORWARD, true, 0xF800);
                help::directionalCubeArray(i, 11 - i, 10, BACKWARD, true, 0x0770);
                help::directionalCubeArray(i, 11 - i, 10, LEFT, true, 0x00EF);
                help::directionalCubeArray(i, 11 - i, 10, RIGHT, true, 0xF00F);
            }
            start = true;
        }
        if (millis() - swirlTimer > 100)
        {
            for (int k = 0; k < 12; k++)
            {
                help::moveRow(11, k, FORWARD);
                help::moveRow(11, k, BACKWARD);
                help::moveRow(11, k, LEFT);
                help::moveRow(11, k, RIGHT);
            }
            for (int i = 0; i < 4; i++)
            {
                for (int k = 1; k < 11; k++)
                {
                    help::moveRow(1, k, directions(i + 1), 1, false, 1, 10);
                }
            }

            swirlTimer = millis();
        }
    }
    clearCube();
}

#endif