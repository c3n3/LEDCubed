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
directions TypeEngine::getDirection(uint8_t charPosition) {
    if (charPosition < charsPerSide) {
        return FORWARD;
    }
    if (charPosition < charsPerSide * 2) {
        return LEFT;
    }
    if (charPosition < charsPerSide * 3) {
        return BACKWARD;
    }
    if (charPosition < charsPerSide * 4) {
        return RIGHT;
    }
    return (getDirection(charPosition - charsPerSide * 4)); // just loop back recursively for ease; Should never happen though
}

// draws a char c at the coordinates in the direction of the viewPoint with the color
void TypeEngine::drawChar(char c, int x1, int y1, int z1, directions viewpoint, uint16_t color)
{
    uint16_t letter = font[getFontIndex(c)];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            bool on = letter & 0x8000; // get the last bit
            letter = letter << 1;      // shift to the left to get the next bit
            // if (font[getFontIndex(c)][i * 5 + j])
            help::directionalCubeArray(x1 + i, y1 + j, z1, viewpoint, true, on ? color : 0x0000);
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
    directions direction = getDirection(position);
    uint8_t x = (position % 4) * charWidth;
    uint8_t y = lower == true ? lowerHeight : upperHeight;
    drawChar(c, x, y, 0, direction, color);
}

// char arrays are just empty to start 
char TypeEngine::upperChars[16] = {0};
char TypeEngine::lowerChars[16] = {0};

// this is a font listed in bits
uint16_t TypeEngine::font[37] = {
    //A
    0b1111000101111100,
    //B
    0b1111110101010100,
    //C
    0b0111010001100010,
    //D
    0b1111110001011100,
    //E
    0b1111110101100010,
    //F
    0b1111100101000010,
    //G
    0b0111010001011000,
    //H
    0b1111100100111110,
    //I
    0b1000111111100010,
    //J
    0b0100010000011110,
    //k
    0b1111101110100010,
    //L
    0b1111110000100000,
    //M
    0b1111100110111110,
    //N
    0b1111101110111110,
    //O
    0b0111010001011100,
    //P
    0b1111100101000100,
    //Q
    0b0111011001101100,
    //R
    0b1111100101110100,
    //S
    0b1001010101010010,
    //T
    0b0000111111000010,
    //U
    0b0111110000011110,
    //V
    0b0011110000001110,
    //W
    0b1111101100111110,
    //X
    0b1101100100110110,
    //Y
    0b0001111100000110,
    //Z
    0b1100110101100110,
    //1
    0b1001011111100000,
    //2
    0b1100110101100110,
    //3
    0b1010110101011100,
    //4
    0b0011100100111110,
    //5
    0b1001110101010010,
    //6
    0b0111010101010000,
    //7
    0b0000100001111110,
    //8
    0b1101110101110110,
    //9
    0b0001100101111110,
    //0,
    0b1111110001111110,
    //
    0b0000000000000000,
};