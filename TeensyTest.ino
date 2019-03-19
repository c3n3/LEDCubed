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

void set_led( uint8_t x, uint8_t y, uint8_t z, uint16_t r, uint16_t g, uint16_t b);
void drawBall( int x, int y, int z, uint16_t color);
void bounceBall(int iterations);



PS2Keyboard keyboard;
volatile uint8_t     gs_buf[NUM_BYTES];  //Buffer written to TLCs over SPI (12 bit color values)
volatile uint16_t    px_buf[NUM_LEDS];   //Pixel buffer storing each LED color as a 16 bit value ( RRRRRGGGGGGBBBBB )

int animation = 0;
int key = 9;
int x = 5;
int y = 5;
int z = 5;

//uint8_t x;
//uint8_t y;
//uint8_t z;
//uint16_t blue = 0x000F;
uint32_t white = 0xFFFF;
uint32_t timer0;



int count = 0;

void setup()
{
    delay(1000);
    keyboard.begin(15, 21);
    Serial.begin(9800);
    Serial.println("hello");

    
    timer0 = millis();
    

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

//Coordinates and RGB values and buffer. RGB range 0-255
void set_led( uint8_t x, uint8_t y, uint8_t z, uint16_t r, uint16_t g, uint16_t b){
    px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y] = ((r & 0x00F8) << 8 ) |
    ((g & 0x00FC) << 3 ) |
    ((b & 0x00F8) >> 3 );
}
//packs a rgb color into one number
uint16_t pk_color(uint16_t r, uint16_t g, uint16_t b) {
    return ((r & 0x00F8) << 8 ) |
    ((g & 0x00FC) << 3 ) |
    ((b & 0x00F8) >> 3 );
}
uint16_t firstCol = pk_color(255, 140, 0);
uint16_t secondCol = pk_color(0, 0, 255);
uint16_t thirdCol = pk_color(0, 255, 0);
uint16_t fourthCol = pk_color(255, 50, 0);

//self explainatory
void clearCube(){
    memset((uint16_t *)px_buf, 0x0000, NUM_LEDS * 2);
}

//houses the edata for the whole cube
uint16_t LEDArray(uint8_t x, uint8_t y, uint8_t z){
    return px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y];
}

//Set led with packed color value
void set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c){
    px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y] = c;
}


//this function switches which orientation you may look at the cube, the  coordinates go as follows, the face you look at for each direction, the reletive 'z' coordinate is the third one, the reletive 'x' is either the true z or x direction, and the second coordinate is always the reletive 'y'
uint16_t directionalCubeArray(uint8_t firstCord, uint8_t secondCord, uint8_t thirdCord, uint16_t color, uint8_t direction, boolean setLED){
    if (setLED){
        switch (direction) { //you can set leds
            case 0:
                set_led_pk(firstCord, thirdCord, secondCord, color);
                break;
            case 1:
                set_led_pk(firstCord, secondCord, thirdCord, color);
                break;
            case 2:
                set_led_pk(11 - thirdCord, secondCord, firstCord, color);
                break;
            case 3:
                set_led_pk(11 - firstCord, secondCord, 11 - thirdCord, color);
                break;
            case 4:
                set_led_pk(thirdCord, secondCord, 11 - firstCord, color);
                break;
            case 5:
                set_led_pk(firstCord, 11 - thirdCord, secondCord, color);
                break;

            default:
                break;
        }
        return 0;
    }
    else {
        switch (direction) {//or you can call the array for the cube, it returns the value
            case 0:
                return LEDArray(firstCord, thirdCord, secondCord);
                break;
            case 1:
                return LEDArray(firstCord, secondCord, thirdCord);
                break;
            case 2:
                return LEDArray(11 - thirdCord, secondCord, firstCord);
                break;
            case 3:
                return LEDArray(11 - firstCord, secondCord, 11 - thirdCord);
                break;
            case 4:
                return LEDArray(thirdCord, secondCord, 11 - firstCord);
                break;
            case 5:
                return LEDArray(firstCord, 11 - thirdCord, secondCord);
                break;

            default:
                break;
        }
    }


}

