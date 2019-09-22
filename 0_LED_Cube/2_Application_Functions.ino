/**************************************************************************
 *
 *
 *
 *  all sub function below, all are self contained 'apps' called within the Main Switch function (must be declared within the two areas up top too.
 *
 *
 *
 **************************************************************************/


void dodgeGame() {

    uint32_t timer0 = millis();
    uint32_t dificultyTimer = millis();
    uint32_t time1 = millis();
    uint8_t ledCount = 3;
    uint8_t key = 0;
    boolean start = false;
    clearCube();
    while (true){

        if (millis() - dificultyTimer > 5000 && start) {

            ledCount++;
            Serial.print(ledCount);
            dificultyTimer += 5000;

        }
        uint16_t delayTime = 150;


    if (key != 7){
        set_led_pk(5, 5, 1, 0xF00);
        set_led_pk(6, 5, 1, 0xF00);
        set_led_pk(5, 6, 1, 0xF00);
        set_led_pk(6, 6, 1, 0xF00);
        set_led_pk(5, 5, 2, 0xF00);
        set_led_pk(6, 5, 2, 0xF00);
        set_led_pk(5, 6, 2, 0xF00);
        set_led_pk(6, 6, 2, 0xF00);


    }

    char c;

    if (keyboard.available()){
        start = true;
        c=keyboard.read();
        Serial.print(c);
        if (c == PS2_ESC) {
            break;
        }
    }

    if (c == PS2_UPARROW){
        for (int i = 0; i < 12; i++){
            moveRow(i, 1, UP, 0xF00, true);
            moveRow(i, 2, UP, 0xF00, true);
            c = '[';
        }
    }
    else if (c == PS2_DOWNARROW){
        for (int i = 0; i < 12; i++){
            moveRow(i, 1, DOWN, 0xF00, true);
            moveRow(i, 2, DOWN, 0xF00, true);
            c = '[';
        }
    }
    else if (c == PS2_LEFTARROW){
        for (int i = 0; i < 12; i++){
            moveRow(1, i, LEFT, 0xF00, true);
            moveRow(2, i, LEFT, 0xF00, true);
            c = '[';
        }
    }
    else if (c == PS2_RIGHTARROW){
        for (int i = 0; i < 12; i++){

            moveRow(10, i, RIGHT, 0xF00, true);
            moveRow(9, i, RIGHT, 0xF00, true);
            c = '[';
        }
    }

        if (start) {
    if (millis() - timer0 > delayTime){
        Serial.print(ledCount);
        setRandomLED(ledCount, BACKWARD, 0xFFF);


        for (int i = 0; i < 12; i++){
            for (int j = 0; j < 12; j++){

                moveRow(i, j, BACKWARD, 0xFFF);
            }

        }
        timer0 += delayTime;
    }
}
        else if (key != 7) {
            setRandomLED(ledCount, BACKWARD, 0xFFF);
            key = 7;
        }
    }
    clearCube();
}

/***************************************************************************
 *
 *      SNAKE GAME BELOW
 *      and all the neccessary functions for it
 *
 ***************************************************************************/

void dropMatch(int score) {
    for (int p = 0; p < 3; p++) {

    for (int k = 0; k < 12; k++) {
        for (int j = 0; j < 12; j++) {
            for (int i = 0; i < 12; i++) {
                if (LEDArray(i, k, j) == 0) {
        set_led_pk(i, j, k, 0xF800);
                }
            }
        }
    }
    d(250);
    clearCube();
        d(250);

    }
    gameOverScore(score);
}
void lightMatch(int score) {
    dropMatch(score);
}
void pourGasoline(int score) {
    lightMatch(score);
}

uint16_t colorShifter(uint16_t currentColor) {
    boolean state = false;
    uint8_t r  = (currentColor & 0xF800) >> 11;
    uint16_t g = (currentColor & 0x07E0) >> 5;
    uint16_t b = (currentColor & 0x001F);
    if (state) {
        if (b != 31) { b++; } else if (r != 63) { r++; } else { state = true; }
    } else {
    if (b != 0) { b--; } else if (r != 0) { r--; } else {state = false;}
    }
    return pk_low(r, g, b);
}

