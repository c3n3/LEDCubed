#include <PS2Keyboard.h>

#include <vector>
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
//#include "helper_functions.h"
// #include "Helpful_Functions.h"
// #include "src/Apps/App_Includes.h"
#include "src/LED_Cube_library/globals.h"
#include "src/Apps/App_Includes.h"
#include "src/Apps/App.h"

// #define GAMEAMOUNT 3
// #define ANIMATIONAMOUNT 6
// //store all functions in here after declaration
// App applications[2][GAMEAMOUNT > ANIMATIONAMOUNT ? GAMEAMOUNT : ANIMATIONAMOUNT] () 
// {{Snow(), Swirl()}, {Dodge(), Snake(), Pong()}};

// std::vector <App*> games{new Dodge(), new Snake(), new Pong()};
// std::vector <App*> animations{new Snow(), new Swirl()};

uint16_t white = 0xFFFF;

PS2Keyboard keyboard;

// font for typeing on the cube
uint16_t font[37] = {
   //A
    0b1111000101111100
  ,
   //B
    0b1111110101010100
  ,
   //C
    0b0111010001100010
  ,
   //D
    0b1111110001011100
  ,
   //E
    0b1111110101100010
  ,
   //F
    0b1111100101000010
  ,
   //G
    0b0111010001011000
  ,
   //H
    0b1111100100111110
  ,
   //I
    0b1000111111100010
  ,
   //J
    0b0100010000011110
  ,
   //k
    0b1111101110100010
  ,
   //L
    0b1111110000100000
  ,
   //M
    0b1111100110111110
  ,
   //N
    0b1111101110111110
  ,
   //O
    0b0111010001011100
  ,
   //P
    0b1111100101000100
  ,
   //Q
    0b0111011001101100
  ,
   //R
    0b1111100101110100
  ,
   //S
    0b1001010101010010
  ,
   //T
    0b0000111111000010
  ,
   //U
    0b0111110000011110
  ,
   //V
    0b0011110000001110
  ,
   //W
    0b1111101100111110
  ,
   //X
    0b1101100100110110
  ,
   //Y
    0b0001111100000110
  ,
   //Z
    0b1100110101100110
  ,
   //1
    0b1001011111100000
  ,
   //2
    0b1100110101100110
  ,
   //3
    0b1010110101011100
  ,
   //4
    0b0011100100111110
  ,
   //5
    0b1001110101010010
  ,
   //6
    0b0111010101010000
  ,
   //7
    0b0000100001111110
  ,
   //8
    0b1101110101110110
  ,
   //9
    0b0001100101111110
  ,
   //0
    0b1111110001111110
  ,
   //
    0b0000000000000000
  ,
};

void setup()
{
    delay(1000);
    keyboard.begin(15, 21);
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
    const uint8_t appElements = 5;
    const uint8_t screenSaverElements = 2;
    App* stuff[appElements] = {new Snake(), new Dodge(), new Pong(), new Snow(), new Swirl()};
    App* screenSaver[screenSaverElements] = {new Snow(), new Swirl()};

    Menu menu = Menu(((App**)stuff), appElements, (App**)screenSaver, screenSaverElements);

    menu.run();
} //end loop