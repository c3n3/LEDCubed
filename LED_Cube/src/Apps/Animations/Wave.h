#include "../App.h"
#include "../../LED_Cube_library/Basic_Functions.h"
#include "../../Tools/MathObjects/UltamateTrigLookUp.h"
class Wave: public App
{
private:
    SinLookUpTable<ui8, 12> sine;
    ui8 iteration;
public:
    bool init() {
        iteration = 0;
        return CONTINUE_PROGRAM;
    }
    bool frame() {
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                set_led_pk(i, sine[i + iteration], j, 0xFFFF);
            }
        }
        iteration++;
        return CONTINUE_PROGRAM;
    }
};

