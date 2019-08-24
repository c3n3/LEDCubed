//
// TeensyTest
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

#include "helperFunctions.h"
#include "subApplicationFunctions.h"
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
void set_led( uint8_t x, uint8_t y, uint8_t z, uint16_t r, uint16_t g, uint16_t b);
void drawBall( int x, int y, int z, uint16_t color);
void bounceBall(int iterations);
void dodgeGame();
void lightCube();
void snow();
void snakeGame();
void someThing();
void lights();
void test();
void swirl();
void pong();
void randomColors();
#define GAMEAMOUNT 3
#define ANIMATIONAMOUNT 5
#define INTERACTIVEANIMATIONSAMOUNT 1
//store all functions in here after declaration
void (*appFunctions[3][5])() {{lightCube, snow, randomColors, swirl, test}, {someThing},  {dodgeGame, snakeGame, pong}};
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

//mainStates state = TOP;

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

/**************************************************************************
 *
 *
 *
 *  Functions to aid animations/games below
 *
 *
 *
 **************************************************************************/


//Coordinates and RGB values and buffer. RGB range 0-255
void set_led( uint8_t x, uint8_t y, uint8_t z, uint16_t r, uint16_t g, uint16_t b){
    px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y] = ((r & 0x00F8) << 8 ) |
    ((g & 0x00FC) << 3 ) |
    ((b & 0x00F8) >> 3 );
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void protected_set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c){
    if (!(x > 11 || y > 11 || z > 11)) {
    px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y]  = c;
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void d(uint16_t t){
    uint32_t temp = millis();
    while (millis() - temp < t) {
        if (keyboard.available()) {
            if (keyboard.read() == PS2_ESC) {
                break;
            }
        }
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//packs a rgb color into one number
uint16_t pk_color(uint16_t r, uint16_t g, uint16_t b) {

    return ((r & 0x00F8) << 8 ) |
    ((g & 0x00FC) << 3 ) |
    ((b & 0x00F8) >> 3 );
}


/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/
// red goes up to 31
//blue to 31
//green up to 63
uint16_t pk_low(uint16_t r, uint16_t g, uint16_t b) {
    return ((r & 0x001F) << 11 ) |
    ((g & 0x003F) << 5 ) |
    ((b & 0x001F));
}
/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/


uint16_t pk_coord(uint8_t x, uint8_t y, uint8_t z) {
    return (((z << 4) | y) << 4) | x;
}


/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

uint8_t shifter(uint8_t k, directions more, mainStates state) {
    uint8_t amount = 3; //for the top level
    if (state == GAMES) {
        amount = GAMEAMOUNT;
    }
    else if (state == ANIMATIONS) {
        amount = ANIMATIONAMOUNT;
    }
    else if (state == INTERACTIVEANIMATIONS) {

        amount = INTERACTIVEANIMATIONSAMOUNT;
    }

    if (more == RIGHT) {
        if (k == amount - 1) {
            k = 0;
        }
        else {
            k++;

        }
    }
    else if (more == LEFT){
        if (k == 0) {
            k = amount - 1;
        }
        else {
            k--;

        }
    }
    return k;
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//self explainatory
void clearCube(){
    memset((uint16_t *)px_buf, 0x0000, NUM_LEDS * 2);
}

//void adressToCoordinate

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//houses the edata for the whole cube
uint16_t LEDArray(uint8_t x, uint8_t y, uint8_t z){
    if (!(z > 11 || x > 11|| y > 11)) {
    return px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y];
    }
    else {
        return 0;
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//Set led with packed color value
void set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c){
    px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y] = c;
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//Set led with packed color value
void setAdressLED( uint16_t address, uint16_t c){
    px_buf[address] = c;
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/


void setPackedPackedLED(uint16_t coord, uint16_t c) {
    //set_led_pk((coord & 0x000F), (coord & 0x00F0), (coord & 0x0F00), c);
    px_buf[ ((coord & 0x0F00) >> 8) * NUM_LEDS_LYR + NUM_LEDS_DIM * (coord & 0x000F) + ((coord & 0x00F0) >> 4)] = c;
}


/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//this function switches which orientation you may look at the cube, the  coordinates go as follows, the face you look at for each direction, the reletive 'z' coordinate is the third one, the reletive 'x' is either the true z or x direction, and the second coordinate is always the reletive 'y'
uint16_t directionalCubeArray(uint8_t firstCord, uint8_t secondCord, uint8_t thirdCord, directions direction, boolean setLED = false, uint16_t color = 0){


    if (setLED){
        switch (direction) { //you can set leds
            case UP:
                set_led_pk(firstCord, thirdCord, secondCord, color);
                break;
            case FORWARD:
                set_led_pk(firstCord, secondCord, thirdCord, color);
                break;
            case LEFT:
                set_led_pk(11 - thirdCord, secondCord, firstCord, color);
                break;
            case BACKWARD:
                set_led_pk(11 - firstCord, secondCord, 11 - thirdCord, color);
                break;
            case RIGHT:
                set_led_pk(thirdCord, secondCord, 11 - firstCord, color);
                break;
            case DOWN:
                set_led_pk(firstCord, 11 - thirdCord, secondCord, color);
                break;

            default:
                break;
        }
        return 0;
    }
    else {
        switch (direction) {//or you can call the array for the cube, it returns the value
            case UP:
                return LEDArray(firstCord, thirdCord, secondCord);
                break;
            case FORWARD:
                return LEDArray(firstCord, secondCord, thirdCord);
                break;
            case LEFT:
                return LEDArray(11 - thirdCord, secondCord, firstCord);
                break;
            case BACKWARD:
                return LEDArray(11 - firstCord, secondCord, 11 - thirdCord);
                break;
            case RIGHT:
                return LEDArray(thirdCord, secondCord, 11 - firstCord);
                break;
            case DOWN:
                return LEDArray(firstCord, 11 - thirdCord, secondCord);
                break;

            default:
                break;
        }
    }


}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void rotate(uint16_t t) {
    uint32_t timer  = millis();
    uint32_t R0Time = millis();
    uint32_t R1Time = millis();
    uint32_t R2Time = millis();
    uint32_t R3Time = millis();
    uint32_t R4Time = millis();
    uint32_t R5Time = millis();

    while (millis() - timer < t) {

    }

}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void moveRow(uint8_t firstCord, uint8_t secondCord,  directions direction,  uint16_t specificColor = 1, boolean collective = false, uint8_t start = 0, uint8_t end = 11, uint16_t color = 1){


    if (!collective && end == 11){
        directionalCubeArray(firstCord, secondCord, 11, direction, true);
    }
    for (int i = 10 - (11 - end); i >= 0 + start; i--) {
        if (specificColor == 1) {
            if (directionalCubeArray(firstCord, secondCord, i, direction) != 0){
                if (collective){
                    if (directionalCubeArray(firstCord, secondCord, i + 1, direction) == 0){
                        if (color == 1){
                            directionalCubeArray(firstCord, secondCord, i + 1,  direction, true, directionalCubeArray(firstCord, secondCord, i, direction));
                        }
                        else {
                            directionalCubeArray(firstCord, secondCord, i, direction, true, color);
                        }
                        directionalCubeArray(firstCord, secondCord, i, direction, true);
                    }

                }
                else {

                    if (color == 1){
                        directionalCubeArray(firstCord, secondCord, i + 1, direction, true, directionalCubeArray(firstCord, secondCord, i, direction));
                    }
                    else {
                        directionalCubeArray(firstCord, secondCord, i + 1, direction, true, color);
                    }
                    directionalCubeArray(firstCord, secondCord, i, direction, true);
                }
            }
        }
        else {
            if (directionalCubeArray(firstCord, secondCord, i, direction) != 0 && directionalCubeArray(firstCord, secondCord, i, direction) == specificColor){
                if (collective){
                    if (directionalCubeArray(firstCord, secondCord, i + 1, direction) != specificColor){
                        if (color == 1){
                            directionalCubeArray(firstCord, secondCord, i + 1, direction, true, directionalCubeArray(firstCord, secondCord, i, direction, false));
                        }
                        else {
                            directionalCubeArray(firstCord, secondCord, i, direction, true, color);
                        }
                        directionalCubeArray(firstCord, secondCord, i, direction, true);
                    }

                }
                else {

                    if (color == 1){
                        directionalCubeArray(firstCord, secondCord, i + 1,  direction, true, directionalCubeArray(firstCord, secondCord, i, direction));
                    }
                    else {
                        directionalCubeArray(firstCord, secondCord, i + 1, direction, true, color);
                    }
                    directionalCubeArray(firstCord, secondCord, i, direction, true);

                }
            }
        }
    }

}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void eradicate(uint16_t color) {
    for (uint8_t i = 0; i < 12; i++) {
        for (uint8_t j = 0; j < 12; j++) {
            for (uint8_t k = 0; k < 12; k++) {
                if (LEDArray(i, j, k) == color) {
                    set_led(i, j, k, 0, 0, 0);
                }
            }
        }
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void setRandomLED(uint8_t leds, directions direction, uint16_t color, boolean threeD = false) {
    if (!threeD) {
    for (uint8_t i = 0; i < leds; i++) {
        directionalCubeArray(rand() % 12, rand() % 12, 0, direction, true, color);
    }
    }
}
/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//no up or down yet
void angledMove(uint8_t rise, uint8_t run, directions direction, uint16_t color) {
    //rise
    for (uint8_t k = 0; k < rise; k++) {
        for (uint8_t i = 0; i < 12; i++) {
            for (uint8_t j = 0; j < 12; j++) {
                moveRow(i, j, UP, color);
            }
        }
    }
    //rise
    for (uint8_t k = 0; k < run; k++) {
        for (uint8_t i = 0; i < 12; i++) {
            for (uint8_t j = 0; j < 12; j++) {
                moveRow(i, j, direction, color);
            }
        }
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/
 /***************************************************************************
  *
  *   Sub Seperator
  *
  ***************************************************************************/

uint8_t getFontIndex(char c) {
  switch (c) {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    case 'D': return 3;
    case 'E': return 4;
    case 'F': return 5;
    case 'G': return 6;
    case 'H': return 7;
    case 'I': return 8;
    case 'J': return 9;
    case 'K': return 10;
    case 'L': return 11;
    case 'M': return 12;
    case 'N': return 13;
    case 'O': return 14;
    case 'P': return 15;
    case 'Q': return 16;
    case 'R': return 17;
    case 'S': return 18;
    case 'T': return 19;
    case 'U': return 20;
    case 'V': return 21;
    case 'W': return 22;
    case 'X': return 23;
    case 'Y': return 24;
    case 'Z': return 25;
    case 1: return 26;
    case 2: return 27;
    case 3: return 28;
    case 4: return 29;
    case 5: return 30;
    case 6: return 31;
    case 7: return 32;
    case 8: return 33;
    case 9: return 34;
    case 0: return 35;
    case PS2_BACKSPACE: return 36;
  }
}

void drawChar(char c, int x1, int y1, int z1, directions viewpoint, uint16_t color) {
    for (int i = 1; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        if (font[getFontIndex(c)][j*i]) {
          directionalCubeArray(x1 + i - 1, y1 + j*i, z1, viewpoint, true, color);
        }
      }
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void typeChars(char c){
  directions direction = FORWARD;
  uint8_t xPosition = charCount % 4;
  uint8_t yPosition = 7;
  uint16_t color = 0xFFFF;
  if (charCount % 2) {
    color = 0x00FF;
  }
  if (charCount > 20) {
    yPosition = 0;
  }
  if ((charCount <= 8 && 4 < charCount) || charCount > 20) {
    direction = LEFT;
  } else if (charCount <= 12) {
    direction = BACKWARD;
  }  else if (charCount <= 16) {
    direction = RIGHT;
  } else if (charCount <= 24) {
    direction = FORWARD;
  }
  if (c == PS2_BACKSPACE) {
    charCount--;
  } else {
    charCount++;
  }
  drawChar(c, xPosition, yPosition, 0, direction, color);
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//DrawFigure
//Coordinate 1: (x1,y2,z2)
//Coordinate 2: (x2,y2,z2);
void DrawFigure(int x1, int y1, int z1, int x2, int y2, int z2, uint16_t color) {
    int xDist = abs(x1 - x2);
    int yDist = abs(y1 - y2);
    int zDist = abs(z1 - z2);
    if (x1 > x2){ //created in order to make the 'for' loops always accurate
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y1 > y2){ // created in order to make the 'for' loop always accurate
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }
    if (z1 > z2) { // created in order to make the 'for' loop always accurate
        int temp = z1;
        z1 = z2;
        z2 = temp;
    }
    if (xDist == 0) { // if the x coordinates are the same, the shape will be a square will a constant x value
        for (int i = y1; i <= y2; i++){
            set_led_pk(x1,i,z1,color);
            //delay(200);
            set_led_pk(x1,i,z2,color);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++) {
            set_led_pk(x1,y1,i,color);
            //delay_pk(200);
            set_led_pk(x1,y2,i,color);
            //delay(200);
        }
    }
    else if (yDist == 0) { // if the y coordinates are the same, the shape will be a square will a constant y value
        for (int i = x1; i <= x2; i++){
            set_led_pk(i,y1,z1,color);
            //delay_pk(200);
            set_led_pk(i,y1,z2,color);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++) {
            set_led_pk(x1,y1,i,color);
            //delay_pk(200);
            set_led_pk(x2,y1,i,color);
            //delay(200);
        }
    }
    else if (zDist == 0) { // if the z coordinates are the same, the shape will be a square will a constant z value
        for (int i = x1; i <= x2; i++){
            set_led_pk(i,y1,z1,color);
            //delay_pk(200);
            set_led_pk(i,y2,z1,color);
            //delay(200);
        }
        for (int i = y1; i <= y2; i++) {
            set_led_pk(x1,i,z1,color);
            //delay+pk(200);
            set_led_pk(x2,i,z1,color);
            //delay(200);
        }
    }
    else { // if none of the x/y/z coordinates match the other points' x/y/z, then the shape will be a cube.
        for (int i = x1; i <= x2; i++){
            set_led_pk(i,y1,z1,color);
            //delay_pk(200);
            set_led_pk(i,y2,z1,color);
            //delay_pk(200);
            set_led_pk(i,y1,z2,color);
            //delay_pk(200);
            set_led_pk(i,y2,z2,color);
            //delay(200);
        }
        for (int i = y1; i <= y2; i++){
            set_led_pk(x1,i,z1,color);
            //delay_pk(200);
            set_led_pk(x2,i,z1,color);
            //delay_pk(200);
            set_led_pk(x1,i,z2,color);
            //delay_pk(200);
            set_led_pk(x2,i,z2,color);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++){
            set_led_pk(x1,y1,i,color);
            //delay_pk(200);
            set_led_pk(x1,y2,i,color);
            //delay_pk(200);
            set_led_pk(x2,y1,i,color);
            //delay_pk(200);
            set_led_pk(x2,y2,i,color);
            //delay(200);
        }
    }
}
void clearMost(uint8_t howMany, directions backSide) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            for (int k = 11; k > 11-howMany; k--) {
                directionalCubeArray(i, j, k, backSide, true);
            }
        }
    }
}

/**************************************************************************
 *                                                                        *
 * ************************************************************************
 *                                                                        *
 *  Main Switch Function below                                            * ***************************
 *                                                                        *
 * ************************************************************************
 *                                                                        *
 **************************************************************************/

void mainSwitch(mainStates state) {
    int i = 0;
    uint8_t stateSwitch = 0;
    uint32_t backgroundTimer = millis();
    while(true) {

        if (millis() - backgroundTimer > 200) {

           // setRandomLED(3, DOWN, 0xFFFF);
            for (uint8_t j = 0; j < 12; j++) {
            for (uint8_t i = 0; i < 12; i++) {
             //   moveRow(i, j, DOWN);
            }
            backgroundTimer += 200;
        }
        }

        char c;

        if (keyboard.available()) {
            c = keyboard.read();
            //i = c - '0';
        }
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                for (int k = 0; k < 6; k++) {
                    set_led_pk(i, j, k + 6, 0);
                }
            }
        }

    switch (state) {
            //int y;
        case TOP:

            if (c == PS2_RIGHTARROW) {
                clearMost(6, BACKWARD);

                stateSwitch = shifter(stateSwitch, RIGHT, TOP);
            }
            if (c == PS2_LEFTARROW) {
                clearMost(6, BACKWARD);

                stateSwitch = shifter(stateSwitch, LEFT, TOP);

            }
            else if (c == PS2_ENTER) {
                state = mainStates(stateSwitch);
                clearMost(6, BACKWARD);
                i=0;
                break;
            }
            //y=0;
            drawChar(stateSwitch + 1, 5, 5, 0, FORWARD, 0xF0F0);
            drawChar(stateSwitch + 1, 5, 5, 1, FORWARD, 0xF0F0);

            break;

        case ANIMATIONS:

            if (c == PS2_ESC) {
                state = TOP;
                clearMost(6, BACKWARD);
                break;

            }

            else if (c == PS2_LEFTARROW) {
                i = shifter(i, LEFT, ANIMATIONS);
                clearMost(6, BACKWARD);

            }
            else if (c == PS2_RIGHTARROW) {
                i = shifter(i, RIGHT, ANIMATIONS);
                clearMost(6, BACKWARD);

            }

            else if (c == PS2_ENTER){
                appFunctions[0][i]();
            }
            drawChar(i + 1, 5, 5, 0, FORWARD, 0xFFFF);
            drawChar(i + 1, 5, 5, 1, FORWARD, 0xFFFF);

            break;

        case GAMES:

            if (c == PS2_ESC) {
                state = TOP;
                clearMost(6, BACKWARD);
                break;
            }

            else if (c == PS2_LEFTARROW) {
                i = shifter(i, LEFT, GAMES);
                clearMost(6, BACKWARD);
            }
            else if (c == PS2_RIGHTARROW) {
                i = shifter(i, RIGHT, GAMES);
                clearMost(6, BACKWARD);

            }

            else if (c == PS2_ENTER){
            appFunctions[2][i]();
            }
            drawChar(i + 1, 5, 5, 0, FORWARD, 0xFFFF);
            drawChar(i + 1, 5, 5, 1, FORWARD, 0xFFFF);

            break;

            case INTERACTIVEANIMATIONS:

            if (c == PS2_ESC) {
                state = TOP;
                clearMost(6, BACKWARD);
                break;
            }

            else if (c == PS2_LEFTARROW) {
                i = shifter(i, LEFT, INTERACTIVEANIMATIONS);
                clearMost(6, BACKWARD);

            }
            else if (c == PS2_RIGHTARROW) {
                i = shifter(i, RIGHT, INTERACTIVEANIMATIONS);
                clearMost(6, BACKWARD);

            }

            else if (c == PS2_ENTER){
                appFunctions[1][i]();
            }
            drawChar(i + 1, 5, 5, 0, FORWARD, 0xFFFF);
            drawChar(i + 1, 5, 5, 1, FORWARD, 0xFFFF);

            break;

    }
        c = ']';

}
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

    mainSwitch(TOP);

} //end loop


/**************************************************************************
 *
 *
 *
 *  all sub function below, all are self contained 'apps' called within the Main Switch function (must be declared within the two areas up top too.
 *
 *
 *
 **************************************************************************/


void dodgeGame() {

    uint32_t timer0 = millis();
    uint32_t dificultyTimer = millis();
    uint32_t time1 = millis();
    uint8_t ledCount = 3;
    uint8_t key = 0;
    boolean start = false;
    clearCube();
    while (true){

        if (millis() - dificultyTimer > 5000 && start) {

            ledCount++;
            Serial.print(ledCount);
            dificultyTimer += 5000;

        }
        uint16_t delayTime = 150;


    if (key != 7){
        set_led_pk(5, 5, 1, 0xF00);
        set_led_pk(6, 5, 1, 0xF00);
        set_led_pk(5, 6, 1, 0xF00);
        set_led_pk(6, 6, 1, 0xF00);
        set_led_pk(5, 5, 2, 0xF00);
        set_led_pk(6, 5, 2, 0xF00);
        set_led_pk(5, 6, 2, 0xF00);
        set_led_pk(6, 6, 2, 0xF00);


    }

    char c;

    if (keyboard.available()){
        start = true;
        c=keyboard.read();
        Serial.print(c);
        if (c == PS2_ESC) {
            break;
        }
    }

    if (c == PS2_UPARROW){
        for (int i = 0; i < 12; i++){
            moveRow(i, 1, UP, 0xF00, true);
            moveRow(i, 2, UP, 0xF00, true);
            c = '[';
        }
    }
    else if (c == PS2_DOWNARROW){
        for (int i = 0; i < 12; i++){
            moveRow(i, 1, DOWN, 0xF00, true);
            moveRow(i, 2, DOWN, 0xF00, true);
            c = '[';
        }
    }
    else if (c == PS2_LEFTARROW){
        for (int i = 0; i < 12; i++){
            moveRow(1, i, LEFT, 0xF00, true);
            moveRow(2, i, LEFT, 0xF00, true);
            c = '[';
        }
    }
    else if (c == PS2_RIGHTARROW){
        for (int i = 0; i < 12; i++){

            moveRow(10, i, RIGHT, 0xF00, true);
            moveRow(9, i, RIGHT, 0xF00, true);
            c = '[';
        }
    }

        if (start) {
    if (millis() - timer0 > delayTime){
        Serial.print(ledCount);
        setRandomLED(ledCount, BACKWARD, 0xFFF);


        for (int i = 0; i < 12; i++){
            for (int j = 0; j < 12; j++){

                moveRow(i, j, BACKWARD, 0xFFF);
            }

        }
        timer0 += delayTime;
    }
}
        else if (key != 7) {
            setRandomLED(ledCount, BACKWARD, 0xFFF);
            key = 7;
        }
    }
    clearCube();
}

/***************************************************************************
 *
 *   Sub Seperator t
 *
 ***************************************************************************/

void dropMatch() {
    for (int p = 0; p < 3; p++) {

    for (int k = 0; k < 12; k++) {
        for (int j = 0; j < 12; j++) {
            for (int i = 0; i < 12; i++) {
                if (LEDArray(i, k, j) == 0) {
        set_led_pk(i, j, k, 0xF800);
                }
            }
        }
    }
    d(250);
    clearCube();
        d(250);

    }
}
void lightMatch() {
    dropMatch();
}
void pourGasoline() {
    lightMatch();
}

uint16_t colorShifter(uint16_t currentColor) {
    boolean state = false;
    uint8_t r  = (currentColor & 0xF800) >> 11;
    uint16_t g = (currentColor & 0x07E0) >> 5;
    uint16_t b = (currentColor & 0x001F);
    if (state) {
        if (b != 31) { b++; } else if (r != 63) { r++; } else { state = true; }
    } else {
    if (b != 0) { b--; } else if (r != 0) { r--; } else {state = false;}
    }
    return pk_low(r, g, b);
}

void MoveLED(uint8_t x, uint8_t y, uint8_t z, uint16_t currentColor, boolean gainLength) {
    currentColor = colorShifter(currentColor);

//    Serial.println(0xFFFF);
//    Serial.println(colorShifter(0xFFFF));
//    Serial.println(LEDArray(x, y, z));

    if (LEDArray(x + 1, y, z) == currentColor) {
        set_led_pk(x, y, z, currentColor);
        MoveLED(x + 1, y, z, currentColor, gainLength);
    }
    else if (LEDArray(x - 1, y, z) == currentColor) {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x - 1, y, z, currentColor, gainLength);

    }
    else if (LEDArray(x, y+1, z) == currentColor) {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x, y + 1, z, currentColor, gainLength);

    }
    else if (LEDArray(x, y-1, z) == currentColor) {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x, y-1, z, currentColor, gainLength);

    }
    else if (LEDArray(x, y, z+1) == currentColor) {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x, y, z+1, currentColor, gainLength);

    }
    else if (LEDArray(x, y, z-1) == currentColor) {
        set_led_pk(x, y, z, currentColor);
        //Serial.println("z-1");
        //uses underflow
        if (z-1 < 12) {
            MoveLED(x, y, z-1, currentColor, gainLength);
        }
    }
    else if (gainLength) {
        set_led_pk(x, y, z, currentColor);

    }
  else {
      set_led_pk(x, y, z, 0);
  }

}



void snakeGame() {
#define NUM_FOOD 10
    boolean start = false;
    uint16_t color = 0xFFFF;
    boolean toggle = false;
    uint8_t x = 5;
    uint8_t y = 5;
    uint8_t z = 4;
    uint8_t x2 = 5;
    uint8_t y2 = 3;
    uint8_t z2 = 6;
    uint16_t speed = 500;
    uint16_t length = 4;
//    uint8_t fx;
//    uint8_t fy;
//    uint8_t fx;
    directions direction = FORWARD;
    uint32_t foodTimer = millis();
    uint32_t moveTimer = millis();
    boolean addLength = false;
    coord_t food[NUM_FOOD];
    boolean endGame = false;

   // coord_t snake[ MAX_SNAKE_LEN ];
   // coord_t * sk_head = snake;
   // coord_t * sk_tail = snake;
    while (true) {
        char c = ']';

        if (keyboard.available()){
            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }

            // so that the snake cannot eat itself
            if (c == PS2_LEFTARROW && direction == RIGHT) {
                c = ']';
            } else if (c == PS2_RIGHTARROW && direction == LEFT) {
                c = ']';
            } else if (c == PS2_DOWNARROW && direction == FORWARD) {
                c = ']';
            } else if (c == PS2_UPARROW && direction == BACKWARD) {
                c = ']';
            } else if ((c == '1' || c == 'r') && direction == DOWN) {
                c = ']';
            } else if ((c == '0' || c == 'f')  && direction == UP) {
                c = ']';
            }
        }

        if (!start) {
            clearCube();
            for (int i = 0; i < 4; i++) {
                set_led_pk(5, 5, 4 - i, color);
                color = colorShifter(color);
            }
            for (int i = 0; i < NUM_FOOD; i++) {
                while (true) {
                food[i].x = rand() % 12;
                food[i].y = rand() % 12;
                food[i].z = rand() % 12;
                    if (LEDArray(food[i].x, food[i].y, food[i].z) == 0) {
                        break;
                    }
                }
            }
            start = true;
        }

        if (millis() - foodTimer > 900) {
            if (toggle) {
                for (int i = 0; i < NUM_FOOD; i++ ) {
                    set_led_pk(food[i].x, food[i].y, food[i].z, 0xF830);
                }
                toggle = !toggle;
            } else {
                for (int i = 0; i < NUM_FOOD; i++ ) {
                    set_led_pk(food[i].x, food[i].y, food[i].z, 0x031F);
                }
                toggle = !toggle;
            }
            foodTimer += 900;
        }

        switch (c) {
            case PS2_LEFTARROW: direction = LEFT; break;
            case PS2_RIGHTARROW: direction = RIGHT; break;
            case '0': direction = DOWN; break;
            case 'f': direction = DOWN; break;
            case 'r': direction = UP; break;
            case '1': direction = UP; break;
            case PS2_DOWNARROW: direction = BACKWARD; break;
            case PS2_UPARROW: direction = FORWARD; break;
            default: break;
        }


        x2 = x;
        y2 = y;
        z2 = z;

//        if (addLength && eatenFood != 100) {
//            food[eatenFood] = {
//
//
//            }
//        }


        if (millis() - moveTimer > speed && !endGame) {
            if (length >= 7 && speed > 300) {
                speed -= 90;
                length = 0;
            }
            if (!(x == 12 || z == 12 || y == 12)) {
        switch (direction) {
            case FORWARD:
                z++;
                break;
            case BACKWARD:
                z--;
                break;
            case UP:
                y++;
                break;
            case DOWN:
                y--;
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;

            default:
                break;
                    }

                for (int i = 0; i < NUM_FOOD; i++) {
                    if (food[i].x == x && food[i].y == y && food[i].z == z) {
                        while (true) {
                        food[i].x = rand() % 12;
                        food[i].y = rand() % 12;
                        food[i].z = rand() % 12;
                        addLength = true;
                            if (LEDArray(food[i].x, food[i].y, food[i].z) == 0) {
                                length++;
                                break;
                            }
                        }

                    }

                }
                if (LEDArray(x, y, z) != 0 && addLength != true || (x - 1 >= 11 || y - 1 >= 11 || z - 1 >= 11)) {
                    endGame = true;
                    pourGasoline();
                } else {
                set_led_pk(x, y, z, 0xFFFF);

        MoveLED(x2, y2, z2, 0xFFFF, addLength);
                addLength = false;
            moveTimer += speed;
                }
            }

        }

    }
#undef NUM_FOOD
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void lightCube() {
    boolean lightUp = true;
    uint32_t timer = millis();
    uint8_t i = 0;
    while (true) {
        char c;

        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;

            }
        }


        if (lightUp){
            if (millis() - timer > 200) {

            for (int l = 0; l < 12; l++){
                for (int j = 0; j < 12; j++){
                    for (int k = 0; k < 12; k++){
                        set_led(l, j, k, i * (255 / 10), i * (0 / 10), i * (255 / 10));

                    }
                }
            }

            if (i == 11){
                lightUp = false;

            }
            else {
            i++;
            }
            timer += 200;
            }
        }
        else {
            if (millis() - timer > 200) {

            for (int l = 0; l < 12; l++){
                for (int j = 0; j < 12; j++){
                    for (int k = 0; k < 12; k++){
                        set_led(l, j, k, i * (255 / 10), i * (0 / 10), i * (255 / 10));
                    }
                }
            }

            if (i == 0){
                lightUp = true;
            }else {
            i--;
            }
            timer += 200;
        }
        }
}
    clearCube();
}
/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void drawCrossHelper(coord_t p) {
  for (int i = 0; i < 12; i++) {
    if (!LEDArray(i, p.y, p.z)) {
      set_led_pk(i, p.y, p.z, 0x3333);
    }
  }
  for (int i = 0; i < 12; i++) {
    if (!LEDArray(p.x, p.y, i)) {
      set_led_pk(p.x, p.y, i, 0x3333);
    }
  }
  for (int i = 0; i < 12; i++) {
    if (!LEDArray(p.x, i, p.z)) {
      set_led_pk(p.x, i, p.z, 0x3333);
    }
  }
}

