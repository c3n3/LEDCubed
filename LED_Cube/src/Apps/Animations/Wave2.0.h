#include "../App.h"
#include "../../LED_Cube_library/Basic_Functions.h"
#include "../../Tools/MathObjects/UltamateTrigLookUp.h"
class Wave2p0: public App
{
private:
    SinLookUpTable<ui8, 12 * 2> sine;
    CosLookUpTable<ui8, 12 * 2> cos;
    ui8 iteration;
public:
App::Resut run(uint32_t time = 0, bool timed = false)
{
    int wave = rand() % 7;
    uint32_t timer = millis();
    uint32_t timerTotal = millis();
    auto func = [this, wave](int i, int j, int k, int iter, uint32_t p) -> void {
        if (wave == 0) lim_set_led_pk(((this->sine[k + iter] / 2) + (this->sine[j + iter] / 2)) / 2, ((this->cos[i + iter] / 2) + (this->cos[k + iter] / 2)) / 2, k, p);
        else if (wave == 1) lim_set_led_pk(i, j, ((this->sine[j + iter] / 2) + (this->cos[i + iter] / 2)) / 2, p);
        else if (wave == 2) lim_set_led_pk(i, (this->sine[i + iter] / 2), (this->cos[i + iter] / 2), p);
        else if (wave == 3) lim_set_led_pk(i, j, ((this->sine[i + iter] / 2) + (this->sine[j + iter] / 2)) / 2, p);
        else if (wave == 4) lim_set_led_pk(((this->sine[k + iter] / 2) + (this->sine[j + iter] / 2)) / 2, ((this->sine[i + iter] / 2) + (this->sine[k + iter] / 2)) / 2, k, p);
        else if (wave == 5) lim_set_led_pk(i, ((this->sine[i + iter] / 2)), ((this->sine[i + iter] / 2) + (this->sine[j + iter] / 2)) / 2, p);
        else if (wave == 6) lim_set_led_pk((this->sine[iter] / 2), (this->sine[iter + k] / 2), (this->sine[i + iter] / 2), p);
    };
    App::Resut res = App::TIMER_STOP;
    while (!timed || millis() - timerTotal < time)
    {
        char c;
        if (Input::available())
        {
            c = Input::read();
            if (c == PS2_ESC)
            {
                res = KEYBOARD_STOP;
                break;
            }
        }
        if (millis() - timer > 100)
        {
            // for (int i = 0; i < 12; i++) {
            //     for (int j = 0; j < 12; j++) {
            //         for (int k = 0; k < 12; k++) {
            //             set_led_pk(i, j, k, 0);
            //         }
            //     }
            // }
            clearCube();
            iteration = (iteration + 1) % (12 * 2);
            for (int i = 0; i < 12; i++) {
                for (int j = 0; j < 12; j++) {
                    for (int k = 0; k < 12; k++) {
                        func(i, j, k, iteration, rand());
                    }
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

