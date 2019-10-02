//
// File			MUX_lib.h
//
// Details		This is a header file for the multiplexing functionality
//
// Author		William Lies
//
// Date			04/03/18 9:58 AM
//
// Copyright	(c) William Lies, 2017
//
#ifndef MUX_lib_h
#define MUX_lib_h

/*------------------------------------------------------
 *  NOTES
 -----------------------------------------------------*/
//

/*------------------------------------------------------
 *  Automatic Includes
 -----------------------------------------------------*/
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


/*------------------------------------------------------
 *  User Includes
 -----------------------------------------------------*/
#include "IntervalTimer.h"

/*------------------------------------------------------
 *  Types
 -----------------------------------------------------*/


/*------------------------------------------------------
 *  Literal Constants
 -----------------------------------------------------*/
#define P_Q_0       5           //Quarter Selects (ARM Port D)
#define P_Q_1       6
#define P_Q_2       7
#define P_Q_3       8
#define P_L_0       19          //Layer Selects (ARM Port B)
#define P_L_1       0
#define P_L_2       1
#define P_C_R       16          //Color Selects (ARM Port B)
#define P_C_G       17
#define P_C_B       18

#define NUM_P_Q 4
#define NUM_P_L 3
#define NUM_P_C 3

#define NUM_LEDS        (12*12*12)      //Number of LEDs in the cube
#define NUM_LEDS_LYR    (12*12)         //Number of LEDs in a layer
#define NUM_LEDS_DIM    (12)            //Number of LEDs in a dimension

/*------------------------------------------------------
 *  Function Prototypes
 -----------------------------------------------------*/

void mux_init();

void mux_begin();

void mux_isr();


uint16_t extract_color( uint16_t bits, uint8_t color );



#endif /* MUX_lib_h */
