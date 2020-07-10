#ifndef TYPE_ENGINE
#define TYPE_ENGINE
#include "../../LED_Cube_library/globals.h"
#include "../../LED_Cube_library/types.h"
#include "../../Tools/RelativeCoordinates/Relativistic.h"
#include "Arduino.h"

/**
 * @brief This is a static typing engine solution that you can use to print text to the cube
 * @c future changes: try to impliment this to where we do not have the arbitrary upper line, and lower line. But rather possibly a sub object that defines lines
 */
class TypeEngine
{
private:

    // how many chars are on the upper line
    static uint8_t upperCharCount;

    // how many chars are on the lower line
    static uint8_t lowerCharCount;

    // how many chars can ocupy one side of the cube
    static const uint8_t charsPerSide = 4; // how many characters can fit on a cube side

    // the LED width of a character
    static const uint8_t charWidth = 3; 

    // an array holding the upper line
    static char upperChars[16];

    // characters on the lower line
    static char lowerChars[16];

    // this is a helpful function that gets the direction of the next character
    static Relativistic::Directions getDirection(uint8_t);

    // this is a basic function that types a character to the cube
    static void type(char, uint8_t, uint16_t, bool);

    // clears a layer of the TypeEngine
    static void clearLayer(bool lower);

public:
    /**
     * @brief Construct a new Type Engine object; JK you cannot use this constructor to even make a TypeEngine, it is fully static
     * 
     */
    TypeEngine() = delete;

    // the font that is used to draw chars 
    static uint16_t font[37];

    // the bottom of the letter hieght for the upper string of chars
    static uint8_t upperHeight;

    // the same but for the bottom string of chars
    static uint8_t lowerHeight;

    // gets the index of the char for the font
    static uint8_t getFontIndex(char c);

    // draws a char c at the coordinates in the direction of the viewPoint with the color
    static void drawChar(char c, int x1, int y1, int z1, Relativistic::Directions viewpoint, uint16_t color);

    // Types chars on the top that scroll across the cubes outside
    static void typeUpper(char c, uint16_t color);

    //types chars on the bottom that scroll across the cubes outside
    static void typeLower(char c, uint16_t color);

    // types a string across the top of the cube with alternating colors
    static void autoTypeUpper(String str, uint16_t col1, uint16_t col2, bool clear = true);

    // types a string across the bottom of the cube with alternation colors
    static void autoTypeLower(String str, uint16_t col1, uint16_t col2, bool clear = true);

    // gets the upper char count
    static uint8_t getUpperCharCount();

    // gets the lower char count
    static uint8_t getLowerCharCount();

    // just resets the char count for upper line, does not clear
    static void resetCharCountUpper();

    // just resets the char count for lower line, does not clear
    static void resetCharCountLower();
};
#endif