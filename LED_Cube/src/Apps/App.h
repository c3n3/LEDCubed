#ifndef APP
#define APP
#include "../Tools/Input/Input.h"


// the run() function within an app will be a sefcontained loop that runs until "ESC" is pressed or the app has ended
class App {
public:
    enum Resut {
        CONTINUE = 0x00,
        STOP = 0x80,
        TIMER_STOP = 0x81,
        KEYBOARD_STOP = 0x83
    };
protected:

    // a basic integer for use with timing since almost all apps use one; maybe we could use static as that might save us some memory and only one app can run at a time
    uint32_t timer;

    // the input character used to test esc and for the frame() function
    char c;

    // this is the function that is called to get character input and set the c member. returns char == PS2_ESC
    bool characterInput();
    
    // this is the function that signifies a single 'frame' of an app. ie it is run every loop cycle
    // This is the most important function as this is where YOU right your code to make an app
    // this is also not pure virtual so that if someone wants to overide the run() function they can and not impliment a fake frame() function
    virtual App::Resut frame();

    // called before the frame loop
    virtual App::Resut init();

    // called after the frame loop
    virtual void end();

public:
    virtual ~App();
    // title of the App
    const String title = "";

    // The run function that is called when a user 'opens' the app
    // If you need more control than what frame() gives, then override this function
    virtual App::Resut run(uint32_t time = 0, bool timed = false);

    template<class C>
    static App* Ctor() {
        return new C();
    }
};

typedef App* (*AppCtor)();

#endif
