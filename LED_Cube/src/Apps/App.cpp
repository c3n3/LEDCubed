#include "App.h"

App::Resut App::init() {return App::CONTINUE;}
void App::end() {}
App::~App() {}
bool App::characterInput()
{
    c = 0; // resets the character every frame
    if (Input::available())
    {
        c = Input::read();
    }
    return c != PS2_ESC;
}

App::Resut App::frame()
{
    return App::STOP; // this kills the program
};

App::Resut App::run(uint32_t time, bool timed)
{
    uint32_t appTimer = millis();
    timer = millis();
    App::Resut res = App::CONTINUE;
    if ((res = init()) & App::STOP) {  // init the function
        return res;
    }
    // This may look confusing, but the magic is in the characterInput() and frame() function calls
    // this loop will continueously check the conditions until one is false
    // The way this loop ends is either the characterInput() function takes in an ESC character, or YOUR frame program returns STOP_PROGRAM
    while (true) {
        res = !timed || millis() - appTimer < time ? App::CONTINUE : App::TIMER_STOP;
        if (res) {
            break;
        }
        res = !characterInput() ? App::KEYBOARD_STOP : App::CONTINUE;
        if (res) {
            break;
        }
        res = frame();
        if (res) {
            break;
        }
    }
    end();
    return res;   
}