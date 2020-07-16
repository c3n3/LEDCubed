#pragma once
#include "../App.h"
#include "../../Tools/ParticleSystem/Particle.h"
#include "../../Tools/MathObjects/Vector.h"

class RandomParticles: public App
{
private:
    Particle* particles; // array of particle pointers
protected:
    bool init();
    void end();
public:
    String title = "Particles";
    bool frame();
};

bool RandomParticles::init() {
    particles = (Particle*)malloc(sizeof(Particle) * 10);
    for (int i = 0; i < 10; i++) {
        // create a bunch of bouncy particles with random everything
        particles[i] = Particle(
            Vector<float>((rand() % 2 + 4.0), rand() % 2 + 4.0, rand() % 2 + 4.0), 
            Vector<float>((rand() % 2) * 1.0, (rand() % 2) * 1.0, (rand() % 2) *1.0), 
            Vector<float>((rand() % 2) * 1.0, (rand() % 2) * 1.0, (rand() % 2) *1.0), 
            100, Particle::BOUNCE);
    }
    return CONTINUE_PROGRAM;
}

bool RandomParticles::frame() {
    for (int i = 0; i < 10; i++) {
        particles[i].updatePosition();
        particles[i].drawSelf();
    }
    return CONTINUE_PROGRAM;
}

void RandomParticles::end() {
    // memory clean up
    // for (int i = 0; i < 10; i++) {
    //     delete particles[i];
    // }
    free(particles);
}