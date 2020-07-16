#include "Particle.h"
void Particle::handleWallHit(float& x, float& v, float& a, uint32_t& t, float& orig) {

    // these equations for more precision could be made to calculate intersect point, but that seems too expensive
    if (x > 11 || x < 0) {
        x = (11 < x) * 11; // make either one or 11 (could do above ^^^^)
        if (effect == STICK) {
            velocity.set(0,0,0);
            acceleration.set(0,0,0);
        }
        else if (effect == BOUNCE) {
            // velocity = the change in time * acceleration * 
            v = -(v + a * (timer - t) * 0.001); // perfectly elastic equation?
            t = timer; // new tragectory new time start
            orig = x;
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
    timeStartX = other.timeStartX;
    timeStartY = other.timeStartY;
    timeStartZ = other.timeStartZ;
}

void Particle::updatePosition() {
    // use equations x = x0 + v * t + 1/2 * a * t^2, where t = time passed = timer - timeStart
    if (millis() - timer > resolution) {
        point.x = origin.x + velocity.x * (timer - timeStartX) * 0.001 + 0.5 * acceleration.x * (timer - timeStartX) * (timer - timeStartX) * 0.001 * 0.001;
        point.y = origin.y + velocity.y * (timer - timeStartY) * 0.001 + 0.5 * acceleration.y * (timer - timeStartY) * (timer - timeStartY) * 0.001 * 0.001;
        point.z = origin.z + velocity.z * (timer - timeStartZ) * 0.001 + 0.5 * acceleration.z * (timer - timeStartZ) * (timer - timeStartZ) * 0.001 * 0.001;
        timer += resolution;

        // handle a bounds issue with every single axis
        handleWallHit(point.x, velocity.x, acceleration.x, timeStartX, origin.x);
        handleWallHit(point.y, velocity.y, acceleration.y, timeStartY, origin.y);
        handleWallHit(point.z, velocity.z, acceleration.z, timeStartZ, origin.z);
    }
}

void Particle::drawSelf(const uint16_t& colour) {
    protected_set_led_pk(help::normalize(point.x), help::normalize(point.y), help::normalize(point.z), colour);
}

void Particle::drawSelf() {
    protected_set_led_pk(help::normalize(point.x), help::normalize(point.y), help::normalize(point.z), color);
}
    
Particle::Particle(Vector<float> p, Vector<float> v, Vector<float> a, uint16_t r, WallEffects e, Color c): resolution(r), color(c) {
    point = p; 
    velocity = v;
    acceleration = a;
    effect = e;
    origin = p;
    timeStartX = millis();
    timeStartY = millis();
    timeStartZ = millis();
    timer = millis();
}
