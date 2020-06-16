#pragma once
#include "../Tools/ParticleSystem/Particle.h"

/**
 * @brief This is a firework subclass that is used to specify an effect generation function, along with other parameters
 * 
 */
struct FireWorkEffect {

    /**
     * @brief Construct a new Fire Work Effect object
     * 
     * @param drawEffect this is the Draw burst function, you must create a function that draws whatever effect you want base on position, color and intervals
     * @param maxIntervals this is the maximum intervals the firework effect lives for
     * @param intervalTime this is the interval time ie how often the effect function gets executed in milliseconds
     */
    FireWorkEffect(void (*drawEffect)(ui8 x, ui8 y, ui8 z, Color& color, int interval), ui8 maxIntervals, uint16_t inter);

    // this is the draw burst function from above
    void (*drawEffect)(ui8 x, ui8 y, ui8 z, Color& color, int interval);

    // max intervals effect lasts
    ui8 maxIntevals;

    // time it takes for one interval to run
    uint16_t intervalTime;
};


/**
 * @brief This is a firework that is used hopefully just like a normal firework
 * 
 */
class Firework
{
private:
    Particle rocket;
    Color color;
    FireWorkEffect effect;
    uint32_t timer;
    bool effectStage = false;
    ui8 interval;
    uint32_t fuseLength;
    bool runRocket();
    bool runEffect();
public:

    // run this function continuously so the fire work can work (ie -> while (firework.fireAway()); )
    // returns false when the fire work has died; true otherwise
    bool fireAway();

    // used to 'reload' the firework ie bassically create a new firework object without actually creating a new one
    void reload(Particle r, uint32_t fuse, Color burstColor, FireWorkEffect f);    

    /**
     * @brief Construct a new Firework object
     * 
     * @param rocket this is the Particle that represents the moving rocket
     * @param fuseLength the time the rocket stage lasts for
     * @param effect the fireworks effect (bassically what happens when it blows up)
     * @param burstColor the color of the firework effect, does not need to be utilized
     */
    Firework(Particle rocket, uint32_t fuseLength, FireWorkEffect effect, Color burstColor = 0xFFFF);
};