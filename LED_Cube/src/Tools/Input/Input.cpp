#include "Input.h"

PS2Keyboard Input::keyboard;


bool Input::available() {
    return Input::keyboard.available();
}

char Input::read() {
    return Input::keyboard.read();
}