void drawObject(coord_t p) {
    for(int i = p.x - 1; i < p.x + 1; i++) {
      protected_set_led_pk(i, i, p.z);
      protected_set_led_pk(12 - i, 12 - i, p.z);
        }

      for(int i = p.z - 1; i < p.z + 1; i++) {
        protected_set_led_pk(p.x, i, i);
        protected_set_led_pk(p.x, 12 - i, 12 - i);
    }
}

void objectSomethingGame() {
  #define NUM_ATTACKERS 5
  coord_t crossPoint;
  coord_t attackers[NUM_ATTACKERS];
  crossPoint.x = 5;
  crossPoint.y = 5;
  crossPoint.z = 5;
  uint32_t timer = millis();
  while (true) {
     char c;
     if (keyboard.available()){

       for (int i = 0; i < NUM_ATTACKERS; i++) {
            attackers[i].x = 13;
            attackers[i].y = 13;
            attackers[i].z = 13;
          }
         c=keyboard.read();
         if (c == PS2_ESC) {
             break;
         }
     }

     if (millis() - timer > 2000) {}


       timer = millis();
     }

     switch (c) {
         case PS2_LEFTARROW: crossPoint.x--; break;
         case PS2_RIGHTARROW: crossPoint.x++; break;
         case '0': crossPoint.y--; break;
         case 'w': crossPoint.y++; break;
         case 's': crossPoint.y--; break;
         case '1': crossPoint.y++; break;
         case PS2_DOWNARROW: crossPoint.z--; break;
         case PS2_UPARROW: crossPoint.z++; break;
         default: break;
     }

     // draw the cross hairs on the cube at a regular interval
     if (millis() - timer > 150) {
       drawCrossHelper(crossPoint);
       timer = millis();
     }

     }
  clearCube();
  #undef NUM_ATTACKERS
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void someThing() {
    uint32_t resetTime = millis();
    uint32_t timer = millis();
    while (true) {
        char c;

        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }
        if (millis() - resetTime > 20000) {
            for (int h = 0; h < 12; h++) {
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, DOWN);
                }
            }
                d(60);
            }
            resetTime += 20000;
        }
        if (millis() - timer > 150){
        set_led(rand() % 12, rand() % 12, rand() % 12, rand() % 255, rand() % 255, rand() % 255);
            timer += 150;
        }
        if (c == PS2_BACKSPACE) {
            resetTime = millis();
            uint8_t r = rand() % 2;
            uint8_t g = rand() % 2;
            uint8_t b = rand() % 2;
            if (r + b + g == 0){
                r = 1;
                b = 1;
            }
            for (int i = 1; i < 10; i++){
                for (int l = 0; l < 12; l++){
                    for (int j = 0; j < 12; j++){
                        for (int k = 0; k < 12; k++){
                            set_led(l, j, k, r * i * (255 / 10), g * i * (255 / 10),  b * i * (255 / 10));

                        }
                    }
                }
                d(12); //delay

            }
            for (int i = 9; i >= 0; i--){
                for (int l = 0; l < 12; l++){
                    for (int j = 0; j < 12; j++){
                        for (int k = 0; k < 12; k++){
                            set_led(l, j, k, r * i * (255 / 10), g * i * (255 / 10), b * i * (255 / 10));
                        }
                    }
                }
                d(12); //delay
            }
            c = ']';
        }

        if (c == PS2_UPARROW){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                moveRow(i, j, FORWARD, 1, true);
                c = '[';
            }
        }
        }
        else if (c == PS2_DOWNARROW){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, BACKWARD, 1, true);
                    c = '[';
                }
            }
        }


        else if (c == PS2_LEFTARROW){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, LEFT, 1, true);
                    c = '[';
                }
            }
        }


        else if (c == PS2_RIGHTARROW){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, RIGHT, 1, true);
                    c = '[';
                }
            }
        }
        else if (c == 'h'){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, DOWN, 1, true);
                    c = '[';
                }
            }
        }
        else if (c == 'y'){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, UP, 1, true);
                    c = '[';
                }
            }
        }




    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void lights() {

    while (true) {
        char c;

        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }

        setPackedPackedLED(rand() % 4096 & 0x0777, 0xFFFF);
        clearCube();
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/
void snow() {

    uint32_t timer = millis();
    while (true) {
        char c;

        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }

    if (millis() - timer > 260) {


    //int color = rand() % 64000;
    int count = 0;



        //delay(260);
    for (int i = 0; i < 12; i++){
        for (int f  = 0; f < 12; f++){
            count = 0;
            for (int g = 0; g < 4; g++){
                if (LEDArray(i, g, f) != 0){
                    count += 1;
                }
                if (count == 4){
                    set_led_pk(i, g, f, 0);
                }

            }
        }
    }

    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 12; j++){
            if (rand() % 25 != 1){
                moveRow(j, i, DOWN, 1, true);
            }
            else {
                moveRow(j, i, DOWN, 1, false);
            }
        }
    }
        int num = rand() % 12;
        int num1 = rand() % 12;
        int num2 = rand() % 12;
        set_led_pk(num, 11, num2, white);
        set_led_pk(num1, 11, num, white);
        set_led_pk(num2, 11, num1, white);
            timer += 260;
        }
    }
    clearCube();
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void drawBall( int x, int y, int z, uint16_t color){
    for(int i=-1; i<=1; i++){
        for(int j=-1; j<=1; j++){
            for(int k=-1; k<=1; k++){
                if( i*j*k == 0 )    //make sure one is zero so the corners don't get drawn
                    set_led_pk(x+i,y+j,z+k, color);
            }
        }
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void pong() {
#define PADDLE_LENGTH 3
#define P1_COLOR 0xFFFF
#define P2_COLOR 0xFFFE
#define BALL_COLOR 0xF81F
#define BALL_REFRESH 200
    boolean start = false;
//    vector_t rise;
//    rise.magnitude = 0;
//    rise.direction = UP;
//    vector_t run;
//    run.magnitude = 0;
//    run.direction = FORWARD;
    directionalFloat_t slope;
    slope.ofRise = DOWN;
    slope.ofRun = LEFT;
    slope.ofZRun = BACKWARD;
    slope.zRun = 1;
    slope.rise = 1;
    slope.run = 1;
    float ballx = 0;
    float bally = 3;
    float ballz = 5;
    coord_t player1;
    player1.x = 11;
    player1.y = 3;
    player1.z = 3;
    coord_t player2;
    player2.x = 0;
    player2.y = 3;
    player2.z = 3;
    coord_t ball;
    ball.x = 6;
    ball.y = 6;
    ball.z = 6;
    uint32_t ballTimer = millis();

    while (true) {
        char c = ']';
        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }
        if (((uint8_t) (ballx + 0.5) != ball.x || (uint8_t) (bally + 0.5) != ball.y || (uint8_t) (ballz + 0.5) != ball.z) || !start) {

        }

        if (!start) {
            start = true;
        }
        // Move the paddles location
        switch (c) {
                //ifs use underflow
            case 's': if (!(player2.y + PADDLE_LENGTH == 11)) { player2.y++; eradicate(P2_COLOR); } break;
            case 'z': if (!(player2.z == 0)) { player2.z--; eradicate(P2_COLOR); } break;
            case 'q': if (!(player2.z + PADDLE_LENGTH == 11)) { player2.z++; eradicate(P2_COLOR); } break;
            case 'a': if (!(player2.y == 0)) { player2.y--; eradicate(P2_COLOR); } break;

            case '5': if (!(player1.y + PADDLE_LENGTH == 11)) { player1.y++; eradicate(P1_COLOR); } break;
            case '3': if (!(player1.z == 0)) { player1.z--; eradicate(P1_COLOR); } break;
            case '9': if (!(player1.z + PADDLE_LENGTH == 11)) { player1.z++; eradicate(P1_COLOR); } break;
            case '6': if (!(player1.y == 0)) { player1.y--; eradicate(P1_COLOR); } break;
        }

        }

//  MOVE THE FLOATED REFERENCE POINT FOR THA BALL
        if (millis() - ballTimer > BALL_REFRESH) {
        switch (slope.ofRise) {
            case FORWARD: ballz += (slope.rise); break;
            case UP: bally += slope.rise; break;
            case BACKWARD: ballz -= slope.rise; break;
            case RIGHT: ballx += slope.rise; break;
            case DOWN: bally -= slope.rise; break;
            case LEFT: ballx -= slope.rise; break;
            }
            switch (slope.ofRun) {
                case FORWARD: ballz += (slope.run); break;
                case UP: bally += slope.run; break;
                case BACKWARD: ballz -= slope.run; break;
                case RIGHT: ballx += slope.run; break;
                case DOWN: bally -= slope.run; break;
                case LEFT: ballx -= slope.run; break;
            }
            switch (slope.ofZRun) {
                case FORWARD: ballz += (slope.zRun); break;
                case UP: bally += slope.zRun; break;
                case BACKWARD: ballz -= slope.zRun; break;
                case RIGHT: ballx += slope.zRun; break;
                case DOWN: bally -= slope.zRun; break;
                case LEFT: ballx -= slope.zRun; break;
            }
            ballTimer += BALL_REFRESH;
            if (ball.x != (uint8_t) (ballx + 0.5) || ball.y != (uint8_t) (bally + 0.5) || ball.z != (uint8_t) (ballz + 0.5)) {
                eradicate(BALL_COLOR);
            }
            ball.x = (uint8_t) (ballx + 0.5);
            ball.y = (uint8_t) (bally + 0.5);
            ball.z = (uint8_t) (ballz + 0.5);
            if (LEDArray(ball.x, ball.y, ball.z) != 0 || ( ball.x != 0 || ball.x != 11)) {

            if (ball.x > 50) {
                ball.x = 0;
            } else if (ball.x > 11) {
                ball.x = 11;
                if (rand() % 2 == 0) {
                }
            }
                if (ball.y > 50) {
                    ball.y = 0;
                } else if (ball.y > 11) {
                    ball.y = 11;
                }
                if (ball.z > 50) {
                    ball.z = 0;
                } else if (ball.z > 11) {
                    ball.z = 11;
                }

            if (ball.x == 0) {
                slope.ofRise = directions((rand() % 2) * 5);
                slope.ofZRun = directions((rand() % 2) * 2 + 1);

                slope.ofRun = RIGHT;
            } else if (ball.x == 11) {
                slope.ofRun = LEFT;
            }
                if (ball.y == 0) {
                    slope.ofRise = UP;
                } else if (ball.y == 11) {
                    slope.ofRise = DOWN;
                }
                if (ball.z == 0) {
                    slope.ofZRun = FORWARD;
                } else if (ball.z == 11) {
                    slope.ofZRun = BACKWARD;
                }


            for (uint8_t i = 3; i > 0; i--) {
                protected_set_led_pk(ball.x - 2 + i, ball.y, ball.z, BALL_COLOR);
                protected_set_led_pk(ball.x, ball.y, ball.z - 2 + i, BALL_COLOR);
                protected_set_led_pk(ball.x, ball.y - 2 + i, ball.z, BALL_COLOR);
            }
            }
        }



        //draw paddles from location
        DrawFigure(player1.x, player1.y + PADDLE_LENGTH / 2, player1.z + PADDLE_LENGTH / 2, player1.x, player1.y + PADDLE_LENGTH - PADDLE_LENGTH / 2, player1.z + PADDLE_LENGTH - PADDLE_LENGTH / 2, P1_COLOR);
        DrawFigure(player2.x, player2.y + PADDLE_LENGTH / 2, player2.z + PADDLE_LENGTH / 2, player2.x, player2.y + PADDLE_LENGTH - PADDLE_LENGTH / 2, player2.z + PADDLE_LENGTH - PADDLE_LENGTH / 2, P2_COLOR);
        DrawFigure(player1.x, player1.y, player1.z, player1.x, player1.y + PADDLE_LENGTH, player1.z + PADDLE_LENGTH, P1_COLOR);
        DrawFigure(player2.x, player2.y, player2.z, player2.x, player2.y + PADDLE_LENGTH, player2.z + PADDLE_LENGTH, P2_COLOR);
    }
    clearCube(); //exit game
#undef P2_COLOR
#undef P1_COLOR
#undef PADDLE_LENGTH
#undef BALL_COLOR
#undef BALL_REFRESH
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void randomColors() {
    while (true) {
        char c;
        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            for (int k = 0; k < 12; k++) {
                set_led_pk(i, j, k, rand() % 65535);
            }
        }
    }
    }
    clearCube();
}
/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void ballBounce() {
#define PADDLE_LENGTH 3
#define P1_COLOR 0xFFFF
#define P2_COLOR 0xFFFE
#define BALL_COLOR 0xF81F
#define BALL_REFRESH 200
    boolean start = false;
    //    vector_t rise;
    //    rise.magnitude = 0;
    //    rise.direction = UP;
    //    vector_t run;
    //    run.magnitude = 0;
    //    run.direction = FORWARD;
    directionalFloat_t slope;
    slope.ofRise = DOWN;
    slope.ofRun = LEFT;
    slope.ofZRun = BACKWARD;
    slope.zRun = 1;
    slope.rise = 1;
    slope.run = 1;
    float ballx = 0;
    float bally = 3;
    float ballz = 5;
    coord_t player1;
    player1.x = 11;
    player1.y = 3;
    player1.z = 3;
    coord_t player2;
    player2.x = 0;
    player2.y = 3;
    player2.z = 3;
    coord_t ball;
    ball.x = 6;
    ball.y = 6;
    ball.z = 6;
    uint32_t ballTimer = millis();


    while (true) {
        char c = ']';
        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }
        if (((uint8_t) (ballx + 0.5) != ball.x || (uint8_t) (bally + 0.5) != ball.y || (uint8_t) (ballz + 0.5) != ball.z) || !start) {

        }


        if (!start) {
            start = true;
        }
        // Move the paddles location
        switch (c) {
                //ifs use underflow
            case 's': if (!(player2.y + PADDLE_LENGTH == 11)) { player2.y++; eradicate(P2_COLOR); } break;
            case 'z': if (!(player2.z == 0)) { player2.z--; eradicate(P2_COLOR); } break;
            case 'q': if (!(player2.z + PADDLE_LENGTH == 11)) { player2.z++; eradicate(P2_COLOR); } break;
            case 'a': if (!(player2.y == 0)) { player2.y--; eradicate(P2_COLOR); } break;

            case '5': if (!(player1.y + PADDLE_LENGTH == 11)) { player1.y++; eradicate(P1_COLOR); } break;
            case '3': if (!(player1.z == 0)) { player1.z--; eradicate(P1_COLOR); } break;
            case '9': if (!(player1.z + PADDLE_LENGTH == 11)) { player1.z++; eradicate(P1_COLOR); } break;
            case '6': if (!(player1.y == 0)) { player1.y--; eradicate(P1_COLOR); } break;
            default:
                break;
        }

        //  MOVE THE FLOATED REFERENCE POINT FOR THA BALL
        if (millis() - ballTimer > BALL_REFRESH) {
            switch (slope.ofRise) {
                case FORWARD: ballz += (slope.rise); break;
                case UP: bally += slope.rise; break;
                case BACKWARD: ballz -= slope.rise; break;
                case RIGHT: ballx += slope.rise; break;
                case DOWN: bally -= slope.rise; break;
                case LEFT: ballx -= slope.rise; break;
            }
            switch (slope.ofRun) {
                case FORWARD: ballz += (slope.run); break;
                case UP: bally += slope.run; break;
                case BACKWARD: ballz -= slope.run; break;
                case RIGHT: ballx += slope.run; break;
                case DOWN: bally -= slope.run; break;
                case LEFT: ballx -= slope.run; break;
            }
            switch (slope.ofZRun) {
                case FORWARD: ballz += (slope.zRun); break;
                case UP: bally += slope.zRun; break;
                case BACKWARD: ballz -= slope.zRun; break;
                case RIGHT: ballx += slope.zRun; break;
                case DOWN: bally -= slope.zRun; break;
                case LEFT: ballx -= slope.zRun; break;
            }
            ballTimer += BALL_REFRESH;
            if (ball.x != (uint8_t) (ballx + 0.5) || ball.y != (uint8_t) (bally + 0.5) || ball.z != (uint8_t) (ballz + 0.5)) {
                eradicate(BALL_COLOR);
            }
            ball.x = (uint8_t) (ballx + 0.5);
            ball.y = (uint8_t) (bally + 0.5);
            ball.z = (uint8_t) (ballz + 0.5);
            if (LEDArray(ball.x, ball.y, ball.z) != 0 || ( ball.x != 0 || ball.x != 11)) {

                if (ball.x > 50) {
                    ball.x = 0;
                } else if (ball.x > 11) {
                    ball.x = 11;
                }
                if (ball.y > 50) {
                    ball.y = 0;
                } else if (ball.y > 11) {
                    ball.y = 11;
                }
                if (ball.z > 50) {
                    ball.z = 0;
                } else if (ball.z > 11) {
                    ball.z = 11;
                }

                if (ball.x == 0) {
                    slope.ofRun = RIGHT;
                } else if (ball.x == 11) {
                    slope.ofRun = LEFT;
                }
                if (ball.y == 0) {
                    slope.ofRise = UP;
                } else if (ball.y == 11) {
                    slope.ofRise = DOWN;
                }
                if (ball.z == 0) {
                    slope.ofZRun = FORWARD;
                } else if (ball.z == 11) {
                    slope.ofZRun = BACKWARD;
                }


                for (uint8_t i = 3; i > 0; i--) {
                    protected_set_led_pk(ball.x - 2 + i, ball.y, ball.z, BALL_COLOR);
                    protected_set_led_pk(ball.x, ball.y, ball.z - 2 + i, BALL_COLOR);
                    protected_set_led_pk(ball.x, ball.y - 2 + i, ball.z, BALL_COLOR);
                }
            }
        }

        //draw paddles from location
        DrawFigure(player1.x, player1.y + PADDLE_LENGTH / 2, player1.z + PADDLE_LENGTH / 2, player1.x, player1.y + PADDLE_LENGTH - PADDLE_LENGTH / 2, player1.z + PADDLE_LENGTH - PADDLE_LENGTH / 2, P1_COLOR);
        DrawFigure(player2.x, player2.y + PADDLE_LENGTH / 2, player2.z + PADDLE_LENGTH / 2, player2.x, player2.y + PADDLE_LENGTH - PADDLE_LENGTH / 2, player2.z + PADDLE_LENGTH - PADDLE_LENGTH / 2, P2_COLOR);
        DrawFigure(player1.x, player1.y, player1.z, player1.x, player1.y + PADDLE_LENGTH, player1.z + PADDLE_LENGTH, P1_COLOR);
        DrawFigure(player2.x, player2.y, player2.z, player2.x, player2.y + PADDLE_LENGTH, player2.z + PADDLE_LENGTH, P2_COLOR);
    }
    clearCube(); //exit game
