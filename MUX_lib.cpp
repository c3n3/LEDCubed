//
// MUX_lib.cpp
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
//


/*------------------------------------------------------
 *  Automatic Includes
 -----------------------------------------------------*/

/*------------------------------------------------------
 *  User Includes
 -----------------------------------------------------*/
#include "MUX_lib.h"
#include "TLC_lib.h"
/*------------------------------------------------------
 * Constants
 -----------------------------------------------------*/
enum{
    VAL_R = 0,
    VAL_G = 1,
    VAL_B = 2
};

/*------------------------------------------------------
 * Variables
 -----------------------------------------------------*/
extern volatile uint8_t     gs_buf[NUM_BYTES];   //Declared in the main .ino
extern volatile uint16_t    px_buf[NUM_LEDS];

IntervalTimer per_int;          //Object to set up periodic timer interrupt

volatile uint8_t    cur_q;      //Tracks what quarter we're on
volatile uint8_t    cur_l;      //Tracks what physical layer we're on
volatile uint8_t    cur_c;      //Tracks what color layer we're on
volatile uint8_t    next_q;      //next quarter (for pre-loading of gs_buf)
volatile uint8_t    next_l;      //next layer (for pre-loading of gs_buf)
volatile uint8_t    next_c;      //next color (for pre-loading of gs_buf)
static const uint8_t pins_q[NUM_P_Q] = { P_Q_0, P_Q_1, P_Q_2, P_Q_3 };
static const uint8_t pins_l[NUM_P_L] = { P_L_0, P_L_1, P_L_2 };
static const uint8_t pins_c[NUM_P_C] = { P_C_R, P_C_G, P_C_B };


/*------------------------------------------------------
 *  Funciton Definitions
 -----------------------------------------------------*/

//Initializes all the pins and variables used for multiplexing
void mux_init(){

    
    pinMode(P_Q_0, OUTPUT);
    pinMode(P_Q_1, OUTPUT);
    pinMode(P_Q_2, OUTPUT);
    pinMode(P_Q_3, OUTPUT);
    pinMode(P_L_0, OUTPUT);
    pinMode(P_L_1, OUTPUT);
    pinMode(P_L_2, OUTPUT);
    pinMode(P_C_R, OUTPUT);
    pinMode(P_C_G, OUTPUT);
    pinMode(P_C_B, OUTPUT);
    
    digitalWriteFast(P_Q_0, LOW);
    digitalWriteFast(P_Q_1, LOW);
    digitalWriteFast(P_Q_2, LOW);
    digitalWriteFast(P_Q_3, LOW);
    digitalWriteFast(P_L_0, LOW);
    digitalWriteFast(P_L_1, LOW);
    digitalWriteFast(P_L_2, LOW);
    digitalWriteFast(P_C_R, LOW);
    digitalWriteFast(P_C_G, LOW);
    digitalWriteFast(P_C_B, LOW);
    
    cur_q = 0;
    cur_l = 0;
    cur_c = 0;
    next_q = 0;
    next_l = 0;
    next_c = 0;
}


//Starts the timer interrupt for multiplexing
void mux_begin(){
    //Start timer interrupt
    per_int.priority(0xFF);
    per_int.begin(mux_isr, 500); //4096 cycles at 12 MHz is 342us.
}



//Multiplexing Interrupt Service Routine (ISR)
//This function is called periodically via the timer interrupt.
//This function switches the multiplexing FETs and writes data to the TLCs.
//First, the values for the next layer are computed, then they are all written at once (at CHANGE ACTIVE LAYER)
//This approach avoids turning off the leds while we wait for data transfers and such.
void mux_isr(){
interrupts();

    
    //find next quarter, layer, and color
    next_c = cur_c + 1;
    if( next_c >= NUM_P_C ){
        next_c = 0;
        next_l = cur_l + 1;
        if( next_l >= NUM_P_L ){
            next_l = 0;
            next_q = cur_q + 1;
            if( next_q >= NUM_P_Q ){
                next_q = 0;
            }
        }
    }
    
    //Transfer data from the pixel buffer to the grayscale buffer
    int led_idx_ofs = NUM_LEDS_LYR * ((int)next_q * NUM_P_L + (int)next_l);   //LED index offset
    for(int i=0; i<NUM_LEDS_LYR; i++){                                  //Iterate through each LED in the layer
        set_channel(    i,  //set the ith channel of the 144 available channels
                        //find the color value for the ith LED in the current layer
                        extract_color( px_buf[led_idx_ofs + i], next_c ),
                        (uint8_t*)gs_buf );
    }
    
    
    
    /* CHANGE ACTIVE LAYER */       //Please excuse the unorthodox formatting.
                           digitalWriteFast( pins_c[cur_c], LOW );      //Turn off all the current FET pins
    if( cur_l != next_l ){ digitalWriteFast( pins_l[cur_l], LOW ); }
    digitalWriteFast( pins_q[cur_q], LOW );
    
    if( cur_l != next_l ){ digitalWriteFast( pins_l[next_l], HIGH ); } //Turn on the next FET pins
                           digitalWriteFast( pins_c[next_c], HIGH );

    write_grey_scale((uint8_t*)gs_buf);         //Write the grayscale buffer
    
    digitalWriteFast( pins_q[next_q], HIGH );
    
    
    cur_l = next_l;     //update the current counters
    cur_q = next_q;
    cur_c = next_c;

    
}


//Extracts a "12-bit" (0-4096) color value from a 16-bit number packed (RRRR RGGG GGGB BBBB)
uint16_t extract_color( uint16_t bits, uint8_t color ){
    switch( color ){
        case VAL_R:
            if( (bits & 0xF800) == 0 ){ return 0; } //return 0 if it's all 0
            return ( bits | 0x07FF )>>4; //return R value with ones at end
            break;
        case VAL_G:
            if( (bits & 0x07E0) == 0 ){ return 0; }
            return ( (bits << 5) | 0x03FF )>>4;
            break;
        default: //VAL_B
            if( (bits & 0x001F) == 0 ){ return 0; }
            return ( (bits << 11) | 0x07FF )>>4;
    }
}
