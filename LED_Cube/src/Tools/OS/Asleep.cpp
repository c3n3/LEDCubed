#include "Asleep.h"
Asleep::Asleep(AppCtor* a, uint8_t m) {
    apps = a;
    size = m;
};


void Asleep::go(uint32_t setTimes) {
    while (true) {
        for (int i = 0; i < size; i++) {
            App* app = apps[i]();
            App::Resut res = app->run(setTimes, true); // we always set the run time since this needs to keep shuffling
            delete app;
            if (res == App::KEYBOARD_STOP) {
                return;
            }
        }
    }
}