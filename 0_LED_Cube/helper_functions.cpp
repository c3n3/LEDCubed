#include "helper_functions.h"

/**************************************************************************
 *
 *
 *
 *  Functions to aid animations/games below
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

/***************************************************************************
 *

 *
 ***************************************************************************/

// will not destroy the program if you set a nonexistant LED
void protected_set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c){
    if (!(x > 11 || y > 11 || z > 11)) {
    px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y]  = c;
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

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

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//packs a rgb color into one number
uint16_t pk_color(uint16_t r, uint16_t g, uint16_t b) {
    return ((r & 0x00F8) << 8 ) |
    ((g & 0x00FC) << 3 ) |
    ((b & 0x00F8) >> 3 );
}


/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

// red goes up to 31
//blue to 31
//green up to 63
uint16_t pk_low(uint16_t r, uint16_t g, uint16_t b) { //gives color values an increment of one
    return ((r & 0x001F) << 11 ) |
    ((g & 0x003F) << 5 ) |
    ((b & 0x001F));
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

// a packed coordinate
uint16_t pk_coord(uint8_t x, uint8_t y, uint8_t z) {
    return (((z << 4) | y) << 4) | x;
}


/***************************************************************************
 *
 *   Shifter Function used by the main switch to display the current state
 *
 ***************************************************************************/

uint8_t shifter(uint8_t k, directions more, mainStates state) {
    uint8_t amount = 3; //for the top level
    if (state == GAMES) {
        amount = GAMEAMOUNT;
    }
    else if (state == ANIMATIONS) {
        amount = ANIMATIONAMOUNT;
    }
    else if (state == INTERACTIVEANIMATIONS) {

        amount = INTERACTIVEANIMATIONSAMOUNT;
    }

    if (more == RIGHT) {
        if (k == amount - 1) {
            k = 0;
        }
        else {
            k++;

        }
    }
    else if (more == LEFT){
        if (k == 0) {
            k = amount - 1;
        }
        else {
            k--;

        }
    }
    return k;
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//self explainatory
void clearCube(){
    memset((uint16_t *)px_buf, 0x0000, NUM_LEDS * 2);
}

//void adressToCoordinate

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//houses the data for the whole cube (wrapper function for the px_buf array )
uint16_t LEDArray(uint8_t x, uint8_t y, uint8_t z){
    if (!(z > 11 || x > 11|| y > 11)) {
    return px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y];
    }
    else {
        return 0;
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//Set led with packed color value
void set_led_pk( uint8_t x, uint8_t y, uint8_t z, uint16_t c){
    px_buf[ z * NUM_LEDS_LYR + NUM_LEDS_DIM * x + y] = c;
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//Set led with packed color value by address
void setAddressLED( uint16_t address, uint16_t c){
    px_buf[address] = c;
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

// set led by packed coordinates and packed color
void setPackedPackedLED(uint16_t coord, uint16_t c) {
    //set_led_pk((coord & 0x000F), (coord & 0x00F0), (coord & 0x0F00), c);
    px_buf[ ((coord & 0x0F00) >> 8) * NUM_LEDS_LYR + NUM_LEDS_DIM * (coord & 0x000F) + ((coord & 0x00F0) >> 4)] = c;
}


/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//this function switches which orientation you may look at the cube,
// very very useful function, allows writting other helper functions in terms of a direction so that you dont have to have 6 types of the same function for each direction
// the  coordinates go as follows, the face you look at for each direction, the reletive 'z' coordinate is the third one, the reletive 'x' is either the true z or x direction, and the second coordinate is always the reletive 'y'
uint16_t directionalCubeArray(uint8_t firstCord, uint8_t secondCord, uint8_t thirdCord, directions direction, boolean setLED = false, uint16_t color = 0){


    if (setLED){
        switch (direction) { //you can set leds
            case UP:
                set_led_pk(firstCord, thirdCord, secondCord, color);
                break;
            case FORWARD:
                set_led_pk(firstCord, secondCord, thirdCord, color);
                break;
            case LEFT:
                set_led_pk(11 - thirdCord, secondCord, firstCord, color);
                break;
            case BACKWARD:
                set_led_pk(11 - firstCord, secondCord, 11 - thirdCord, color);
                break;
            case RIGHT:
                set_led_pk(thirdCord, secondCord, 11 - firstCord, color);
                break;
            case DOWN:
                set_led_pk(firstCord, 11 - thirdCord, secondCord, color);
                break;

            default:
                break;
        }
        return 0;
    }
    else {
        switch (direction) {//or you can call the array for the cube, it returns the value
            case UP:
                return LEDArray(firstCord, thirdCord, secondCord);
                break;
            case FORWARD:
                return LEDArray(firstCord, secondCord, thirdCord);
                break;
            case LEFT:
                return LEDArray(11 - thirdCord, secondCord, firstCord);
                break;
            case BACKWARD:
                return LEDArray(11 - firstCord, secondCord, 11 - thirdCord);
                break;
            case RIGHT:
                return LEDArray(thirdCord, secondCord, 11 - firstCord);
                break;
            case DOWN:
                return LEDArray(firstCord, 11 - thirdCord, secondCord);
                break;

            default:
                break;
        }
    }


}

/***************************************************************************
 *
 *   Unfinished Function below
 *
 ***************************************************************************/

void rotate(uint16_t t) {
    uint32_t timer  = millis();
    uint32_t R0Time = millis();
    uint32_t R1Time = millis();
    uint32_t R2Time = millis();
    uint32_t R3Time = millis();
    uint32_t R4Time = millis();
    uint32_t R5Time = millis();

    while (millis() - timer < t) {

    }

}

/***************************************************************************
 *
 *   Move Row function, (This is a big function I know, It is very useful to compensate, also should be rewritten with recursion for possibly better performance)
 *   firstCoord and secondCoord determine which row will be shifted in accordance with the specified viewPoint
 *   viewPoint determines which plane will be looked at for the two coordinates to shift there row
 *   specificColor tells it which color it should shift in the cube default is 1, this will shift all colors
 *   collective determines whether this function is allowed to 'push' a lit LED off the cube or not
 *   start is at which index the function will start shifting, Default 0 for the beginning of any row
 *   end is the index the function will stop
 *   color will change the color of any shifted led, Default 1 will not change the color of shifted leds
 *
 ***************************************************************************/

void moveRow(uint8_t firstCoord, uint8_t secondCoord,  directions viewPoint,  uint16_t specificColor = 1, boolean collective = false, uint8_t start = 0, uint8_t end = 11, uint16_t color = 1){
    if (!collective && end == 11){
        directionalCubeArray(firstCoord, secondCoord, 11, viewPoint, true);
    }
    for (int i = 10 - (11 - end); i >= 0 + start; i--) {
        if (specificColor == 1) {
            if (directionalCubeArray(firstCoord, secondCoord, i, viewPoint) != 0){
                if (collective){
                    if (directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint) == 0){
                        if (color == 1){
                            directionalCubeArray(firstCoord, secondCoord, i + 1,  viewPoint, true, directionalCubeArray(firstCoord, secondCoord, i, viewPoint));
                        }
                        else {
                            directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true, color);
                        }
                        directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                    }

                }
                else {

                    if (color == 1){
                        directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, directionalCubeArray(firstCoord, secondCoord, i, viewPoint));
                    }
                    else {
                        directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, color);
                    }
                    directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                }
            }
        }
        else {
            if (directionalCubeArray(firstCoord, secondCoord, i, viewPoint) != 0 && directionalCubeArray(firstCoord, secondCoord, i, viewPoint) == specificColor){
                if (collective){
                    if (directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint) != specificColor){
                        if (color == 1){
                            directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, directionalCubeArray(firstCoord, secondCoord, i, viewPoint, false));
                        }
                        else {
                            directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true, color);
                        }
                        directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);
                    }

                }
                else {

                    if (color == 1){
                        directionalCubeArray(firstCoord, secondCoord, i + 1,  viewPoint, true, directionalCubeArray(firstCoord, secondCoord, i, viewPoint));
                    }
                    else {
                        directionalCubeArray(firstCoord, secondCoord, i + 1, viewPoint, true, color);
                    }
                    directionalCubeArray(firstCoord, secondCoord, i, viewPoint, true);

                }
            }
        }
    }

}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void eradicate(uint16_t color) {
    for (uint8_t i = 0; i < 12; i++) {
        for (uint8_t j = 0; j < 12; j++) {
            for (uint8_t k = 0; k < 12; k++) {
                if (LEDArray(i, j, k) == color) {
                    set_led(i, j, k, 0, 0, 0);
                }
            }
        }
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void setRandomLED(uint8_t leds, directions direction, uint16_t color, boolean threeD = false) {
    if (!threeD) {
    for (uint8_t i = 0; i < leds; i++) {
        directionalCubeArray(rand() % 12, rand() % 12, 0, direction, true, color);
    }
    }
}
/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

//no up or down yet
void angledMove(uint8_t rise, uint8_t run, directions direction, uint16_t color) {
    //rise
    for (uint8_t k = 0; k < rise; k++) {
        for (uint8_t i = 0; i < 12; i++) {
            for (uint8_t j = 0; j < 12; j++) {
                moveRow(i, j, UP, color);
            }
        }
    }
    //rise
    for (uint8_t k = 0; k < run; k++) {
        for (uint8_t i = 0; i < 12; i++) {
            for (uint8_t j = 0; j < 12; j++) {
                moveRow(i, j, direction, color);
            }
        }
    }
}

 /***************************************************************************
  *
  *   Font Functions
  *
  ***************************************************************************/

 // input a char or number and get the index in the font array for that item
uint8_t getFontIndex(char c) {
  switch (c) {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    case 'D': return 3;
    case 'E': return 4;
    case 'F': return 5;
    case 'G': return 6;
    case 'H': return 7;
    case 'I': return 8;
    case 'J': return 9;
    case 'K': return 10;
    case 'L': return 11;
    case 'M': return 12;
    case 'N': return 13;
    case 'O': return 14;
    case 'P': return 15;
    case 'Q': return 16;
    case 'R': return 17;
    case 'S': return 18;
    case 'T': return 19;
    case 'U': return 20;
    case 'V': return 21;
    case 'W': return 22;
    case 'X': return 23;
    case 'Y': return 24;
    case 'Z': return 25;
    case 1: return 26;
    case 2: return 27;
    case 3: return 28;
    case 4: return 29;
    case 5: return 30;
    case 6: return 31;
    case 7: return 32;
    case 8: return 33;
    case 9: return 34;
    case 0: return 35;
    case PS2_BACKSPACE: return 36;
  }
}

// draws a char c at the coordinates in the direction of the viewPoint with the color
void drawChar(char c, int x1, int y1, int z1, directions viewpoint, uint16_t color) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 5; j++) {
        if (font[getFontIndex(c)][i*5 + j]) {
          directionalCubeArray(x1 + i, y1 + j, z1, viewpoint, true, color);
        }
      }
    }
}

