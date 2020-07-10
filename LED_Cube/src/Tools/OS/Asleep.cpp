#include "Asleep.h"
Asleep::Asleep(App** a, uint8_t m) {
    apps = a;
    size = m;
};

void Asleep::go(uint32_t setTimes) {
    while (true) {
        if (keyboard.available() && keyboard.read() == PS2_ESC) { // only leave on escape. No other key does anything
            return;
        }
        for (int i = 0; i < size; i++) {
            apps[i]->run(setTimes, true); // we always set the run time since this needs to keep shuffling
        }
    }
}