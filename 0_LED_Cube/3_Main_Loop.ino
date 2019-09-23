/**************************************************************************
 *                                                                        *
 * ************************************************************************
 *                                                                        *
 *  Main Switch Function below                                            * ***************************
 *                                                                        *
 * ************************************************************************
 *                                                                        *
 **************************************************************************/

void mainSwitch(mainStates state) {
    int i = 0;
    uint8_t stateSwitch = 0;
    uint32_t backgroundTimer = millis();
    while(true) {

        if (millis() - backgroundTimer > 200) {

           // setRandomLED(3, DOWN, 0xFFFF);
            for (uint8_t j = 0; j < 12; j++) {
            for (uint8_t i = 0; i < 12; i++) {
             //   moveRow(i, j, DOWN);
            }
            backgroundTimer += 200;
        }
        }

        char c;
        if (keyboard.available()) {
            c = keyboard.read();
            clearCube();
            //i = c - '0';
        }

        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 12; j++) {
                for (int k = 0; k < 6; k++) {
                    set_led_pk(i, j, k + 6, 0);
                }
            }
        }

    switch (state) {
            //int y;
        case TOP:

            if (c == PS2_RIGHTARROW) {

                stateSwitch = shifter(stateSwitch, RIGHT, TOP);
            }
            if (c == PS2_LEFTARROW) {

                stateSwitch = shifter(stateSwitch, LEFT, TOP);

            }
            else if (c == PS2_ENTER) {
                state = mainStates(stateSwitch);
                i=0;
                break;
            }
            //y=0;
            drawChar(stateSwitch + 1, 5, 5, 0, FORWARD, 0xF0F0);
            drawChar(stateSwitch + 1, 5, 5, 1, FORWARD, 0xF0F0);

            break;

        case ANIMATIONS:

            if (c == PS2_ESC) {
                state = TOP;
                break;

            }

            else if (c == PS2_LEFTARROW) {
                i = shifter(i, LEFT, ANIMATIONS);

            }
            else if (c == PS2_RIGHTARROW) {
                i = shifter(i, RIGHT, ANIMATIONS);

            }

            else if (c == PS2_ENTER){
                appFunctions[0][i]();
            }
            drawChar(i + 1, 5, 5, 0, FORWARD, 0xFFFF);
            drawChar(i + 1, 5, 5, 1, FORWARD, 0xFFFF);

            break;

        case GAMES:

            if (c == PS2_ESC) {
                state = TOP;
                break;
            }

            else if (c == PS2_LEFTARROW) {
                i = shifter(i, LEFT, GAMES);
            }
            else if (c == PS2_RIGHTARROW) {
                i = shifter(i, RIGHT, GAMES);
            }

            else if (c == PS2_ENTER){
            appFunctions[2][i]();
            }
            drawChar(i + 1, 5, 5, 0, FORWARD, 0xFFFF);
            drawChar(i + 1, 5, 5, 1, FORWARD, 0xFFFF);

            break;

            case INTERACTIVEANIMATIONS:

            if (c == PS2_ESC) {
                state = TOP;
                break;
            }

            else if (c == PS2_LEFTARROW) {
                i = shifter(i, LEFT, INTERACTIVEANIMATIONS);
            }
            else if (c == PS2_RIGHTARROW) {
                i = shifter(i, RIGHT, INTERACTIVEANIMATIONS);
            }

            else if (c == PS2_ENTER){
                appFunctions[1][i]();
            }
            drawChar(i + 1, 5, 5, 0, FORWARD, 0xFFFF);
            drawChar(i + 1, 5, 5, 1, FORWARD, 0xFFFF);

            break;

    }
        c = ']';

}
}

/**************************************************************************
 *
 *
 *
 *  The loop call
 *
 *
 *
 **************************************************************************/



void loop()
{
    mainSwitch(TOP);

} //end loop