// funciton to let continuous typing of characters on the cube, (it wraps chars around as space fills up)
void typeChars(char c){
  directions direction = FORWARD;
  uint8_t xPosition = charCount % 4;
  uint8_t yPosition = 7;
  uint16_t color = 0xFFFF;
  if (charCount % 2) {
    color = 0x00FF;
  }
  if (charCount > 20) {
    yPosition = 0;
  }
  if ((charCount <= 8 && 4 < charCount) || charCount > 20) {
    direction = LEFT;
  } else if (charCount <= 12) {
    direction = BACKWARD;
  }  else if (charCount <= 16) {
    direction = RIGHT;
  } else if (charCount <= 24) {
    direction = FORWARD;
  }
  if (c == PS2_BACKSPACE) {
    charCount--;
  } else {
    charCount++;
  }
  drawChar(c, xPosition, yPosition, 0, direction, color);
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

// draws a box based on the 6 coordinates (Two Points in the cube) and the color (This thing definitley needs rewritting)
void DrawFigure(int x1, int y1, int z1, int x2, int y2, int z2, uint16_t color) {
    int xDist = abs(x1 - x2);
    int yDist = abs(y1 - y2);
    int zDist = abs(z1 - z2);
    if (x1 > x2){ //created in order to make the 'for' loops always accurate
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y1 > y2){ // created in order to make the 'for' loop always accurate
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }
    if (z1 > z2) { // created in order to make the 'for' loop always accurate
        int temp = z1;
        z1 = z2;
        z2 = temp;
    }
    if (xDist == 0) { // if the x coordinates are the same, the shape will be a square will a constant x value
        for (int i = y1; i <= y2; i++){
            set_led_pk(x1,i,z1,color);
            //delay(200);
            set_led_pk(x1,i,z2,color);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++) {
            set_led_pk(x1,y1,i,color);
            //delay_pk(200);
            set_led_pk(x1,y2,i,color);
            //delay(200);
        }
    }
    else if (yDist == 0) { // if the y coordinates are the same, the shape will be a square will a constant y value
        for (int i = x1; i <= x2; i++){
            set_led_pk(i,y1,z1,color);
            //delay_pk(200);
            set_led_pk(i,y1,z2,color);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++) {
            set_led_pk(x1,y1,i,color);
            //delay_pk(200);
            set_led_pk(x2,y1,i,color);
            //delay(200);
        }
    }
    else if (zDist == 0) { // if the z coordinates are the same, the shape will be a square will a constant z value
        for (int i = x1; i <= x2; i++){
            set_led_pk(i,y1,z1,color);
            //delay_pk(200);
            set_led_pk(i,y2,z1,color);
            //delay(200);
        }
        for (int i = y1; i <= y2; i++) {
            set_led_pk(x1,i,z1,color);
            //delay+pk(200);
            set_led_pk(x2,i,z1,color);
            //delay(200);
        }
    }
    else { // if none of the x/y/z coordinates match the other points' x/y/z, then the shape will be a cube.
        for (int i = x1; i <= x2; i++){
            set_led_pk(i,y1,z1,color);
            //delay_pk(200);
            set_led_pk(i,y2,z1,color);
            //delay_pk(200);
            set_led_pk(i,y1,z2,color);
            //delay_pk(200);
            set_led_pk(i,y2,z2,color);
            //delay(200);
        }
        for (int i = y1; i <= y2; i++){
            set_led_pk(x1,i,z1,color);
            //delay_pk(200);
            set_led_pk(x2,i,z1,color);
            //delay_pk(200);
            set_led_pk(x1,i,z2,color);
            //delay_pk(200);
            set_led_pk(x2,i,z2,color);
            //delay(200);
        }
        for (int i = z1; i <= z2; i++){
            set_led_pk(x1,y1,i,color);
            //delay_pk(200);
            set_led_pk(x1,y2,i,color);
            //delay_pk(200);
            set_led_pk(x2,y1,i,color);
            //delay_pk(200);
            set_led_pk(x2,y2,i,color);
            //delay(200);
        }
    }
}

/***************************************************************************
 *
 *   Special helper function to be used to display scores of a game
 *
 ***************************************************************************/


void gameOverScore(int score) {
    uint32_t timer = millis();
    boolean started = false;
    while (true) {
        char c;

        if (keyboard.available()) {

            c = keyboard.read();
            if (c == PS2_ESC) {
                break;

            }
        }

        if (!started) {
        for (int i = 0; i < strlen(score); i++) {
            typeChars(String(score)[i]);
        }
        started = true;
        }
        if (millis() - timer > 500) {
            for (int k = 0; k < 12; k++) {
                moveRow(11, k, FORWARD);
                moveRow(11, k, BACKWARD);
                moveRow(11, k, LEFT);
                moveRow(11, k, RIGHT);

            }
            for (int i = 0; i < 4; i++) {
                for (int k = 1; k < 11; k++) {
                    moveRow(1, k, directions(i + 1), 1, false, 1, 10);
                }
            }


            timer = millis();
        }
    }
}