void MoveLED(uint8_t x, uint8_t y, uint8_t z, uint16_t currentColor, boolean gainLength) {
    currentColor = colorShifter(currentColor);

    if (LEDArray(x + 1, y, z) == currentColor) {
        set_led_pk(x, y, z, currentColor);
        MoveLED(x + 1, y, z, currentColor, gainLength);
    }
    else if (LEDArray(x - 1, y, z) == currentColor) {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x - 1, y, z, currentColor, gainLength);

    }
    else if (LEDArray(x, y+1, z) == currentColor) {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x, y + 1, z, currentColor, gainLength);

    }
    else if (LEDArray(x, y-1, z) == currentColor) {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x, y-1, z, currentColor, gainLength);

    }
    else if (LEDArray(x, y, z+1) == currentColor) {
        set_led_pk(x, y, z, currentColor);

        MoveLED(x, y, z+1, currentColor, gainLength);

    }
    else if (LEDArray(x, y, z-1) == currentColor) {
        set_led_pk(x, y, z, currentColor);
        //uses underflow
        if (z-1 < 12) {
            MoveLED(x, y, z-1, currentColor, gainLength);
        }
    }
    else if (gainLength) {
        set_led_pk(x, y, z, currentColor);

    }
  else {
      set_led_pk(x, y, z, 0);
  }

}



void snakeGame() {
#define NUM_FOOD 10
    boolean start = false;
    uint16_t color = 0xFFFF;
    boolean toggle = false;
    uint8_t x = 5;
    uint8_t y = 5;
    uint8_t z = 4;
    uint8_t x2 = 5;
    uint8_t y2 = 3;
    uint8_t z2 = 6;
    uint16_t speed = 500;
    uint16_t length = 4;
    directions direction = FORWARD;
    uint32_t foodTimer = millis();
    uint32_t moveTimer = millis();
    boolean addLength = false;
    coord_t food[NUM_FOOD];
    boolean endGame = false;

    while (true) {
        char c = ']';

        if (keyboard.available()){
            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }

            // so that the snake cannot eat itself prevent motion in the reverse direction
            if (c == PS2_LEFTARROW && direction == RIGHT) {
                c = ']';
            } else if (c == PS2_RIGHTARROW && direction == LEFT) {
                c = ']';
            } else if (c == PS2_DOWNARROW && direction == FORWARD) {
                c = ']';
            } else if (c == PS2_UPARROW && direction == BACKWARD) {
                c = ']';
            } else if ((c == '1' || c == 'r') && direction == DOWN) {
                c = ']';
            } else if ((c == '0' || c == 'f')  && direction == UP) {
                c = ']';
            }
        }

        if (!start) {
            clearCube();
            for (int i = 0; i < 4; i++) {
                set_led_pk(5, 5, 4 - i, color);
                color = colorShifter(color);
            }
            for (int i = 0; i < NUM_FOOD; i++) {
                while (true) {
                food[i].x = rand() % 12;
                food[i].y = rand() % 12;
                food[i].z = rand() % 12;
                    if (LEDArray(food[i].x, food[i].y, food[i].z) == 0) {
                        break;
                    }
                }
            }
            start = true;
        }

        if (millis() - foodTimer > 900) {
            if (toggle) {
                for (int i = 0; i < NUM_FOOD; i++ ) {
                    set_led_pk(food[i].x, food[i].y, food[i].z, 0xF830);
                }
                toggle = !toggle;
            } else {
                for (int i = 0; i < NUM_FOOD; i++ ) {
                    set_led_pk(food[i].x, food[i].y, food[i].z, 0x031F);
                }
                toggle = !toggle;
            }
            foodTimer += 900;
        }

        switch (c) {
            case PS2_LEFTARROW: direction = LEFT; break;
            case PS2_RIGHTARROW: direction = RIGHT; break;
            case '0': direction = DOWN; break;
            case 'f': direction = DOWN; break;
            case 'r': direction = UP; break;
            case '1': direction = UP; break;
            case PS2_DOWNARROW: direction = BACKWARD; break;
            case PS2_UPARROW: direction = FORWARD; break;
            default: break;
        }


        x2 = x;
        y2 = y;
        z2 = z;


        if (millis() - moveTimer > speed && !endGame) {
            if (length >= 7 && speed > 300) {
                speed -= 90;
                length = 0;
            }
            if (!(x == 12 || z == 12 || y == 12)) {
        switch (direction) {
            case FORWARD:
                z++;
                break;
            case BACKWARD:
                z--;
                break;
            case UP:
                y++;
                break;
            case DOWN:
                y--;
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;

            default:
                break;
                    }

                for (int i = 0; i < NUM_FOOD; i++) {
                    if (food[i].x == x && food[i].y == y && food[i].z == z) {
                        while (true) {
                        food[i].x = rand() % 12;
                        food[i].y = rand() % 12;
                        food[i].z = rand() % 12;
                        addLength = true;
                            if (LEDArray(food[i].x, food[i].y, food[i].z) == 0) {
                                length++;
                                break;
                            }
                        }

                    }

                }
                if (LEDArray(x, y, z) != 0 && addLength != true || (x - 1 >= 11 || y - 1 >= 11 || z - 1 >= 11)) {
                    endGame = true;
                    pourGasoline(length - 4);
                } else {
                set_led_pk(x, y, z, 0xFFFF);

        MoveLED(x2, y2, z2, 0xFFFF, addLength);
                addLength = false;
            moveTimer += speed;
                }
            }

        }

    }
