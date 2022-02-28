#pragma once
#include "Firework.h"

// a small ball effect 
FireWorkEffect SmallBallWithFade(
    [](ui8 x, ui8 y, ui8 z, Color& color, int& interval) {
        // ignore interval and draw ball
        for (int i = 0; i < 3; i++) {
            protected_set_led_pk(x + i - 1, y, z, color);
            protected_set_led_pk(x, y + i - 1, z, color);
            protected_set_led_pk(x, y, z + i - 1, color);
        }
        color--;
    },
    8, // how many intervals till the effect is dead 
    300 // interval time 
);

// a large star effect
FireWorkEffect LargeStarWithFade(
    [](ui8 x, ui8 y, ui8 z, Color& color, int& interval) {
        // ignore interval and draw ball

        // inner small diagnals for 3 axis (3 choose 2 == 3)
        for (int i = 0; i < 3; i++) {
            // x - y plane
            protected_set_led_pk(x + i - 1, y + i - 1, z, color);
            protected_set_led_pk(x + i - 1, y - i + 1, z, color);

            // x - z plane
            protected_set_led_pk(x + i - 1, y, z + i - 1, color);
            protected_set_led_pk(x + i - 1, y, z - i + 1, color);

            // y - z plane
            protected_set_led_pk(x, y + i - 1, z + i - 1, color);
            protected_set_led_pk(x, y + i - 1, z - i + 1, color);
        }
        // the large star points
        for (int i = 0; i < 5; i++) {
            protected_set_led_pk(x + i - 1, y, z, color);
            protected_set_led_pk(x, y + i - 1, z, color);
            protected_set_led_pk(x, y, z + i - 1, color);
        }
        color--; // just naively fade the color right now
    },
    8,
    300
);