#include "../App.h"
#include "../../LED_Cube_library/Basic_Functions.h"
#include "../../Tools/MathObjects/UltamateTrigLookUp.h"
#include "../../../src/Tools/Input/Input.h"

class Wave: public App
{
private:
    SinLookUpTable<ui8, 24> sine;
    ui8 iteration;
public:
App::Resut run(uint32_t time = 0, bool timed = false) {
    uint32_t timer = millis();
    uint32_t timerTotal = millis();
    App::Resut res = App::TIMER_STOP;
    while (!timed || millis() - timerTotal < time)
    {
        char c;

        if (Input::available())
        {
            c = Input::read();
            if (c == PS2_ESC)
            {
                res = App::KEYBOARD_STOP;
                break;
            }
        }
        // TODO: Implement user control
        if (millis() - timer > 100)
        {
            for (int i = 0; i < 12; i++) {
                for (int j = 0; j < 12; j++) {
                    protected_set_led_pk(i, j, ((sine[i + iteration] / 2) + (sine[j + iteration] / 2)) / 2, 0x00);
                }
            }
            iteration = (iteration + 1) % (12 * 2);
            // clearCube();
            for (int i = 0; i < 12; i++) {
                for (int j = 0; j < 12; j++) {
                    protected_set_led_pk(i, j, ((sine[i + iteration] / 2) + (sine[j + iteration] / 2)) / 2, rand());
                }
            }
            
            // FIX ALT. Out of bounds iterator
            timer += 100;
        }
    }
    clearCube();
    return res;
}
};