#undef NUM_FOOD
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void lightCube() {
    boolean lightUp = true;
    uint32_t timer = millis();
    uint8_t i = 0;
    while (true) {
        char c;

        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;

            }
        }


        if (lightUp){
            if (millis() - timer > 200) {

            for (int l = 0; l < 12; l++){
                for (int j = 0; j < 12; j++){
                    for (int k = 0; k < 12; k++){
                        set_led(l, j, k, i * (255 / 10), i * (0 / 10), i * (255 / 10));

                    }
                }
            }

            if (i == 11){
                lightUp = false;

            }
            else {
            i++;
            }
            timer += 200;
            }
        }
        else {
            if (millis() - timer > 200) {

            for (int l = 0; l < 12; l++){
                for (int j = 0; j < 12; j++){
                    for (int k = 0; k < 12; k++){
                        set_led(l, j, k, i * (255 / 10), i * (0 / 10), i * (255 / 10));
                    }
                }
            }

            if (i == 0){
                lightUp = true;
            }else {
            i--;
            }
            timer += 200;
        }
        }
}
    clearCube();
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void someThing() {
    uint32_t resetTime = millis();
    uint32_t timer = millis();
    while (true) {
        char c;

        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }
        if (millis() - resetTime > 20000) {
            for (int h = 0; h < 12; h++) {
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, DOWN);
                }
            }
                d(60);
            }
            resetTime += 20000;
        }
        if (millis() - timer > 150){
        set_led(rand() % 12, rand() % 12, rand() % 12, rand() % 255, rand() % 255, rand() % 255);
            timer += 150;
        }
        if (c == PS2_BACKSPACE) {
            resetTime = millis();
            uint8_t r = rand() % 2;
            uint8_t g = rand() % 2;
            uint8_t b = rand() % 2;
            if (r + b + g == 0){
                r = 1;
                b = 1;
            }
            for (int i = 1; i < 10; i++){
                for (int l = 0; l < 12; l++){
                    for (int j = 0; j < 12; j++){
                        for (int k = 0; k < 12; k++){
                            set_led(l, j, k, r * i * (255 / 10), g * i * (255 / 10),  b * i * (255 / 10));

                        }
                    }
                }
                d(12); //delay

            }
            for (int i = 9; i >= 0; i--){
                for (int l = 0; l < 12; l++){
                    for (int j = 0; j < 12; j++){
                        for (int k = 0; k < 12; k++){
                            set_led(l, j, k, r * i * (255 / 10), g * i * (255 / 10), b * i * (255 / 10));
                        }
                    }
                }
                d(12); //delay
            }
            c = ']';
        }

        if (c == PS2_UPARROW){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                moveRow(i, j, FORWARD, 1, true);
                c = '[';
            }
        }
        }
        else if (c == PS2_DOWNARROW){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, BACKWARD, 1, true);
                    c = '[';
                }
            }
        }


        else if (c == PS2_LEFTARROW){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, LEFT, 1, true);
                    c = '[';
                }
            }
        }


        else if (c == PS2_RIGHTARROW){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, RIGHT, 1, true);
                    c = '[';
                }
            }
        }
        else if (c == 'h'){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, DOWN, 1, true);
                    c = '[';
                }
            }
        }
        else if (c == 'y'){
            for (int i = 0; i < 12; i++){
                for (int j = 0; j < 12; j++){

                    moveRow(i, j, UP, 1, true);
                    c = '[';
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

void lights() {

    while (true) {
        char c;

        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }

        setPackedPackedLED(rand() % 4096 & 0x0777, 0xFFFF);
        clearCube();
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/
void snow() {

    uint32_t timer = millis();
    while (true) {
        char c;

        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }

    if (millis() - timer > 260) {


    //int color = rand() % 64000;
    int count = 0;



        //delay(260);
    for (int i = 0; i < 12; i++){
        for (int f  = 0; f < 12; f++){
            count = 0;
            for (int g = 0; g < 4; g++){
                if (LEDArray(i, g, f) != 0){
                    count += 1;
                }
                if (count == 4){
                    set_led_pk(i, g, f, 0);
                }

            }
        }
    }

    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 12; j++){
            if (rand() % 25 != 1){
                moveRow(j, i, DOWN, 1, true);
            }
            else {
                moveRow(j, i, DOWN, 1, false);
            }
        }
    }
        int num = rand() % 12;
        int num1 = rand() % 12;
        int num2 = rand() % 12;
        set_led_pk(num, 11, num2, white);
        set_led_pk(num1, 11, num, white);
        set_led_pk(num2, 11, num1, white);
            timer += 260;
        }
    }
    clearCube();
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void drawBall( int x, int y, int z, uint16_t color){
    for(int i=-1; i<=1; i++){
        for(int j=-1; j<=1; j++){
            for(int k=-1; k<=1; k++){
                if( i*j*k == 0 )    //make sure one is zero so the corners don't get drawn
                    set_led_pk(x+i,y+j,z+k, color);
            }
        }
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void pong() {
#define PADDLE_LENGTH 3
#define P1_COLOR 0xFFFF
#define P2_COLOR 0xFFFE
#define BALL_COLOR 0xF81F
#define BALL_REFRESH 200
    boolean start = false;
//    vector_t rise;
//    rise.magnitude = 0;
//    rise.direction = UP;
//    vector_t run;
//    run.magnitude = 0;
//    run.direction = FORWARD;
    directionalFloat_t slope;
    slope.ofRise = DOWN;
    slope.ofRun = LEFT;
    slope.ofZRun = BACKWARD;
    slope.zRun = 1;
    slope.rise = 1;
    slope.run = 1;
    float ballx = 0;
    float bally = 3;
    float ballz = 5;
    coord_t player1;
    player1.x = 11;
    player1.y = 3;
    player1.z = 3;
    coord_t player2;
    player2.x = 0;
    player2.y = 3;
    player2.z = 3;
    coord_t ball;
    ball.x = 6;
    ball.y = 6;
    ball.z = 6;
    uint32_t ballTimer = millis();

    while (true) {
        char c = ']';
        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }
        if (((uint8_t) (ballx + 0.5) != ball.x || (uint8_t) (bally + 0.5) != ball.y || (uint8_t) (ballz + 0.5) != ball.z) || !start) {

        }

        if (!start) {
            start = true;
        }
        // Move the paddles location
        switch (c) {
                //ifs use underflow
            case 's': if (!(player2.y + PADDLE_LENGTH == 11)) { player2.y++; eradicate(P2_COLOR); } break;
            case 'z': if (!(player2.z == 0)) { player2.z--; eradicate(P2_COLOR); } break;
            case 'q': if (!(player2.z + PADDLE_LENGTH == 11)) { player2.z++; eradicate(P2_COLOR); } break;
            case 'a': if (!(player2.y == 0)) { player2.y--; eradicate(P2_COLOR); } break;

            case '5': if (!(player1.y + PADDLE_LENGTH == 11)) { player1.y++; eradicate(P1_COLOR); } break;
            case '3': if (!(player1.z == 0)) { player1.z--; eradicate(P1_COLOR); } break;
            case '9': if (!(player1.z + PADDLE_LENGTH == 11)) { player1.z++; eradicate(P1_COLOR); } break;
            case '6': if (!(player1.y == 0)) { player1.y--; eradicate(P1_COLOR); } break;
        }

//  MOVE THE FLOATED REFERENCE POINT FOR THA BALL
        if (millis() - ballTimer > BALL_REFRESH) {
        switch (slope.ofRise) {
            case FORWARD: ballz += (slope.rise); break;
            case UP: bally += slope.rise; break;
            case BACKWARD: ballz -= slope.rise; break;
            case RIGHT: ballx += slope.rise; break;
            case DOWN: bally -= slope.rise; break;
            case LEFT: ballx -= slope.rise; break;
            }
            switch (slope.ofRun) {
                case FORWARD: ballz += (slope.run); break;
                case UP: bally += slope.run; break;
                case BACKWARD: ballz -= slope.run; break;
                case RIGHT: ballx += slope.run; break;
                case DOWN: bally -= slope.run; break;
                case LEFT: ballx -= slope.run; break;
            }
            switch (slope.ofZRun) {
                case FORWARD: ballz += (slope.zRun); break;
                case UP: bally += slope.zRun; break;
                case BACKWARD: ballz -= slope.zRun; break;
                case RIGHT: ballx += slope.zRun; break;
                case DOWN: bally -= slope.zRun; break;
                case LEFT: ballx -= slope.zRun; break;
            }
            ballTimer += BALL_REFRESH;
            if (ball.x != (uint8_t) (ballx + 0.5) || ball.y != (uint8_t) (bally + 0.5) || ball.z != (uint8_t) (ballz + 0.5)) {
                eradicate(BALL_COLOR);
            }
            ball.x = (uint8_t) (ballx + 0.5);
            ball.y = (uint8_t) (bally + 0.5);
            ball.z = (uint8_t) (ballz + 0.5);
            if (LEDArray(ball.x, ball.y, ball.z) != 0 || ( ball.x != 0 || ball.x != 11)) {

            if (ball.x > 50) {
                ball.x = 0;
            } else if (ball.x > 11) {
                ball.x = 11;
                if (rand() % 2 == 0) {
                }
            }
                if (ball.y > 50) {
                    ball.y = 0;
                } else if (ball.y > 11) {
                    ball.y = 11;
                }
                if (ball.z > 50) {
                    ball.z = 0;
                } else if (ball.z > 11) {
                    ball.z = 11;
                }

            if (ball.x == 0) {
                slope.ofRise = directions((rand() % 2) * 5);
                slope.ofZRun = directions((rand() % 2) * 2 + 1);

                slope.ofRun = RIGHT;
            } else if (ball.x == 11) {
                slope.ofRun = LEFT;
            }
                if (ball.y == 0) {
                    slope.ofRise = UP;
                } else if (ball.y == 11) {
                    slope.ofRise = DOWN;
                }
                if (ball.z == 0) {
                    slope.ofZRun = FORWARD;
                } else if (ball.z == 11) {
                    slope.ofZRun = BACKWARD;
                }


            for (uint8_t i = 3; i > 0; i--) {
                protected_set_led_pk(ball.x - 2 + i, ball.y, ball.z, BALL_COLOR);
                protected_set_led_pk(ball.x, ball.y, ball.z - 2 + i, BALL_COLOR);
                protected_set_led_pk(ball.x, ball.y - 2 + i, ball.z, BALL_COLOR);
            }
            }
        }



        //draw paddles from location
        DrawFigure(player1.x, player1.y + PADDLE_LENGTH / 2, player1.z + PADDLE_LENGTH / 2, player1.x, player1.y + PADDLE_LENGTH - PADDLE_LENGTH / 2, player1.z + PADDLE_LENGTH - PADDLE_LENGTH / 2, P1_COLOR);
        DrawFigure(player2.x, player2.y + PADDLE_LENGTH / 2, player2.z + PADDLE_LENGTH / 2, player2.x, player2.y + PADDLE_LENGTH - PADDLE_LENGTH / 2, player2.z + PADDLE_LENGTH - PADDLE_LENGTH / 2, P2_COLOR);
        DrawFigure(player1.x, player1.y, player1.z, player1.x, player1.y + PADDLE_LENGTH, player1.z + PADDLE_LENGTH, P1_COLOR);
        DrawFigure(player2.x, player2.y, player2.z, player2.x, player2.y + PADDLE_LENGTH, player2.z + PADDLE_LENGTH, P2_COLOR);
    }
    clearCube(); //exit game
#undef P2_COLOR
#undef P1_COLOR
#undef PADDLE_LENGTH
#undef BALL_COLOR
#undef BALL_REFRESH
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void randomColors() {

    while (true) {
        char c;
        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            for (int k = 0; k < 12; k++) {
                set_led_pk(i, j, k, rand() % 65535);
            }
        }
    }
    }
    clearCube();
}
/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void ballBounce() {
#define PADDLE_LENGTH 3
#define P1_COLOR 0xFFFF
#define P2_COLOR 0xFFFE
#define BALL_COLOR 0xF81F
#define BALL_REFRESH 200
    boolean start = false;
    //    vector_t rise;
    //    rise.magnitude = 0;
    //    rise.direction = UP;
    //    vector_t run;
    //    run.magnitude = 0;
    //    run.direction = FORWARD;
    directionalFloat_t slope;
    slope.ofRise = DOWN;
    slope.ofRun = LEFT;
    slope.ofZRun = BACKWARD;
    slope.zRun = 1;
    slope.rise = 1;
    slope.run = 1;
    float ballx = 0;
    float bally = 3;
    float ballz = 5;
    coord_t player1;
    player1.x = 11;
    player1.y = 3;
    player1.z = 3;
    coord_t player2;
    player2.x = 0;
    player2.y = 3;
    player2.z = 3;
    coord_t ball;
    ball.x = 6;
    ball.y = 6;
    ball.z = 6;
    uint32_t ballTimer = millis();


    while (true) {
        char c = ']';
        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }
        if (((uint8_t) (ballx + 0.5) != ball.x || (uint8_t) (bally + 0.5) != ball.y || (uint8_t) (ballz + 0.5) != ball.z) || !start) {

        }


        if (!start) {
            start = true;
        }
        // Move the paddles location
        switch (c) {
                //ifs use underflow
            case 's': if (!(player2.y + PADDLE_LENGTH == 11)) { player2.y++; eradicate(P2_COLOR); } break;
            case 'z': if (!(player2.z == 0)) { player2.z--; eradicate(P2_COLOR); } break;
            case 'q': if (!(player2.z + PADDLE_LENGTH == 11)) { player2.z++; eradicate(P2_COLOR); } break;
            case 'a': if (!(player2.y == 0)) { player2.y--; eradicate(P2_COLOR); } break;

            case '5': if (!(player1.y + PADDLE_LENGTH == 11)) { player1.y++; eradicate(P1_COLOR); } break;
            case '3': if (!(player1.z == 0)) { player1.z--; eradicate(P1_COLOR); } break;
            case '9': if (!(player1.z + PADDLE_LENGTH == 11)) { player1.z++; eradicate(P1_COLOR); } break;
            case '6': if (!(player1.y == 0)) { player1.y--; eradicate(P1_COLOR); } break;
            default:
                break;
        }

        //  MOVE THE FLOATED REFERENCE POINT FOR THA BALL
        if (millis() - ballTimer > BALL_REFRESH) {
            switch (slope.ofRise) {
                case FORWARD: ballz += (slope.rise); break;
                case UP: bally += slope.rise; break;
                case BACKWARD: ballz -= slope.rise; break;
                case RIGHT: ballx += slope.rise; break;
                case DOWN: bally -= slope.rise; break;
                case LEFT: ballx -= slope.rise; break;
            }
            switch (slope.ofRun) {
                case FORWARD: ballz += (slope.run); break;
                case UP: bally += slope.run; break;
                case BACKWARD: ballz -= slope.run; break;
                case RIGHT: ballx += slope.run; break;
                case DOWN: bally -= slope.run; break;
                case LEFT: ballx -= slope.run; break;
            }
            switch (slope.ofZRun) {
                case FORWARD: ballz += (slope.zRun); break;
                case UP: bally += slope.zRun; break;
                case BACKWARD: ballz -= slope.zRun; break;
                case RIGHT: ballx += slope.zRun; break;
                case DOWN: bally -= slope.zRun; break;
                case LEFT: ballx -= slope.zRun; break;
            }
            ballTimer += BALL_REFRESH;
            if (ball.x != (uint8_t) (ballx + 0.5) || ball.y != (uint8_t) (bally + 0.5) || ball.z != (uint8_t) (ballz + 0.5)) {
                eradicate(BALL_COLOR);
            }
            ball.x = (uint8_t) (ballx + 0.5);
            ball.y = (uint8_t) (bally + 0.5);
            ball.z = (uint8_t) (ballz + 0.5);
            if (LEDArray(ball.x, ball.y, ball.z) != 0 || ( ball.x != 0 || ball.x != 11)) {

                if (ball.x > 50) {
                    ball.x = 0;
                } else if (ball.x > 11) {
                    ball.x = 11;
                }
                if (ball.y > 50) {
                    ball.y = 0;
                } else if (ball.y > 11) {
                    ball.y = 11;
                }
                if (ball.z > 50) {
                    ball.z = 0;
                } else if (ball.z > 11) {
                    ball.z = 11;
                }

                if (ball.x == 0) {
                    slope.ofRun = RIGHT;
                } else if (ball.x == 11) {
                    slope.ofRun = LEFT;
                }
                if (ball.y == 0) {
                    slope.ofRise = UP;
                } else if (ball.y == 11) {
                    slope.ofRise = DOWN;
                }
                if (ball.z == 0) {
                    slope.ofZRun = FORWARD;
                } else if (ball.z == 11) {
                    slope.ofZRun = BACKWARD;
                }


                for (uint8_t i = 3; i > 0; i--) {
                    protected_set_led_pk(ball.x - 2 + i, ball.y, ball.z, BALL_COLOR);
                    protected_set_led_pk(ball.x, ball.y, ball.z - 2 + i, BALL_COLOR);
                    protected_set_led_pk(ball.x, ball.y - 2 + i, ball.z, BALL_COLOR);
                }
            }
        }

        //draw paddles from location
        DrawFigure(player1.x, player1.y + PADDLE_LENGTH / 2, player1.z + PADDLE_LENGTH / 2, player1.x, player1.y + PADDLE_LENGTH - PADDLE_LENGTH / 2, player1.z + PADDLE_LENGTH - PADDLE_LENGTH / 2, P1_COLOR);
        DrawFigure(player2.x, player2.y + PADDLE_LENGTH / 2, player2.z + PADDLE_LENGTH / 2, player2.x, player2.y + PADDLE_LENGTH - PADDLE_LENGTH / 2, player2.z + PADDLE_LENGTH - PADDLE_LENGTH / 2, P2_COLOR);
        DrawFigure(player1.x, player1.y, player1.z, player1.x, player1.y + PADDLE_LENGTH, player1.z + PADDLE_LENGTH, P1_COLOR);
        DrawFigure(player2.x, player2.y, player2.z, player2.x, player2.y + PADDLE_LENGTH, player2.z + PADDLE_LENGTH, P2_COLOR);
    }
    clearCube(); //exit game
#undef P2_COLOR
#undef P1_COLOR
#undef PADDLE_LENGTH
#undef BALL_COLOR
#undef BALL_REFRESH
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void bounceBall(int iterations){
    int x_vec = 1;
    int y_vec = 1;
    int z_vec = 1;
    int x = 6;
    int y = 7;
    int z = 1;

    memset((uint16_t *)px_buf, 0x0000, NUM_LEDS * 2);

    for( int q = 0; q< iterations; q++){

        drawBall( x, y, z, 0);

        if(x+x_vec >= 11 || x+x_vec <= 0){
            x += (x_vec = -x_vec);
        }
        else{ x += x_vec; }

        if(y+y_vec >= 11 || y+y_vec <= 0){
            y += (y_vec = -y_vec);
        }
        else{ y += y_vec; }

        if(z+z_vec >= 11 || z+z_vec <= 0){
            z += (z_vec = -z_vec);
        }
        else{ z += z_vec; }

        drawBall(x,y,z, 0xFFFF);
    }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void spiral() {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 12; j++) {
      set_led(j, i, 0, 255, 20*i, 9*i);
      delay(30);
    }
    for (int j = 0; j < 12; j++) {
      set_led(11, i, j, 255, 20*i, 9*i);
      delay(30);
    }
    for (int j = 11; j >= 0; j--) {
      set_led(j, i, 11, 255, 20*i, 9*i);
      delay(30);
    }
    for (int j = 11; j >= 0; j--) {
      set_led(0, i, j, 255, 20*i, 9*i);
      delay(30);
    }
  }
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/

void swirl() {
    boolean start = false;
    clearCube();
    uint32_t timer = millis();
    while (true) {
        char c;

        if (keyboard.available()){
            c=keyboard.read();
            if (c == PS2_ESC) {
                break;
            }
        }
        if (!start) {
        for (int i = 0; i < 12; i++) {
            directionalCubeArray(i, i, 11, FORWARD, true, 0xF000);
            directionalCubeArray(i, i, 11, BACKWARD, true,  0xFF00);
            directionalCubeArray(i, i, 11, LEFT, true, 0xFFFF);
            directionalCubeArray(i, i, 11, RIGHT, true, 0xF00F);

        }

            for (int i = 1; i < 11; i++) {
                directionalCubeArray(i, 11-i, 10, FORWARD, true, 0xF800);
                directionalCubeArray(i, 11-i, 10, BACKWARD, true,  0x0770);
                directionalCubeArray(i, 11-i, 10, LEFT, true, 0x00EF);
                directionalCubeArray(i, 11-i, 10, RIGHT, true, 0xF00F);
            }

            start = true;
        }

        if (millis() - timer > 100) {
            for (int k = 0; k < 12; k++) {
                moveRow(11, k, FORWARD);
                moveRow(11, k, BACKWARD);
               moveRow(11, k, LEFT);
               moveRow(11, k, RIGHT);

            }
            for (int i = 0; i < 4; i++) {
            for (int k = 1; k < 11; k++) {
                moveRow(1, k, directions(i+1), 1, false, 1, 10);
            }
            }


            timer = millis();
        }
    }

    clearCube();
}

/***************************************************************************
 *
 *   Sub Seperator
 *
 ***************************************************************************/


void test() {
    uint32_t timer = millis();
    uint16_t co = 0xFFFF;
    while (true) {
        char c;
        if (keyboard.available()){

            c=keyboard.read();
            if (c == PS2_ESC) {
                 break;
            }
        }
        if (millis() - timer > 50) {
            co = colorShifter(co);
            timer += 50;

            //Serial.println(((0xFFFF & 0xF800))>>8);

        }
        setPackedPackedLED(pk_coord(1, 1, 1), co);

        //DO STUFF HERE

    }
    clearCube();
}

/***************************************************************************
 *
 *
 *  BASIC 'APP' FUNCTION SETUP BELOW
 *
 *
 ***************************************************************************/
/*
 void NAME() {
 while (true) {
    char c;
    if (keyboard.available()){

        c=keyboard.read();
        if (c == PS2_ESC) {
            break;
        }
    }

    //DO STUFF HERE


    }
 clearCube();
 }
*/
