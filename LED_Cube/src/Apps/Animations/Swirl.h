#ifndef SWIRL
#define SWIRL
#include "../../../src/LED_Cube_library/Basic_Functions.h"
#include "../../../src/LED_Cube_library/Helpful_Functions.h"
#include "../../../src/Tools/RelativeCoordinates/Relativistic.h"
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
                Relativistic::setLED(i, i, 11, Relativistic::FORWARD, 0xF000);
                Relativistic::setLED(i, i, 11, Relativistic::BACKWARD, 0xFF00);
                Relativistic::setLED(i, i, 11, Relativistic::LEFT, 0xFFFF);
                Relativistic::setLED(i, i, 11, Relativistic::RIGHT, 0xF00F);
            }
            for (int i = 1; i < 11; i++)
            {
                Relativistic::setLED(i, 11 - i, 10, Relativistic::FORWARD, 0xF800);
                Relativistic::setLED(i, 11 - i, 10, Relativistic::BACKWARD, 0x0770);
                Relativistic::setLED(i, 11 - i, 10, Relativistic::LEFT, 0x00EF);
                Relativistic::setLED(i, 11 - i, 10, Relativistic::RIGHT, 0xF00F);
            }
            start = true;
        }
        if (millis() - swirlTimer > 100)
        {
            for (int k = 0; k < 12; k++)
            {
                help::moveRow(11, k, Relativistic::FORWARD);
                help::moveRow(11, k, Relativistic::BACKWARD);
                help::moveRow(11, k, Relativistic::LEFT);
                help::moveRow(11, k, Relativistic::RIGHT);
            }
            for (int i = 0; i < 4; i++)
            {
                for (int k = 1; k < 11; k++)
                {
                    help::moveRow(1, k, Relativistic::Directions(i + 1), 1, false, 1, 10);
                }
            }

            swirlTimer = millis();
        }
    }
    clearCube();
}

#endif