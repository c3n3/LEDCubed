#ifndef TEENSY_INPUT
#define TEENSY_INPUT
#include "PS2Keyboard.h"

/**
 * @brief This is a simple static wrapper for input methods (ie the keyboard). This is mainly to provide a clean global method to access the keyboard
 * 
 */
class Input
{
public:
    // this is the static keyboard object
    static PS2Keyboard keyboard;

    // this is the available function
    static bool available();

    // This is the read function for the keyboard
    static char read();
};
#endif