#undef P2_COLOR
#undef P1_COLOR
#undef PADDLE_LENGTH
#undef BALL_COLOR
#undef BALL_REFRESH
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void bounceBall(int iterations){
    int x_vec = 1;
    int y_vec = 1;
    int z_vec = 1;
    int x = 6;
    int y = 7;
    int z = 1;

    memset((uint16_t *)px_buf, 0x0000, NUM_LEDS * 2);

    for( int q = 0; q< iterations; q++){

        drawBall( x, y, z, 0);

        if(x+x_vec >= 11 || x+x_vec <= 0){
            x += (x_vec = -x_vec);
        }
        else{ x += x_vec; }

        if(y+y_vec >= 11 || y+y_vec <= 0){
            y += (y_vec = -y_vec);
        }
        else{ y += y_vec; }

        if(z+z_vec >= 11 || z+z_vec <= 0){
            z += (z_vec = -z_vec);
        }
        else{ z += z_vec; }

        drawBall(x,y,z, 0xFFFF);
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void spiral() {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 12; j++) {
      set_led(j, i, 0, 255, 20*i, 9*i);
      delay(30);
    }
    for (int j = 0; j < 12; j++) {
      set_led(11, i, j, 255, 20*i, 9*i);
      delay(30);
    }
    for (int j = 11; j >= 0; j--) {
      set_led(j, i, 11, 255, 20*i, 9*i);
      delay(30);
    }
    for (int j = 11; j >= 0; j--) {
      set_led(0, i, j, 255, 20*i, 9*i);
      delay(30);
    }
  }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void swirl() {
    boolean start = false;
    clearCube();
    uint32_t timer = millis();
    while (true) {
        char c;

        if (keyboard.available()){
            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }
        if (!start) {
        for (int i = 0; i < 12; i++) {
            directionalCubeArray(i, i, 11, FORWARD, true, 0xF000);
            directionalCubeArray(i, i, 11, BACKWARD, true,  0xFF00);
            directionalCubeArray(i, i, 11, LEFT, true, 0xFFFF);
            directionalCubeArray(i, i, 11, RIGHT, true, 0xF00F);

        }

            for (int i = 1; i < 11; i++) {
                directionalCubeArray(i, 11-i, 10, FORWARD, true, 0xF800);
                directionalCubeArray(i, 11-i, 10, BACKWARD, true,  0x0770);
                directionalCubeArray(i, 11-i, 10, LEFT, true, 0x00EF);
                directionalCubeArray(i, 11-i, 10, RIGHT, true, 0xF00F);
            }

            start = true;
        }

        if (millis() - timer > 100) {
            for (int k = 0; k < 12; k++) {
                moveRow(11, k, FORWARD);
                moveRow(11, k, BACKWARD);
               moveRow(11, k, LEFT);
               moveRow(11, k, RIGHT);

            }
            for (int i = 0; i < 4; i++) {
            for (int k = 1; k < 11; k++) {
                moveRow(1, k, directions(i+1), 1, false, 1, 10);
            }
            }


            timer = millis();
        }
    }

    clearCube();
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/


void test() {
    uint32_t timer = millis();
    uint16_t co = 0xFFFF;
    while (true) {
        char c;
        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                 break;
            }
        }
        if (millis() - timer > 50) {
            co = colorShifter(co);
            timer += 50;

            //Serial.println(((0xFFFF & 0xF800))>>8);

        }
        setPackedPackedLED(pk_coord(1, 1, 1), co);

        //DO STUFF HERE

    }
    clearCube();
}

/***************************************************************************
 *
 *
 *  BASIC 'APP' FUNCTION SETUP BELOW
 *
 *
 ***************************************************************************/
/*
 void NAME() {
 while (true) {
    char c;
    if (keyboard.available()){

        c=keyboard.read();
        if (c == PS2_ESC) {
            break;
        }
    }

    //DO STUFF HERE


    }
 clearCube();
 }
*/
