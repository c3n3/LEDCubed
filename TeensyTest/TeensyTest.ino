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
void randomColors();
uint8_t GAMEAMOUNT = 2;
uint8_t ANIMATIONAMOUNT = 5;
uint8_t INTERACTIVEANIMATIONSAMOUNT = 1;
//store all functions in here after declaration
void (*appFunctions[3][5])() {{lightCube, snow, randomColors, lights, test}, {someThing},  {dodgeGame, snakeGame}};
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

uint8_t phase = 0; //strictly for the color shifting of the snake game


//uint8_t x;
//uint8_t y;
//uint8_t z;
//uint16_t blue = 0x000F;
uint32_t white = 0xFFFF;
uint32_t timer0;



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
    Serial.begin(9800);
    Serial.println("hello");


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

void d(uint16_t t){
    uint32_t temp = millis();
    while (millis() - temp < t) {
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


uint16_t setPackedPackedLED(uint16_t coord, uint16_t c) {
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

void drawNumber(int number, int x1, int y1, int z1, directions viewpoint, uint16_t color) {
    if (number == 0) {
        directionalCubeArray(x1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+1, z1, viewpoint, true, color);
    }
    else if (number == 1) {
        directionalCubeArray(x1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+3, z1, viewpoint, true, color);
    }
    else if (number == 2) {
        directionalCubeArray(x1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+2, z1, viewpoint, true, color);
    }
    else if (number == 3) {
        directionalCubeArray(x1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1, z1, viewpoint, true, color);
    }
    else if (number == 4) {
        directionalCubeArray(x1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+4, z1, viewpoint, true, color);
    }
    else if (number == 5) {
        directionalCubeArray(x1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1, z1, viewpoint, true, color);
    }
    else if (number == 6) {
        directionalCubeArray(x1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+1, z1, viewpoint, true, color);
    }
    else if (number == 7) {
        directionalCubeArray(x1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+4, z1, viewpoint, true, color);
    }
    else if (number == 8) {
        directionalCubeArray(x1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+1, z1, viewpoint, true, color);
    }
    else if (number == 9) {
        directionalCubeArray(x1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+1, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+2, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+3, z1, viewpoint, true, color);
        directionalCubeArray(x1+2, y1+4, z1, viewpoint, true, color);
        directionalCubeArray(x1+1, y1+4, z1, viewpoint, true, color);
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//DrawFigure
//Coordinate 1: (x1,y2,z2)
//Coordinate 2: (x2,y2,z2);
void DrawFigure(int x1, int y1, int z1, int x2, int y2, int z2) {
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
            set_led(x1,i,z1,255,255,255);
            //delay(200);
            set_led(x1,i,z2,255,255,255);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++) {
            set_led(x1,y1,i,255,255,255);
            //delay(200);
            set_led(x1,y2,i,255,255,255);
            //delay(200);
        }
    }
    else if (yDist == 0) { // if the y coordinates are the same, the shape will be a square will a constant y value
        for (int i = x1; i <= x2; i++){
            set_led(i,y1,z1,255,255,255);
            //delay(200);
            set_led(i,y1,z2,255,255,255);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++) {
            set_led(x1,y1,i,255,255,255);
            //delay(200);
            set_led(x2,y1,i,255,255,255);
            //delay(200);
        }
    }
    else if (zDist == 0) { // if the z coordinates are the same, the shape will be a square will a constant z value
        for (int i = x1; i <= x2; i++){
            set_led(i,y1,z1,255,255,255);
            //delay(200);
            set_led(i,y2,z1,255,255,255);
            //delay(200);
        }
        for (int i = y1; i <= y2; i++) {
            set_led(x1,i,z1,255,255,255);
            //delay(200);
            set_led(x2,i,z1,255,255,255);
            //delay(200);
        }
    }
    else { // if none of the x/y/z coordinates match the other points' x/y/z, then the shape will be a cube.
        for (int i = x1; i <= x2; i++){
            set_led(i,y1,z1,255,255,255);
            //delay(200);
            set_led(i,y2,z1,255,255,255);
            //delay(200);
            set_led(i,y1,z2,255,255,255);
            //delay(200);
            set_led(i,y2,z2,255,255,255);
            //delay(200);
        }
        for (int i = y1; i <= y2; i++){
            set_led(x1,i,z1,255,255,255);
            //delay(200);
            set_led(x2,i,z1,255,255,255);
            //delay(200);
            set_led(x1,i,z2,255,255,255);
            //delay(200);
            set_led(x2,i,z2,255,255,255);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++){
            set_led(x1,y1,i,255,255,255);
            //delay(200);
            set_led(x1,y2,i,255,255,255);
            //delay(200);
            set_led(x2,y1,i,255,255,255);
            //delay(200);
            set_led(x2,y2,i,255,255,255);
            //delay(200);
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
    while(true) {
        char c;
        
        if (keyboard.available()) {
            c = keyboard.read();
            //i = c - '0';
        }
        
    switch (state) {
            int y;
        case TOP:

            if (c == PS2_RIGHTARROW) {
                clearCube();

                stateSwitch = shifter(stateSwitch, RIGHT, TOP);
            }
            if (c == PS2_LEFTARROW) {
                clearCube();

                stateSwitch = shifter(stateSwitch, LEFT, TOP);

            }
            else if (c == PS2_ENTER) {
                state = mainStates(stateSwitch);
                clearCube();
                i=0;
                break;
            }
            y=0;
            drawNumber(stateSwitch + 1, 5, 5, 0, FORWARD, 0xF0F0);
            drawNumber(stateSwitch + 1, 5, 5, 1, FORWARD, 0xF0F0);

            break;
            
        case ANIMATIONS:

            if (c == PS2_ESC) {
                state = TOP;
                clearCube();
                break;

            }
            
            else if (c == PS2_LEFTARROW) {
                i = shifter(i, LEFT, ANIMATIONS);
                clearCube();

            }
            else if (c == PS2_RIGHTARROW) {
                i = shifter(i, RIGHT, ANIMATIONS);
                clearCube();

            }
            
            else if (c == PS2_ENTER){
                appFunctions[0][i]();
            }
            drawNumber(i + 1, 5, 5, 0, FORWARD, 0xFFFF);
            drawNumber(i + 1, 5, 5, 1, FORWARD, 0xFFFF);

            break;
            
        case GAMES:

            if (c == PS2_ESC) {
                state = TOP;
                clearCube();
                break;
            }
            
            else if (c == PS2_LEFTARROW) {
                i = shifter(i, LEFT, GAMES);
                clearCube();

            }
            else if (c == PS2_RIGHTARROW) {
                i = shifter(i, RIGHT, GAMES);
                clearCube();

            }
            
            else if (c == PS2_ENTER){
            appFunctions[2][i]();
            }
            drawNumber(i + 1, 5, 5, 0, FORWARD, 0xFFFF);
            drawNumber(i + 1, 5, 5, 1, FORWARD, 0xFFFF);

            break;
        
            case INTERACTIVEANIMATIONS:
            
            if (c == PS2_ESC) {
                state = TOP;
                clearCube();
                break;
            }
            
            else if (c == PS2_LEFTARROW) {
                i = shifter(i, LEFT, INTERACTIVEANIMATIONS);
                clearCube();
                
            }
            else if (c == PS2_RIGHTARROW) {
                i = shifter(i, RIGHT, INTERACTIVEANIMATIONS);
                clearCube();
                
            }
            
            else if (c == PS2_ENTER){
                appFunctions[1][i]();
            }
            drawNumber(i + 1, 5, 5, 0, FORWARD, 0xFFFF);
            drawNumber(i + 1, 5, 5, 1, FORWARD, 0xFFFF);
            
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



// Add loop code
void loop()
{
    mainSwitch(TOP);
  //this is curently just a simple 'dodge' game
    
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
            dificultyTimer += 5000;
            
        }
        uint16_t delayTime = 500;
    
    
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
            dificultyTimer = millis();
    if (millis() - timer0 > delayTime){
        
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

uint16_t colorShifter(uint16_t currentColor) {
    
    uint8_t r  = (currentColor & 0xF800) >> 8;
    uint16_t g = (currentColor & 0x07E0) >> 3;
    uint16_t b = (currentColor & 0x001F) << 3;
//    Serial.println('c');
//    Serial.print(currentColor);
//    Serial.println();
    b = b - 8; //better way
    

//    Serial.print('g');
//    Serial.print(g);
//   Serial.print('b');
//    Serial.println(b);
//    Serial.println(phase);
 /*   switch (phase) {
        case 0:
            if (r > 16) {
                r = r - 14;
            }
            else if (g > 16) {
                g -= 14;
            }
            else {
                phase = 1;
            }
            break;
            
        case 1:
            if (b > 16) {
                b -= 14;
                r += 14;
            }
            else if (g < 244) {
                g += 14;
            }
            else {
                phase = 2;
            }
            break;
            
        case 2:
            
            if (b < 244) {
                b += 14;
            }
            else {
                phase = 0;
            }
            
            break;
        default:
            break;
    }
    
    Serial.print(pk_color(r, g, b));*/
    return pk_color(r, g, b);
    
}

void MoveLED(uint8_t x, uint8_t y, uint8_t z, uint16_t currentColor, boolean gainLength) {
    currentColor = colorShifter(currentColor);
    
//    Serial.println(0xFFFF);
//    Serial.println(colorShifter(0xFFFF));
//    Serial.println(LEDArray(x, y, z));
    Serial.println(z);

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
        if (z-1 < 12) {
            MoveLED(x, y, z-1, currentColor, gainLength);
        }
    }
    else if (gainLength) {
        set_led_pk(x, y, z, colorShifter(currentColor));

    }
    else {
        set_led_pk(x, y, z - 1, 0);
    }
    
}



void snakeGame() {
#define MAX_SNAKE_LEN 50
#define NUM_FOOD 5
    boolean start = false;
    uint16_t color = 0xFFFF;
    uint8_t x = 5;
    uint8_t y = 5;
    uint8_t z = 4;
    uint8_t x2 = 5;
    uint8_t y2 = 3;
    uint8_t z2 = 6;
//    uint8_t fx;
//    uint8_t fy;
//    uint8_t fx;
    directions direction = FORWARD;
    uint32_t foodTimer;
    uint32_t moveTimer = millis();
    boolean addLength = false;
    //coord_t food[NUM_FOOD];
    //uint8_t eatenFood = 100;
    
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
        }
    
        if (!start) {
//            fx = rand() % 12;
//            fy = rand() % 12;
//            fz = rand() % 12;
            clearCube();
            //if (c != ']') {
            for (int i = 0; i < 4; i++) {
                set_led_pk(5, 5, 4 - i, color);


                color = colorShifter(color);
                
               // Serial.print((color));
            }
            start = true;

            //}
        }

        switch (c) {
            case PS2_LEFTARROW:
                direction = LEFT;
                break;
            case PS2_RIGHTARROW:
                direction = RIGHT;
                break;
            case PS2_ENTER:
                direction = DOWN;
                break;
            case '\\':
                direction = UP;
                break;
            case PS2_DOWNARROW:
                direction = BACKWARD;
                break;
            case PS2_UPARROW:
                direction = FORWARD;
                break;
            default:
                break;
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
        if (millis() - foodTimer >= 15000 && addLength) {
            
            foodTimer += 15000;
        }
        
        if (millis() - moveTimer > 2000) {
            if (!(x == 12 || z == 12 || y == 12)) {
        switch (direction) {
            case FORWARD:
                set_led_pk(x, y, z + 1, 0xFFFF);
                z++;
                break;
            case BACKWARD:
                set_led_pk(x, y, z - 1, 0xFFFF);
                z--;
                break;
            case UP:
                set_led_pk(x, y+1, z, 0xFFFF);
                y++;
                break;
            case DOWN:
                set_led_pk(x, y-1, z, 0xFFFF);
                y--;
                break;
            case LEFT:
                set_led_pk(x-1, y, z, 0xFFFF);
                x--;
                break;
            case RIGHT:
                set_led_pk(x+1, y, z, 0xFFFF);
                x++;
                break;
                
            default:
                break;
               // if (
        }
//                if (x == fx && y == fy, && fz == z) {
//                    addLength = true;
//                }
        MoveLED(x2, y2, z2, 0xFFFF, addLength);
            moveTimer += 2000;
                
            }
            
            
        }
    
    }
#undef MAX_SNAKE_LEN
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
        ////delay(200);
        //test of the github
    }
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
 while (!kill) {
    char c;
    if (keyboard.available()){
 
        c=keyboard.read();
        if (c == PS2_ESC) {
            kill = true;
        }
    }

    //DO STUFF HERE
 
 
    }
 kill = false;
 clearCube();
 }
*/
