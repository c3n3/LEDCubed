#include <PS2Keyboard.h>
#include "SPI.h"
#include "TLC_lib.h"
#include "MUX_lib.h"

// Core library for code-sense - IDE-based
#if defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(ESP8266) // ESP8266 specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.8 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

volatile uint8_t     gs_buf[NUM_BYTES];  //Buffer written to TLCs over SPI (12 bit color values)
volatile uint16_t    px_buf[NUM_LEDS];   //Pixel buffer storing each LED color as a 16 bit value ( RRRRRGGGGGGBBBBB )

#include <math.h>
#include "PS2Keyboard.h"
#include "src/Tools/Input/Input.h"
#include "src/LED_Cube_library/globals.h"
#include "src/Tools/OS/Menu.h"
#include "src/Apps/App_Includes.h"
#include "src/Apps/Animations/Wave2.0.h"
#include "src/Apps/App.h"
#include "src/Tools/MathObjects/UltamateTrigLookUp.h"

// just no, no, no. This must be exterminated
uint16_t white = 0xFFFF;

// setup function
void setup()
{
    delay(1000);

    // only one will be victorious....
    Input::keyboard.begin(15, 21);

    delay(200);
    mux_init();
    init_TLC();
    memset((uint8_t *)gs_buf, 0xFF, NUM_BYTES);
    delay(100);
    write_dot_correction((uint8_t *)gs_buf);
    memset((uint8_t *)gs_buf, 0x00, NUM_BYTES);
    memset((uint16_t *)px_buf, 0x0000, NUM_LEDS * 2);
    mux_begin();
    delay(200);

    pinMode(23, OUTPUT);
    digitalWrite(23, HIGH);
}

/**************************************************************************
 *
 *
 *
 *  The loop call
 *
 *
 *
 **************************************************************************/
void loop()
{
    // TypeEngine::autoTypeUpper("Hello jacob", 0x003F, 0xFD00); 
    // TypeEngine::autoTypeLower("    this is test", 0x000F, 0xF000); 
    // delay(1000);
    // return;
    // App* app = App::Ctor<Snow>();
    // app->run();
    AppCtor stuff[] = {
        App::Ctor<Wave>, App::Ctor<Swirl>, App::Ctor<Wave>, App::Ctor<Space>, App::Ctor<Snow>
    };
    AppCtor Apps[] = {
        App::Ctor<Snake>, App::Ctor<Dodge>
    };
     AppCtor* screenSaver = stuff;
    // creation of the menu application 
     Menu menu = Menu(Apps, 2, screenSaver, 5);
    menu.run(); // thats all folks
} //end loop