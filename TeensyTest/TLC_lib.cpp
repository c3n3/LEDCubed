//
// TLC_lib.cpp
// C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project 		TeensyTest
//
// Created by 	William Lies, 10/21/17 9:56 AM
// 				William Lies
//
// Copyright 	(c) William Lies, 2017
// Licence		licence
//
// See 			TLC_lib.h and ReadMe.txt for references
//


/*------------------------------------------------------
 *  Automatic Includes
 -----------------------------------------------------*/
// Core library for code-sense - IDE-based
#if defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

/*------------------------------------------------------
 *  User Includes
 -----------------------------------------------------*/
#include "TLC_lib.h"
#include "SPI.h"
#include "MUX_lib.h"

/*------------------------------------------------------
 *  Static Variables
 -----------------------------------------------------*/
//static uint8_t gs_buf[NUM_BYTES];  //buffer for greyscale

/*------------------------------------------------------
 *  Funciton Definitions
 -----------------------------------------------------*/

//Initializes pins and buffer for TLC
//Must be called before any other functions in this file.
//
void init_TLC(){
    pinMode( BLANK, OUTPUT);    //BLANK
    pinMode( GCLK, OUTPUT);    //GCLK
    pinMode( XLAT, OUTPUT);    //XLAT
    pinMode( MOSI, OUTPUT);    //SIN (MOSI)
    pinMode( SCK,  OUTPUT);    //SCK
    pinMode( VPRG, OUTPUT);
    pinMode( DCPRG, OUTPUT);
    
    digitalWriteFast( BLANK, HIGH   );    //BLANK
    digitalWriteFast( GCLK, LOW     );    //GCLK
    digitalWriteFast( XLAT, LOW     );    //XLAT
    digitalWriteFast( MOSI, LOW     );    //SIN (MOSI)
    digitalWriteFast( SCK,  LOW     );    //SCK
    digitalWriteFast( VPRG, HIGH);
    digitalWriteFast( DCPRG, LOW);
    
    digitalWriteFast( BLANK, LOW);      //Blank falling edge
    //SPI.usingInterrupt(TIMER0_COMPA_vect);
    SPI.begin();
    SPI.beginTransaction(SPISettings(SCLK_FREQ, MSBFIRST, SPI_MODE0));
    pinMode( MISO, INPUT);
    digitalWriteFast( MISO, HIGH);//Internal pullup on MISO
    
    analogWriteFrequency(GCLK, PWM_FREQ); // All PWM pins on FTM0 change
    /* Hello. Be careful with this pwm frequency. It needs to be much higher (4096 x) than the "refresh rate" of the
     LEDs, or else they will be very flickery.
     */
    analogWrite(GCLK, 128);
}



// Writes Dot Correction value to the chip (0xFF)
// Call once after startup
//
void write_dot_correction(uint8_t * buf){
    digitalWriteFast(VPRG, HIGH);
    digitalWriteFast(DCPRG, HIGH);
    
    //SPI.beginTransaction(SPISettings(SCLK_FREQ, MSBFIRST, SPI_MODE0));
    SPI.transfer((uint8_t *)buf, NUM_BYTES);
    //SPI.endTransaction();
    
    digitalWriteFast(XLAT, HIGH);   //XLAT Pulse
    delayMicroseconds(10);
    digitalWriteFast(XLAT, LOW);
    delayMicroseconds(10);
    digitalWriteFast(VPRG, LOW);
}



// Writes Grey Scale buffer to the chip
// Call to update TLC chain
//
void write_grey_scale(uint8_t * buf){
    //analogWrite(GCLK, 0);
    ///digitalWriteFast(BLANK, HIGH);
    ///digitalWriteFast(BLANK, LOW);
    
    //SPI.beginTransaction(SPISettings(SCLK_FREQ, MSBFIRST, SPI_MODE0));
    SPI.transfer((uint8_t *)buf, NUM_BYTES);
    //SPI.endTransaction();
    
    digitalWriteFast(XLAT, HIGH);   //XLAT Pulse
    digitalWriteFast(XLAT, LOW);
    
    digitalWriteFast(BLANK, HIGH);
    digitalWriteFast(BLANK, LOW);
    //digitalWriteFast(BLANK, LOW);
    //analogWrite(GCLK, 128);
}


// Modifies the buffer (buf) such that the TLC channel (chn) will have the indicated value (val)
// 0 <= chn < NUM_CHNL
// 0 <= val < 4096 (12 bits)
// buf is a pointer to the buffer (layer?) you want to modify.
// NOTE: TLC clocks data in MSB first.
void set_channel( uint8_t chn, uint16_t val, uint8_t* buf ){
    chn = NUM_CHNL-chn-1;   //The data is clocked out ch 15 first. Do this so channel numbers match datasheet.
    buf += (chn / 2) * 3; //move pointer up (every 2 channels is 3 full bytes)
    val &= 0x0FFF;        //mask off upper four bits
    
    if( chn % 2 ){  //if channel is odd (write half byte then full byte
        buf[1] &= 0xF0;         //set lower half of split byte to 0
        buf[1] |= (uint8_t)(val >> 8);   //put upper 4 bits of val into target byte
        buf[2] =  (uint8_t)val; //put lower 8 bits of val into target byte
        /*buf[1] &= 0xF0;
        buf[2] = 0;*/
    }
    else{           //if channel is even (write full byte then half byte
        buf[0] = (uint8_t)(val >> 4);  //put upper 8 bits in
        buf[1] &= 0x0F;         //set upper half of split byte to zero
        buf[1] |= (uint8_t)((val & 0x000F) << 4);   //put in lower 4 bits of val into upper half of target byte
    }
}




