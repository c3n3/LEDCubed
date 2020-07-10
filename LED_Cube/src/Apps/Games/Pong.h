#pragma once
#include "../../../src/LED_Cube_library/Basic_Functions.h"
#include "../../../src/LED_Cube_library/Helpful_Functions.h"
#include "../App.h"
#include "../../Tools/TypingEngine/TypeEngine.h"
#include "../../Tools/RelativeCoordinates/Relativistic.h"
class Pong : public App
{
private:
    enum State
    {
        Start,
        Playing,
        HitWall,
        End,
    };
    const ui8 startScore = 5; // we play bassically like golf so that maybe......... we could have four pong players at once
    const int scoreDisplayTime = 1500;
    class Player;
    Player** players;
    float x, y, z;             // this is all relative points
    float zStep, yStep, xStep; // bassically like rise and run, but 3D style
    void drawBall(bool draw = true);
    void getNextSpeed(float& v);
    void moveBallNext();
    bool calculateNextDirection();
    State findNextState();
    void startRound();
    bool ballAtWall();
public:
    // decided to overide the run function for this one
    void run(uint32_t time = 0, bool timed = false);
    String title = "Pong";
};


class Pong::Player
{
private:
    // the maximum points for any paddle
    static const ui8 maxX = 8; // these also define the size of the paddle via 12 - maxX = length;
    static const ui8 maxY = 8;
    const uint16_t color = 0xFFFF;
    const char upChar;
    const char downChar;
    const char leftChar;
    const char rightChar;
    ui8 x, y;   // the location of the paddle player

public:
    bool alive; // is the player alive
    void drawPaddle(const bool& clear = false);
    bool deservesFailure(ui8 x, ui8 y, ui8 z);
    void reset();
    const Relativistic::Directions wall;
    ui8 lives; // because we count down score we have 'lives'
    void keyboardInput(char &c);
    Player(char, char, char, char, Relativistic::Directions, const ui8);
};
