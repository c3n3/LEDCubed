#include "Basic_Functions.h"

/**************************************************************************
 *
 *
 *
 *  Functions which are very basic and do not provide any "super" specialized functionality
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

// will not destroy the program if you set a nonexistant LED
void protected_set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c){
    if (!(x > 11 || y > 11 || z > 11)) {
    px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y]  = c;
    }
}

// a delay function that accounts for pressing the escape key
char d(uint16_t t){
    uint32_t temp = millis();
    while (millis() - temp < t) {
        if (keyboard.available()) {
            if (keyboard.read() == PS2_ESC) {
                return PS2_ESC;
            }
        }
    }
}

//packs a rgb color into one number
uint16_t pk_color(uint16_t r, uint16_t g, uint16_t b) {
    return ((r & 0x00F8) << 8 ) |
    ((g & 0x00FC) << 3 ) |
    ((b & 0x00F8) >> 3 );
}

// red goes up to 31
//blue to 31
//green up to 63
uint16_t pk_low(uint16_t r, uint16_t g, uint16_t b) { //gives color values an increment of one
    return ((r & 0x001F) << 11 ) |
    ((g & 0x003F) << 5 ) |
    ((b & 0x001F));
}

// a packed coordinate
uint16_t pk_coord(uint8_t x, uint8_t y, uint8_t z) {
    return (((z << 4) | y) << 4) | x;
}

//self explainatory
void clearCube(){
    memset((uint16_t *)px_buf, 0x0000, NUM_LEDS * 2);
}

//houses the data for the whole cube (wrapper function for the px_buf array )
uint16_t LEDArray(uint8_t x, uint8_t y, uint8_t z){
    if (!(z > 11 || x > 11|| y > 11)) {
    return px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y];
    }
    return 0;
}

//Set led with packed color value
void set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c){
    px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y] = c;
}

//Set led with packed color value by address
void setAddressLED( uint16_t address, uint16_t c){
    px_buf[address] = c;
}

// set led by packed coordinates and packed color
void setPackedPackedLED(uint16_t coord, uint16_t c) {
    //set_led_pk((coord & 0x000F), (coord & 0x00F0), (coord & 0x0F00), c);
    px_buf[ ((coord & 0x0F00) >> 8) * NUM_LEDS_LYR + NUM_LEDS_DIM * (coord & 0x000F) + ((coord & 0x00F0) >> 4)] = c;
}
