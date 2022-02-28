#include "Pong.h"

// this can be spiced up for extreme Pong, returns true if the ball hit a wall or is past it
bool Pong::calculateNextDirection()
{
    if (x <= 0 || x >= 11)
    {                        // this hit an xWall
        getNextSpeed(xStep); // now you go opposite way
        return true;
    }

    if (y <= 0 || y >= 11)
    {
        getNextSpeed(yStep);
        return true;
    }

    if (z <= 0 || z >= 11)
    {
        getNextSpeed(zStep);
        return true;
    }
    return false;
}

void Pong::getNextSpeed(float &v)
{
    v = ((xStep < 0) - (0 < xStep)) * (millis() % 3);
}

void Pong::moveBallNext()
{
    drawBall(false);
    x = x + xStep; // no checks on where this will land, could be out of bounds
    y = y + yStep;
    z = z + zStep;
    drawBall();
}



void Pong::drawBall(bool draw)
{
    ui8 normalizedX = help::normalize(x);
    ui8 normalizedY = help::normalize(y);
    ui8 normalizedZ = help::normalize(z);

    // loop is wierd so that no repeated LEDs are painted
    for (int i = -1; i < 2; i += 2)
    {
        protected_set_led_pk(normalizedX + i, normalizedY, normalizedZ, draw ? 0x001F : 0x0000);
        protected_set_led_pk(normalizedX, normalizedY + i, normalizedZ, draw ? 0x001F : 0x0000);
        protected_set_led_pk(normalizedX, normalizedY, normalizedZ + i, draw ? 0x001F : 0x0000);
    }
    protected_set_led_pk(normalizedX, normalizedY, normalizedZ, draw ? 0x001F : 0x0000); // for effeciancy not readability
}

void Pong::startRound()
{
    // Display scores
    for (int i = 0; i < 2; i++)
    {
        TypeEngine::drawChar('0' + players[i]->lives, 5, 5, 0, players[i]->wall, 0xFFFF);
    }

    // TODO: possibly improve this? cant really do anything else, but exit which would happen right after this function
    d(scoreDisplayTime);

    // clear those letters
    for (int i = 0; i < 2; i++)
    {
        TypeEngine::drawChar('0' + players[i]->lives, 5, 5, 0, players[i]->wall, 0);
    }

    // Place ball
    drawBall();

    // Draw players
    for (int i = 0; i < 2; i++)
    {
        players[i]->reset(); // reset then draw
        players[i]->drawPaddle();
    }

    // TODO: possibly improve this? cant really do anything else, but exit which would happen right after this function
    d(500);
    getNextSpeed(xStep);
    getNextSpeed(yStep);
    getNextSpeed(zStep);
}

Pong::State Pong::findNextState()
{
    for (int i = 0; i < 2; i++)
    {
        if (players[i]->deservesFailure(help::normalize(x), help::normalize(y), help::normalize(z)))
        {
            //TODO: if four player pong is wanted then restructure this part
            players[i]->lives--;
            if (players[i]->lives == 0)
            {
                players[i]->alive = false;
                return End;
            }
            return Start;
        }
    }
    return Playing;
}

App::Resut Pong::run(uint32_t time, bool timed)
{
    timer = millis();
    uint32_t intervalTimer = 0;            // timer used to delay the ball movement
    const uint16_t ballMoveInterval = 200; // ball movement delays
    // note the use of NEW here
    players = new Player *[2];
    players[0] = new Player(';', '\'', '[', '/', Relativistic::LEFT, startScore); // just 2 players for now
    players[1] = new Player('s', 'a', 'w', 'z', Relativistic::RIGHT, startScore);

    State state = Start;
    while (!timed || millis() - timer < timed)
    {
        if (!characterInput())
        { // remember characterInput is the fuction that sets c and returns if it is not escape
            return App::KEYBOARD_STOP;
        }

        // Allow player movement
        for (int i = 0; i < 2; i++)
        {
            players[i]->keyboardInput(c); // each player handles its paddles movement
        }

        // state machine
        switch (state)
        {
        case Start:
            startRound();
            intervalTimer = millis(); // reset the ball timer so we dont get super sonic balls, thats just not good for anyone
            state = Playing;
            break;
        case Playing:
            if (millis() - intervalTimer > ballMoveInterval)
            {
                moveBallNext();
                state = calculateNextDirection() ? HitWall : Playing; // this line will change direction on a hitwall
            }
            break;
        case HitWall:
            state = findNextState();
            break;
        case End:
            state = Playing; // for now we just keep playing, but the other player is dead
            break;
        }
    }

    // clean up players since they are dynamically allocated
    for (int i = 0; i < 2; i++)
    {
        delete players[i];
    }
    delete[] players;
    return App::STOP;
}

//-----------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- Player Below -----------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------

Pong::Player::Player(char iup, char idown, char ileft, char iright, Relativistic::Directions iwall, ui8 startScore)
    : upChar(iup), downChar(idown), leftChar(ileft), rightChar(iright), wall(iwall)
{
    lives = startScore;
}

//Assume coordinates have been help::normalized, do not pass by referance here
bool Pong::Player::deservesFailure(ui8 ballX, ui8 ballY, ui8 ballZ)
{
    if (!alive)
    { // if your already dead, you cant desearve failure
        return false;
    }
    Relativistic::toRelative(ballX, ballY, ballZ, wall); // flip the coordinates
    const ui8 length = 11 - maxX;
    const ui8 height = 11 - maxY;
    return (!(ballX >= x && ballX <= x + length - 1) || !(ballY >= y && ballY <= y + height - 1)) && (ballZ == 0);
}

// just resets the paddle to a middle-ish position
void Pong::Player::reset()
{
    x = 4;
    y = 4;
}

void Pong::Player::drawPaddle(const bool &clear)
{
    if (!alive)
    {
        return; // no draw paddle if dead
    }
    const ui8 length = 12 - maxX;
    const ui8 height = 12 - maxY;

    for (int i = x; i < x + length; i++)
    {
        Relativistic::directionalCubeArray(i, y, 0, wall, true, clear == false ? color : 0);
        Relativistic::directionalCubeArray(i, y + height - 1, 0, wall, true, clear == false ? color : 0);
    }
    for (int i = y; i < y + height; i++)
    {
        Relativistic::directionalCubeArray(x, i, 0, wall, true, clear == false ? color : 0);
        Relativistic::directionalCubeArray(x + length - 1, i, 0, wall, true, clear == false ? color : 0);
    }
}

void Pong::Player::keyboardInput(char &c)
{
    if (!alive)
    { // nothing can be done at all if your dead
        return;
    }
    if (upChar == c || downChar == c || leftChar == c || rightChar == c)
    {
        drawPaddle(true); // assume we will have to redraw
        if (c == upChar)
        {
            if (y != maxY)
                y++;
        }
        else if (c == downChar)
        {
            if (y != 0)
                y--;
        }
        else if (c == leftChar)
        {
            if (x != 0)
                x--;
        }
        else if (c == rightChar)
        {
            if (x != maxX)
                x++;
        }
    }
    drawPaddle();
}
