#ifndef SNAKE
#define SNAKE
// #include "../../LED_Cube_library/LED_Cube_Library.h"
#include "../../../src/LED_Cube_library/Basic_Functions.h"
#include "../../../src/LED_Cube_library/Helpful_Functions.h"
#include "../App.h"
class Snake: public App
{
private:
    const int NUM_FOOD = 10;
    void end(int score);
    uint16_t colorShifter(uint16_t currentColor);
    void MoveLED(uint8_t x, uint8_t y, uint8_t z, uint16_t currentColor, bool gainLength);

public:
    const String title = "Snake";
    void run(uint32_t time = 0, bool timed = false);
    ~Snake();
};

#endif