#pragma once
#include "../../LED_Cube_library/Basic_Functions.h"
#include "../../LED_Cube_library/Helpful_Functions.h"
#include "../MathObjects/Vector.h"
#include "Arduino.h"
#include "./../../LED_Cube_library/types.h"
#include "../Color/Color.h"

/**
 * @brief This is a particle that has position, acceleration, velocity, and color; Also contains various 'effects' (what happens when the particle hits a wall)
 * 
 */
class Particle
{
private:
    const float resolution; // (milliseconds per update) for the particle's 'physics' engine
    Color color;
    void thatOnePhysicsEquation();
    void handleWallHit(float&,float&,float&,uint32_t&,float&);
    uint32_t timeStartX;
    uint32_t timeStartY;
    uint32_t timeStartZ;
    uint32_t timer; // timer for use when 
public:
    // this is useful so you can reasign a particle
    Particle& operator = (const Particle&);

    // the current point of the particle
    Vector point;
    
    // the origin of the point
    Vector origin;

    // the initialSpeed in LEDs per second
    Vector velocity; 
    
    // LEDs per second per second
    Vector acceleration;
    
    // A useful enum for defining what happens when the particle reaches a wall
    enum WallEffects {
        STICK,
        BOUNCE,
        PASS_THROUGH,
        SLIDE,
    };

    // determines what happens when a particle hits a wall
    WallEffects effect;

    // when working with particles, call this function as much as possible so that the particles can update their position
    void updatePosition(); 

    /**
     * @brief Construct a new Particle object
     * 
     * @param point the start point of the object
     * @param velocity the starting velocity of the particle
     * @param acceleration the acceleration of the particle
     * @param resolution the 'resolution' of the particle meaning how often the particle gets its position updated
     * @param effect the WallEffect that determines what happens when the particle hits a wall
     * @param color the color of the particle 
     */
    Particle(Vector point, Vector velocity, Vector acceleration, uint16_t resolution, WallEffects effect, Color color = 0xFFFF);

    // this draws the particle with a given color
    void drawSelf(const uint16_t& color);

    // this draws the particle with the internal color
    void drawSelf();
};