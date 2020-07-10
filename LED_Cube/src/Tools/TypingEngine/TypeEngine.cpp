#include "TypeEngine.h"
#include "../../LED_Cube_library/Helpful_Functions.h"
#include "../../LED_Cube_library/Basic_Functions.h"

uint8_t TypeEngine::upperCharCount = 0;
uint8_t TypeEngine::lowerCharCount = 0;
uint8_t TypeEngine::lowerHeight = 0;
uint8_t TypeEngine::upperHeight = 6;


uint8_t TypeEngine::getFontIndex(char c)
{
    if (c < 58 && c > 47)
    { // this is a number for sure
        return c - 48 + (26 /* to pass the letters */); 
    }
    if (c < 91 && c > 64)
    { // capital letter
        return c - 65;
    }
    if (c > 96 && c < 123)
    { // lower case letter
        return c - 97;
    }
    return 36; // assume any other char is just the empty letter (a space)
}

uint8_t TypeEngine::getUpperCharCount() {
    return upperCharCount;
}

uint8_t TypeEngine::getLowerCharCount() {
    return upperCharCount;
}

void TypeEngine::resetCharCountLower() {
    lowerCharCount = 0;
}

void TypeEngine::resetCharCountUpper() {
    upperCharCount = 0;
}

//gets direction based on char positions (four letters per side of cube)
Relativistic::Directions TypeEngine::getDirection(uint8_t charPosition) {
    if (charPosition < charsPerSide) {
        return Relativistic::FORWARD;
    }
    if (charPosition < charsPerSide * 2) {
        return Relativistic::LEFT;
    }
    if (charPosition < charsPerSide * 3) {
        return Relativistic::BACKWARD;
    }
    if (charPosition < charsPerSide * 4) {
        return Relativistic::RIGHT;
    }
    return (getDirection(charPosition - charsPerSide * 4)); // just loop back recursively for ease; Should never happen though
}

// draws a char c at the coordinates in the direction of the viewPoint with the color
void TypeEngine::drawChar(char c, int x1, int y1, int z1, Relativistic::Directions viewpoint, uint16_t color)
{
    uint16_t letter = font[getFontIndex(c)];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            bool on = letter & 0x8000; // get the last bit
            letter = letter << 1;      // shift to the left to get the next bit
            // if (font[getFontIndex(c)][i * 5 + j])
            Relativistic::directionalCubeArray(x1 + i, y1 + j, z1, viewpoint, true, on ? color : 0x0000);
        }
    }
}

// type chars on the bottom in an organized manner
void TypeEngine::typeLower(char c, uint16_t color) {
    lowerCharCount = lowerCharCount % 16; // makes the thing loop back over itself (protects from any mumber above 16, works with underflow)
    if (c == PS2_BACKSPACE) {
        lowerCharCount--;
        lowerChars[lowerCharCount] = '\0';
        type('\0', lowerCharCount, color, true);
        return;
    }
    type(c, lowerCharCount, color, true);
    lowerChars[lowerCharCount] = c;
    lowerCharCount++;
}

void TypeEngine::typeUpper(char c, uint16_t color) {
    upperCharCount = upperCharCount % 16; // makes the thing loop back over itself (protects from any mumber above 16, works with underflow)
    if (c == PS2_BACKSPACE) {
        upperCharCount--;
        upperChars[upperCharCount] = '\0';
        type('\0', upperCharCount, color, false);
        return;
    }
    type(c, upperCharCount, color, false);
    upperChars[upperCharCount] = c;
    upperCharCount++;
}

void TypeEngine::clearLayer (bool lower) {
    for (int i = 0; i < charsPerSide * 4; ++i) {
        type('\0', i, 0x0000, lower); // bassically type nothing in all the places to clear
    }
}

void TypeEngine::autoTypeUpper(String str, uint16_t color1, uint16_t color2, bool clear) {
    if (clear) {
        clearLayer(false);
        upperCharCount = 0;
    }
    for (ui8 i = 0; i < str.length(); i++) {
        typeUpper(str.charAt(i), i % 2 == 0 ? color1 : color2);
    }
}
void TypeEngine::autoTypeLower(String str, uint16_t color1, uint16_t color2, bool clear) {
    if (clear) {
        clearLayer(true);
        lowerCharCount = 0;
    }
    for (ui8 i = 0; i < str.length(); i++) {
        typeLower(str.charAt(i), i % 2 == 0 ? color1 : color2);
    }
}

void TypeEngine::type(char c, uint8_t position, uint16_t color, bool lower)
{
    Relativistic::Directions direction = getDirection(position);
    uint8_t x = (position % 4) * charWidth;
    uint8_t y = lower == true ? lowerHeight : upperHeight;
    drawChar(c, x, y, 0, direction, color);
}

// char arrays are just empty to start 
char TypeEngine::upperChars[16] = {0};
char TypeEngine::lowerChars[16] = {0};

// this is a font listed in bits
uint16_t TypeEngine::font[37] = {
        0b0101011111011010, // this is a
        0b1101011101011100, // this is b
        0b0111001001000110, // this is c
        0b1101011011011100, // this is d
        0b1111001101001110, // this is e
        0b1111001101001000, // this is f
        0b0101001011010100, // this is g
        0b1011011111011010, // this is h
        0b1110100100101110, // this is i
        0b0010010011010100, // this is j
        0b1011101101101010, // this is k
        0b1001001001001110, // this is l
        0b1011111111011010, // this is m
        0b1011111111111010, // this is n
        0b0101011011010100, // this is o
        0b1101011101001000, // this is p
        0b0101011011100110, // this is q
        0b1101011101011010, // this is r
        0b0111000100011100, // this is s
        0b1110100100100100, // this is t
        0b1011011011010100, // this is u
        0b1011011010000100, // this is v
        0b1011011111111010, // this is w
        0b1011010101011010, // this is x
        0b1011010100100100, // this is y
        0b1110010101001110, // this is z
        0b1110010101001110, // this is 1
        0b1100011110011100, // this is 2
        0b1011011110010010, // this is 3
        0b1111000100011100, // this is 4
        0b0101001101010100, // this is 5
        0b1110010010010010, // this is 6
        0b1111010101011110, // this is 7
        0b1111010110010010, // this is 8
        0b1111011011011110, // this is 9
        0b0000000000000000, // this is
};