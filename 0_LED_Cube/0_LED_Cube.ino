#include <PS2Keyboard.h>
//
// 0_LED_Cube
//
//
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author         William Lies
//                 William Lies
//
// Date            10/7/17 10:49 PM
// Version        <#version#>
//
// Copyright    © William Lies, 2017
// Licence        <#licence#>
//
// See         ReadMe.txt for references
//

///TEST COMIT FOR GITHUB
#include "SPI.h"
#include "TLC_lib.h"
#include "MUX_lib.h"
//keyboard library
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

#include "PS2Keyboard.h"
//#include "PS2Keyboard.h"
//hello from xcode
enum mainStates {ANIMATIONS, INTERACTIVEANIMATIONS, GAMES, TOP};
enum directions {UP, FORWARD, LEFT, BACKWARD, RIGHT, DOWN};

typedef struct{
    uint8_t x;
    uint8_t y;
    uint8_t z;
} coord_t;

typedef struct{
    uint8_t magnitude;
    directions direction;
} vector_t;


typedef struct{
    float rise;
    float run;
    float zRun;
    directions ofRise;
    directions ofRun;
    directions ofZRun;
} directionalFloat_t;

/**************************************************************************
 *
 *
 *
 *  Declare all global functions below
 *
 *
 *
 **************************************************************************/

#define GAMEAMOUNT 3
#define ANIMATIONAMOUNT 5
#define INTERACTIVEANIMATIONSAMOUNT 2
//store all functions in here after declaration
void (*appFunctions[3][5])() {{lightCube, snow, randomColors, swirl, test}, {someThing, colorSwitcher},  {dodgeGame, snakeGame, pong}};
//String appFunctions[] = {"dodgeGame"};
/**************************************************************************
 *
 *
 *
 *  Decalare all global variables below
 *
 *
 *
 **************************************************************************/
//escape corispondes to the

mainStates state = TOP;

PS2Keyboard keyboard;
volatile uint8_t     gs_buf[NUM_BYTES];  //Buffer written to TLCs over SPI (12 bit color values)
volatile uint16_t    px_buf[NUM_LEDS];   //Pixel buffer storing each LED color as a 16 bit value ( RRRRRGGGGGGBBBBB )
extern uint8_t font[][15];


uint8_t phase = 0; //strictly for the color shifting of the snake game


//uint8_t x;
//uint8_t y;
//uint8_t z;
//uint16_t blue = 0x000F;
uint32_t white = 0xFFFF;
uint32_t timer0;
uint8_t charCount = 0;


int count = 0;


/**************************************************************************
 *
 *
 *
 *  Setup below
 *
 *
 *
 **************************************************************************/

void setup()
{
    delay(1000);
    keyboard.begin(15, 21);
//    Serial.begin(9800);
//    Serial.println("hello");


    delay(200);
    mux_init();
    init_TLC();
    memset((uint8_t *)gs_buf, 0xFF, NUM_BYTES);
    delay(100);
    write_dot_correction( (uint8_t *)gs_buf );
    memset((uint8_t *)gs_buf, 0x00, NUM_BYTES);
    memset((uint16_t *)px_buf, 0x0000, NUM_LEDS * 2);
    mux_begin();
    delay(200);

    pinMode(23, OUTPUT);
    digitalWrite( 23, HIGH);


}


// font for typeing on the cube
uint8_t font[][15] = {
  { //A
    1,1,1,1,0,
    0,0,1,0,1,
    1,1,1,1,0
  },
  { //B
    1,1,1,1,1,
    1,0,1,0,1,
    0,1,0,1,0
  },
  { //C
    0,1,1,1,0,
    1,0,0,0,1,
    1,0,0,0,1
  },
  { //D
    1,1,1,1,1,
    1,0,0,0,1,
    0,1,1,1,0
  },
  { //E
    1,1,1,1,1,
    1,0,1,0,1,
    1,0,0,0,1
  },
  { //F
    1,1,1,1,1,
    0,0,1,0,1,
    0,0,0,0,1
  },
  { //G
    0,1,1,1,0,
    1,0,0,0,1,
    0,1,1,0,0,
  },
  { //H
    1,1,1,1,1,
    0,0,1,0,0,
    1,1,1,1,1,
  },
  { //I
    1,0,0,0,1,
    1,1,1,1,1,
    1,0,0,0,1
  },
  { //J
    0,1,0,0,0,
    1,0,0,0,0,
    0,1,1,1,1,
  },
  { //k
    1,1,1,1,1,
    0,1,1,1,0,
    1,0,0,0,1
  },
  { //L
    1,1,1,1,1,
    1,0,0,0,0,
    1,0,0,0,0,
  },
  { //M
    1,1,1,1,1,
    0,0,1,1,0,
    1,1,1,1,1,
  },
  { //N
    1,1,1,1,1,
    0,1,1,1,0,
    1,1,1,1,1,
  },
  { //O
    0,1,1,1,0,
    1,0,0,0,1,
    0,1,1,1,0
  },
  { //P
    1,1,1,1,1,
    0,0,1,0,1,
    0,0,0,1,0
  },
  { //Q
    0,1,1,1,0,
    1,1,0,0,1,
    1,0,1,1,0
  },
  { //R
    1,1,1,1,1,
    0,0,1,0,1,
    1,1,0,1,0
  },
  { //S
    1,0,0,1,0,
    1,0,1,0,1,
    0,1,0,0,1,
  },
  { //T
    0,0,0,0,1,
    1,1,1,1,1,
    0,0,0,0,1,
  },
  { //U
    0,1,1,1,1,
    1,0,0,0,0,
    0,1,1,1,1,
  },
  { //V
    0,0,1,1,1,
    1,0,0,0,0,
    0,0,1,1,1,
  },
  { //W
    1,1,1,1,1,
    0,1,1,0,0,
    1,1,1,1,1,
  },
  { //X
    1,1,0,1,1,
    0,0,1,0,0,
    1,1,0,1,1,
  },
  { //Y
    0,0,0,1,1,
    1,1,1,0,0,
    0,0,0,1,1,
  },
  { //Z
    1,1,0,0,1,
    1,0,1,0,1,
    1,0,0,1,1
  },
  { //1
    1,0,0,1,0,
    1,1,1,1,1,
    1,0,0,0,0,
  },
  { //2
    1,1,0,0,1,
    1,0,1,0,1,
    1,0,0,1,1
  },
  { //3
    1,0,1,0,1,
    1,0,1,0,1,
    1,1,1,1,1,
  },
  { //4
    0,0,1,1,1,
    0,0,1,0,0,
    1,1,1,1,1,
  },
  { //5
    1,0,0,1,1,
    1,0,1,0,1,
    0,1,0,0,1,
  },
  { //6
    0,1,1,1,0,
    1,0,1,0,1,
    0,1,0,0,0,
  },
  { //7
    0,0,0,0,1,
    0,0,0,0,1,
    1,1,1,1,1,
  },
  { //8
    1,1,0,1,1,
    1,0,1,0,1,
    1,1,0,1,1,
  },
  { //9
    0,0,0,1,1,
    0,0,1,0,1,
    1,1,1,1,1,
  },
  { //0
    1,1,1,1,1,
    1,0,0,0,1,
    1,1,1,1,1,
  },
  { //
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
  },
};
