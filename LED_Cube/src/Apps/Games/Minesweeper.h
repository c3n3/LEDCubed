#pragma once
#include "../../../src/LED_Cube_library/Basic_Functions.h"
#include "../../../src/LED_Cube_library/Helpful_Functions.h"
#include "../../Tools/MathObjects/Vector.h"
#include "../../Tools/Color/Color.h"
#include "../App.h"
#include "../../Tools/TypingEngine/TypeEngine.h"

class Minesweeper: public App
{
private:
    Vector<uint8_t> self;
    int MINE_COUNT = 50;
    bool blink = true;
    uint16_t* bank;
    Vector<ui8>* mines;
public:
    bool lost = false;
    bool win = false;
    uint16_t empty = 0x0000; // this is empty
    uint16_t full = 0xFFFF; // white is full
    uint16_t mine = 0xF800; // red is a mine
    void drawCursor(bool clear = false) {
        bool p = (blink && !clear);
        if (p) {
            printBank();
            blink = !blink;
            return;
        }
        for (int x = 0; x < CUBE_LENGTH; x++) {
            set_led_pk(x, self.y, self.z, '+');
        }
        for (int y = 0; y < CUBE_LENGTH; y++) {
            set_led_pk(self.x, y, self.z, '+');
        }
        blink = !blink;
    }

    void drawMines() {
        for (int i = 0; i < MINE_COUNT; i++) {
            set_led_pk(mines[i].x, mines[i].y, mines[i].z, mine);
        }
    }

    bool checkWin() {
        for (int i = 0; i < CUBE_LENGTH; i++) {
            for (int j = 0; j < CUBE_LENGTH; j++) {
                for (int k = 0; k < CUBE_LENGTH; k++) {
                    if (LEDArray(i, j, k) == full) {
                        if (!isMine(i, j, k)) return false;
                    }
                }
            }
        }
        return true;
    }

    // make the mines be more blue with the more mines surrounding it
    uint32_t handleMineCount(int count) {
        Color col = 0xFFFF; // start at white
        col.gReal(col.gReal() - count); 
        col.rReal(col.rReal() - count);
        return c;
    }

    void handleEnter(ui8 x, ui8 y, ui8 z) {
        char p = LEDArray(x, y, z);
        if (p != full) {
            return; // do nothing to nothing
        }
        int total = mineInProximity(x, y, z);
        if (!total) {
            protected_set_led_pk(x, y, z, empty);
            for (ui8 i = x - 1; i < x + 2; i++) {
                for (ui8 j = y - 1; j < y + 2; j++) {
                handleEnter(i, j, z + 1); // top
                }
            }
            for (ui8 i = x - 1; i < x + 2; i++) {
                for (ui8 j = y - 1; j < y + 2; j++) {
                handleEnter(i, j, z - 1); // bottom
                }
            }
            for (ui8 i = x - 1; i < x + 2; i++) {
                for (ui8 j = y - 1; j < y + 2; j++) {
                    if (i == x && j == y) {
                        continue;
                    }
                    handleEnter(i, j, z - 1); // bottom
                }
            }
            return;
        }
        protected_set_led_pk(x, y, z, handleMineCount(total));
    }

    int mineInProximity(ui8 x, ui8 y, ui8 z = 0) {
        int count = 0;
        for (int i = 0; i < MINE_COUNT; i++) {
            if (
                mines[i].x >= x - 1 && mines[i].x <= x + 1
                && mines[i].y >= y - 1 && mines[i].y <= y + 1
                && mines[i].z >= z - 1 && mines[i].z <= z + 1
            ) {
                count++;
            }
        }
        return count;
    }

