#pragma once
#include "../App.h"
#include "../../Tools/ParticleSystem/Particle.h"
#include "../../Tools/MathObjects/Vector.h"

class RandomParticles: public App
{
private:
    Particle* particles; // array of particle pointers
protected:
    App::Resut init();
    void end();
public:
    String title = "Particles";
    App::Resut frame();
};

App::Resut RandomParticles::init() {
    particles = (Particle*)malloc(sizeof(Particle) * 10);
    for (int i = 0; i < 10; i++) {
        // create a bunch of bouncy particles with random everything
        particles[i] = Particle(
            Vector<float>((rand() % 2 + 4.0), rand() % 2 + 4.0, rand() % 2 + 4.0), 
            Vector<float>((rand() % 2) * 1.0, (rand() % 2) * 1.0, (rand() % 2) *1.0), 
            Vector<float>((rand() % 2) * 1.0, (rand() % 2) * 1.0, (rand() % 2) *1.0), 
            100, Particle::BOUNCE);
    }
    return App::CONTINUE;
}

App::Resut RandomParticles::frame() {
    for (int i = 0; i < 10; i++) {
        particles[i].updatePosition();
        particles[i].drawSelf();
    }
    return App::CONTINUE;
}

void RandomParticles::end() {
    // memory clean up
    // for (int i = 0; i < 10; i++) {
    //     delete particles[i];
    // }
    free(particles);
}