void moveRow(int firstCord, int secondCord, uint16_t color, boolean collective, int direction, uint16_t specificColor, uint8_t start, uint8_t end){


    if (!collective && end == 11){
        directionalCubeArray(firstCord, secondCord, 11, 0, direction, true);
    }
    for (int i = 10 - (11 - end); i >= 0 + start; i--){
        if (specificColor == 1) {
            if (directionalCubeArray(firstCord, secondCord, i, 0, direction, false) != 0){
                if (collective){
                    if (directionalCubeArray(firstCord, secondCord, i + 1, 0, direction, false) == 0){
                        if (color == 1){
                            directionalCubeArray(firstCord, secondCord, i + 1, directionalCubeArray(firstCord, secondCord, i, 0, direction, false), direction, true);
                        }
                        else {
                            directionalCubeArray(firstCord, secondCord, i, color, direction, true);
                        }
                        directionalCubeArray(firstCord, secondCord, i, 0, direction, true);
                    }

                }
                else {

                    if (color == 1){
                        directionalCubeArray(firstCord, secondCord, i + 1, directionalCubeArray(firstCord, secondCord, i, 0, direction, false), direction, true);
                    }
                    else {
                        directionalCubeArray(firstCord, secondCord, i + 1, color, direction, true);
                    }
                    directionalCubeArray(firstCord, secondCord, i, 0, direction, true);
                }
            }
        }
        else {
            if (directionalCubeArray(firstCord, secondCord, i, 0, direction, false) != 0 && directionalCubeArray(firstCord, secondCord, i, 0, direction, false) == specificColor){
                if (collective){
                    if (directionalCubeArray(firstCord, secondCord, i + 1, 0, direction, false) == 0){
                        if (color == 1){
                            directionalCubeArray(firstCord, secondCord, i + 1, directionalCubeArray(firstCord, secondCord, i, 0, direction, false), direction, true);
                        }
                        else {
                            directionalCubeArray(firstCord, secondCord, i, color, direction, true);
                        }
                        directionalCubeArray(firstCord, secondCord, i, 0, direction, true);
                    }

                }
                else {

                    if (color == 1){
                        directionalCubeArray(firstCord, secondCord, i + 1, directionalCubeArray(firstCord, secondCord, i, 0, direction, false), direction, true);
                    }
                    else {
                        directionalCubeArray(firstCord, secondCord, i + 1, color, direction, true);
                    }
                    directionalCubeArray(firstCord, secondCord, i, 0, direction, true);

                }
            }
        }
    }

}


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






// Add loop code
void loop()
{

  //this is curently just a simple 'dodge' game
    int delayTime = 120;
    int x = rand() % 12;
    int y = rand() % 12;
    int z = rand() % 12;
    int t = rand() % 12;

    if (key != 7){
        set_led_pk(5, 5, 1, 0xF00);
        set_led_pk(6, 5, 1, 0xF00);
        set_led_pk(5, 6, 1, 0xF00);
        set_led_pk(6, 6, 1, 0xF00);

        key = 7;
    }
    
 char c;
  
  if (keyboard.available()){
    c=keyboard.read();
  Serial.print(c);

  }

    if (c == 'w'){
        for (int i = 0; i < 12; i++){
            
            moveRow(i, 1, 1, true, 0, 0xF00, 0, 11);
            c = '[';
        }
    }
    else if (c == 's'){
        for (int i = 0; i < 12; i++){
            moveRow(i, 1, 1, true, 5, 0xF00, 0, 11);
            c = '[';
        }
    }
    else if (c == 'a'){
        for (int i = 0; i < 12; i++){
            
            moveRow(1, i, 1, true, 2, 0xF00, 0, 11);
            c = '[';
        }
    }
    else if (c == 'd'){
        for (int i = 0; i < 12; i++){
            
            moveRow(10, i, 1, true, 4, 0xF00, 0, 11);
            c = '[';
        }
    }
    
    
    if (millis() - timer0 > delayTime){

        set_led_pk(y, x, 11, 0xFFF);
        set_led_pk(t, z, 11, 0xFFF);
        
        for (int i = 0; i < 12; i++){
            for (int j = 0; j < 12; j++){
              
                moveRow(i, j, 1, false, 3, 0xFFF, 0, 11);
            }
        }
     animation = (animation+1) % 5;
     timer0 += delayTime;
   }
} //end loop

/*
 void pk_color(uint16_t r, uint16_t g, uint16_t b){
 return ((r & 0x00F8) << 8 ) |
 ((g & 0x00FC) << 3 ) |
 ((b & 0x00F8) >> 3 );
 }*/



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
    }
}