    void takeChar(char c) {
        drawCursor(true);
        switch (c) {
            case PS2_UPARROW:
            if (self.y != CUBE_LENGTH - 1) {
                printBank();
                self.y++;
                saveBank();
            }
            break;
            case PS2_RIGHTARROW:
            if (self.x != CUBE_LENGTH - 1) {
                printBank();
                self.x++;
                saveBank();
            }
            break;
            case PS2_DOWNARROW:
            if (self.y != 0) {
                printBank();
                self.y--;
                saveBank();
            }
            break;
            case PS2_LEFTARROW:
            if (self.x != 0) {
                printBank();
                self.x--;  
                saveBank();
            } 
            break;
            case '0':
            if (self.x != 0) {
                printBank();
                self.z--;  
                saveBank();
            } 
            break;
            case '1':
            if (self.x != 0) {
                printBank();
                self.z++;  
                saveBank();
            } 
            break;
            case PS2_ENTER:
            if (isMine(self.x, self.y, self.z)) {
                // std::cout << "\n\n\n\n\n\n YOU HAVE LOST\n";
                lost = true;
            }
            printBank();
            handleEnter(self.x, self.y, self.z);
            saveBank();
            break;
            case 'c':
            if (checkWin()) {
                // std::cout << "\n\nYOU HAVE WON\n";
                win = true;
            }
        }
    }

    bool isMine(ui8 x, ui8 y, ui8 z = 0) {
        for (int i = 0; i < MINE_COUNT; i++) {
            if (
                mines[i].x == x &&
                mines[i].y == y &&
                mines[i].z == z
            ) {
                return true;
            }
        }
        return false;
    }

    void saveBank() {
        for (int i = 0; i < CUBE_LENGTH; i++) {
            bank[i] = LEDArray(i, self.y, self.z);
        }
        for (int i = 0; i < CUBE_LENGTH; i++) {
            bank[i + CUBE_LENGTH] = LEDArray(self.x, i, self.z);
        }
        for (int i = 0; i < CUBE_LENGTH; i++) {
            bank[i + CUBE_LENGTH * 2] = LEDArray(self.x, i, self.z);
        }
    }

    void printBank() {
        for (ui8 i = 0; i < CUBE_LENGTH; i++) {
            protected_set_led_pk(i, self.y, self.z, bank[i]);
        }
        for (ui8 i = 0; i < CUBE_LENGTH; i++) {
            protected_set_led_pk(self.x, i, self.z, bank[i + CUBE_LENGTH]);
        }
        for (ui8 i = 0; i < CUBE_LENGTH; i++) {
            protected_set_led_pk(self.x, self.y, i, bank[i + CUBE_LENGTH * 2]);
        }
    }

    App::Resut init(/* args */) {
        for (int i = 0; i < MINE_COUNT; i++) {
            mines[i] = Vector<ui8>(rand() % CUBE_LENGTH, rand() % CUBE_LENGTH, 0);
        }
        // mines[0] =  Point(1,1);
        // mines[1] =  Point(1,0);
        // mines[2] =  Point(1,2);
        bank = new uint16_t[CUBE_LENGTH * 3];
        saveBank();
        bool cont = characterInput();
        while (c != PS2_ENTER) {
            if (!cont) {
                return App::KEYBOARD_STOP;
            }

            if (c == PS2_LEFTARROW) {
                MINE_COUNT -= 5;
            }
            if (c == PS2_RIGHTARROW) {
                MINE_COUNT += 5;
            }
            int print = MINE_COUNT;
            char str[4];
            for (int i = 0; i < 4; i++) {
                str[i] = '0' + (print % 10);
                print = print / 10;
            }


            TypeEngine::autoTypeUpper(str, 0x07E0, 0xF800);

            cont = characterInput();
        }
        return App::CONTINUE;
    };

    App::Resut frame() {
        if (win) {
            TypeEngine::autoTypeUpper("win", 0x001F, 0xF800);
        }
        else if (!lost) {
            if (millis() - timer > 150) {
                drawCursor();
                timer += 150;
            }
            takeChar(c);
        }
        else {
            drawMines();
        }
        return App::CONTINUE;
    }
    void end() {
        delete bank;
    };
};