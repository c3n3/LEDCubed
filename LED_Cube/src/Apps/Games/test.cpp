// void snakeGame() {
// #define NUM_FOOD 10
//     boolean start = false;
//     uint16_t color = 0xFFFF;
//     boolean toggle = false;
//     uint8_t x = 5;
//     uint8_t y = 5;
//     uint8_t z = 4;
//     uint8_t x2 = 5;
//     uint8_t y2 = 3;
//     uint8_t z2 = 6;
//     uint16_t speed = 500;
//     uint16_t length = 4;
//     directions direction = FORWARD;
//     uint32_t foodTimer = millis();
//     uint32_t moveTimer = millis();
//     boolean addLength = false;
//     coord_t food[NUM_FOOD];
//     boolean endGame = false;

//     while (true) {
//         char c = ']';

//         if (keyboard.available()){
//             c=keyboard.read();
//             if (c == PS2_ESC) {
//                 break;
//             }

//             // so that the snake cannot eat itself prevent motion in the reverse direction
//             if (c == PS2_LEFTARROW && direction == RIGHT) {
//                 c = ']';
//             } else if (c == PS2_RIGHTARROW && direction == LEFT) {
//                 c = ']';
//             } else if (c == PS2_DOWNARROW && direction == FORWARD) {
//                 c = ']';
//             } else if (c == PS2_UPARROW && direction == BACKWARD) {
//                 c = ']';
//             } else if ((c == '1' || c == 'r') && direction == DOWN) {
//                 c = ']';
//             } else if ((c == '0' || c == 'f')  && direction == UP) {
//                 c = ']';
//             }
//         }

//         if (!start) {
//             clearCube();
//             for (int i = 0; i < 4; i++) {
//                 set_led_pk(5, 5, 4 - i, color);
//                 color = colorShifter(color);
//             }
//             for (int i = 0; i < NUM_FOOD; i++) {
//                 while (true) {
//                 food[i].x = rand() % 12;
//                 food[i].y = rand() % 12;
//                 food[i].z = rand() % 12;
//                     if (LEDArray(food[i].x, food[i].y, food[i].z) == 0) {
//                         break;
//                     }
//                 }
//             }
//             start = true;
//         }

//         if (millis() - foodTimer > 900) {
//             if (toggle) {
//                 for (int i = 0; i < NUM_FOOD; i++ ) {
//                     set_led_pk(food[i].x, food[i].y, food[i].z, 0xF830);
//                 }
//                 toggle = !toggle;
//             } else {
//                 for (int i = 0; i < NUM_FOOD; i++ ) {
//                     set_led_pk(food[i].x, food[i].y, food[i].z, 0x031F);
//                 }
//                 toggle = !toggle;
//             }
//             foodTimer += 900;
//         }

//         switch (c) {
//             case PS2_LEFTARROW: direction = LEFT; break;
//             case PS2_RIGHTARROW: direction = RIGHT; break;
//             case '0': direction = DOWN; break;
//             case 'f': direction = DOWN; break;
//             case 'r': direction = UP; break;
//             case '1': direction = UP; break;
//             case PS2_DOWNARROW: direction = BACKWARD; break;
//             case PS2_UPARROW: direction = FORWARD; break;
//             default: break;
//         }


//         x2 = x;
//         y2 = y;
//         z2 = z;


//         if (millis() - moveTimer > speed && !endGame) {
//             if (length >= 7 && speed > 300) {
//                 speed -= 90;
//                 length = 0;
//             }
//             if (!(x == 12 || z == 12 || y == 12)) {
//         switch (direction) {
//             case FORWARD:
//                 z++;
//                 break;
//             case BACKWARD:
//                 z--;
//                 break;
//             case UP:
//                 y++;
//                 break;
//             case DOWN:
//                 y--;
//                 break;
//             case LEFT:
//                 x--;
//                 break;
//             case RIGHT:
//                 x++;
//                 break;

//             default:
//                 break;
//                     }

//                 for (int i = 0; i < NUM_FOOD; i++) {
//                     if (food[i].x == x && food[i].y == y && food[i].z == z) {
//                         while (true) {
//                         food[i].x = rand() % 12;
//                         food[i].y = rand() % 12;
//                         food[i].z = rand() % 12;
//                         addLength = true;
//                             if (LEDArray(food[i].x, food[i].y, food[i].z) == 0) {
//                                 length++;
//                                 break;
//                             }
//                         }

//                     }

//                 }
//                 if (LEDArray(x, y, z) != 0 && addLength != true || (x - 1 >= 11 || y - 1 >= 11 || z - 1 >= 11)) {
//                     endGame = true;
//                     pourGasoline(length - 4);
//                 } else {
//                 set_led_pk(x, y, z, 0xFFFF);

//         MoveLED(x2, y2, z2, 0xFFFF, addLength);
//                 addLength = false;
//             moveTimer += speed;
//                 }
//             }

//         }

//     }
// #undef NUM_FOOD
// }