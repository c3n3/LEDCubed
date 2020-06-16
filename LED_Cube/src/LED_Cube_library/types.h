#ifndef TYPE
#define TYPE
/**
 * @brief This file must be killed and banish from existance. it is evil in 75 ways and that is a good enough argument
 * 
 */

// this should really be spit into a RelativeCoord Class but I used it too much like this so I need to not be lazy to do that
enum directions {UP, FORWARD, LEFT, BACKWARD, RIGHT, DOWN};

// this is the pinicle of laziness 
typedef uint8_t ui8; // I really hated typing that (esspecially the _t0)

// um........... dont use this, just make your own or use Vector
typedef struct{
    uint8_t x;
    uint8_t y;
    uint8_t z;
} coord_t;
#endif