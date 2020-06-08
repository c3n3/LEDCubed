//
// File			TLC_lib.h
//
// Details		This is a header file for the TLC_lib
//
// Author		William Lies
//
// Date			10/21/17 9:58 AM
//
// Copyright	(c) William Lies, 2017
//
//

#ifndef TLC_lib_h
#define TLC_lib_h

/*------------------------------------------------------
 *  NOTES
 -----------------------------------------------------*/
//  It takes about .19 ms to write 9 chips of data (measured on scope)
//  The TLC only does 1 PWM count per data write. Update the chip near the TLC's PWM frequency (PWM_FREQ * 4096)

/*------------------------------------------------------
 *  Automatic Includes
 -----------------------------------------------------*/
#if defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE


/*------------------------------------------------------
 *  User Includes
 -----------------------------------------------------*/


/*------------------------------------------------------
 *  Types
 -----------------------------------------------------*/


/*------------------------------------------------------
 *  Literal Constants
 -----------------------------------------------------*/
//      MOSI        11          //MOSI (defined by envrionment)
//      SCK         13          //SCK  (defined by environment)
#define XLAT        10          //Data Latch
#define GCLK        9           //MUST be PWM capable pin
#define BLANK       2           //Output enable
#define VPRG        4           //Mode select
#define DCPRG       3           //Dot Correction Program //THIS SIGNAL MAY BE WIRED HIGH IF YOU'RE RUNNING OUT OF PINS.
#define SCLK_FREQ   12000000    //12 MHz SPI clock (max for Teensy LC)
#define PWM_FREQ    12000000    //PWM Frequency (GS Clock)



#define NUM_CHIPS   9           //Number of chips in the daisy-chain
#define NUM_BYTES   (NUM_CHIPS * 16 * 12 / 8)
                                //<DO NOT EDIT> Number of bytes required in buffer
#define NUM_CHNL    (NUM_CHIPS * 16)    
                                //<DO NOT EDIT> There are 16 channels per chip

/*------------------------------------------------------
 *  Funciton Prototypes
 -----------------------------------------------------*/
void init_TLC();

void write_dot_correction(uint8_t * buf);

void write_grey_scale(uint8_t * buf);

void set_channel( uint8_t chn, uint16_t val, uint8_t* buf );


#endif // TLC_lib_h
