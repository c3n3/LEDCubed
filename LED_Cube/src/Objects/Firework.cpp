#include "Firework.h"


FireWorkEffect::FireWorkEffect(void (*DE)(ui8 x, ui8 y, ui8 z, Color& color, int intervalTime), ui8 maxI, uint16_t inter): drawEffect(DE), maxIntevals(maxI), intervalTime(intervalTime) {}

// --------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------

Firework::Firework(Particle rocket, uint32_t fuseLength, FireWorkEffect effect, Color burstColor) : effect(effect), rocket(rocket), fuseLength(fuseLength), color(burstColor) {
    timer = millis();
}

// so that you dont have to make a new object every time 
void Firework::reload(Particle r, uint32_t fuse, Color burstColor, FireWorkEffect f) {
    rocket = r;
    fuseLength = fuse;
    color = burstColor;
    effect = f;
    effectStage = false;
    timer = millis();
    interval = 0; 
}

bool Firework::runRocket() {
    if (millis() - timer > fuseLength) {
        effectStage = true;    
        timer = millis() - effect.intervalTime; // set timer so it resets, but also runs effect instantly
    } else {
        rocket.drawSelf(0);
        rocket.updatePosition(); // always update rocket until the fuse blows
        rocket.drawSelf();
    }
}

bool Firework::runEffect() {
    if (millis() - timer > effect.intervalTime && interval != effect.maxIntevals) {
        (*effect.drawEffect)(rocket.point.x, rocket.point.y, rocket.point.z, color, interval); 
        interval++;
        timer = millis();
        return true;
    }
    Color o = Color(0);
    (*effect.drawEffect)(rocket.point.x, rocket.point.y, rocket.point.z, o, interval - 1); 
    return false;
}

bool Firework::fireAway() {
    if (!effectStage) {
        return runRocket();
    } else {
        return runEffect();
    }
}