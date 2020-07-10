#pragma once
#include "../App.h"
#include "../../../src/LED_Cube_library/Basic_Functions.h"
#include "../../../src/LED_Cube_library/Helpful_Functions.h"
#include "../../Tools/RelativeCoordinates/Relativistic.h"
class Space : public App
{
private:
    Relativistic::Directions current;

    uint32_t interval;

    const uint16_t intervalAcceleration = 200; // the interval in which we set a new interval
    const uint8_t intervalJump = 50;           // in milliseconds the max the interval can jump
    const uint16_t intervalMax = 1000;         // the max the interval
    const uint16_t intervalMin = 100;          // the minimum the interval can go
    const uint16_t peakSustain = 1000;         // how long the program stops at the max interval
    const uint8_t ledDensity = 4;

    bool speedUp;
    bool sustain;
    void moveAll()
    {
        for (int x = 0; x < 12; x++)
        {
            for (int y = 0; y < 12; y++)
            {
                for (int z = 0; z < 12; z++)
                {
                    help::moveRow(x, y, current, 1); // move all colors
                }
            }
        }
    };

    void randomLEDs()
    {
        help::setRandomLED(ledDensity, current, rand() % 0xFFFF);
    };

    void getNextInterval()
    {
        speedUp ? (interval - (millis() % intervalJump)) : (interval + (millis() % intervalJump));
    };

    Relativistic::Directions getNextDirection()
    {
        return Relativistic::Directions(millis() % 6); // just using millis for random for now
    };

protected:
    bool frame()
    {
        if (sustain && (millis() - timer > peakSustain))
        {
            if (sustain)
            {
                timer += peakSustain;
                sustain = false;
            }
            if (millis() - timer > intervalAcceleration)
            {
                randomLEDs();
                moveAll();
                if (interval > intervalMax && speedUp == false)
                {
                    speedUp = true;
                }
                else if (interval < intervalMin && speedUp)
                {
                    speedUp = false;
                }
                else if ((speedUp == true && interval > intervalMax) || (speedUp == false && interval < intervalMin))
                {
                    sustain = true;
                }
                else
                {
                    getNextInterval();
                }
                timer += intervalJump;
            }
        }
        return CONTINUE_PROGRAM; // this thing always continues
    };

public:
    Space()
    {
        speedUp = true;
        sustain = false; // when will sustain be implimented
        interval = 750; // 750 miliseconds to start the function
        current = Relativistic::Directions(millis() % 6);
    };
};