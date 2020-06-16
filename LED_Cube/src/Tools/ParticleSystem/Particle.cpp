#include "Particle.h"
void Particle::handleWallHit(float& x, float& v, float& a) {

    // these equations for more precision could be made to calculate intersect point, but that seems too expensive
    if (x > 11 || x < 0) {
        x = (11 > x) * 11; // make either one or 11 (could do above ^^^^)
        if (effect == STICK) {
            velocity.set(0,0,0);
            acceleration.set(0,0,0);
        }
        else if (effect == BOUNCE) {
            // velocity = the change in time * acceleration * 
            v = -(a * (timer - timeStart) * 0.001); // perfectly elastic equation?
            timeStart = timer; // new tragectory new time start
        }
        else if (effect == SLIDE) {
            v = 0;
            a = 0;
        } // if it is a phase through type, just do nothing
    }
};

Particle& Particle::operator=(const Particle& other) {
    color = other.color;
    point = other.point;
    acceleration = other.acceleration;
    velocity = other.velocity;
    effect = other.effect;
    timeStart = other.timeStart;
}

void Particle::updatePosition() {
    // use equations x = x0 + v * t + 1/2 * a * t^2, where t = time passed = timer - timeStart
    if (millis() - timer > resolution) {
        point.x = point.x + velocity.x * (timer - timeStart) * 0.001 + 0.5 * acceleration.x * (timer - timeStart) * (timer - timeStart) * 0.001 * 0.001;
        point.y = point.y + velocity.y * (timer - timeStart) * 0.001 + 0.5 * acceleration.y * (timer - timeStart) * (timer - timeStart) * 0.001 * 0.001;
        point.x = point.z + velocity.z * (timer - timeStart) * 0.001 + 0.5 * acceleration.z * (timer - timeStart) * (timer - timeStart) * 0.001 * 0.001;
        timer += resolution;

        // handle a bounds issue with every single axis
        handleWallHit(point.x, velocity.x, acceleration.x);
        handleWallHit(point.y, velocity.y, acceleration.y);
        handleWallHit(point.z, velocity.z, acceleration.z);
    }
}

void Particle::drawSelf(uint16_t& colour) {
    protected_set_led_pk(help::normalize(point.x), help::normalize(point.y), help::normalize(point.z), colour);
}

void Particle::drawSelf() {
    protected_set_led_pk(help::normalize(point.x), help::normalize(point.y), help::normalize(point.z), color);
}
    
Particle::Particle(Vector p, Vector v, Vector a, uint16_t r, WallEffects e, Color c): resolution(r), color(c) {
    point = p; 
    velocity = v;
    acceleration = a;
    effect = e;
}
