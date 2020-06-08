#ifndef TYPEDEF_H
#define TYPEDEF_H
#if defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE
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

#endif