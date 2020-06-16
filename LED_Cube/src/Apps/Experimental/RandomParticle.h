#include "../App.h"
#include "../../Tools/ParticleSystem/Particle.h"

class RandomParticles: public App
{
private:
    Particle** particles; // array of particle pointers
protected:
    void init();
    void end();
public:
    String title = "Particles";
    bool frame();
};

void RandomParticles::init() {
    particles = new Particle*[10];
    for (int i = 0; i < 10; i++) {
        // create a bunch of bouncy particles with random everything
        particles[i] = new Particle(
            Vector(rand() % 2 + 4, rand() % 2 + 4, rand() % 2 + 4), 
            Vector(rand() % 2, rand() % 2, rand() % 2), 
            Vector(rand() % 2, rand() % 2, rand() % 2), 
            100, Particle::BOUNCE);
    }
}

bool RandomParticles::frame() {
    for (int i = 0; i < 10; i++) {
        particles[i]->updatePosition();
        particles[i]->drawSelf();
    }
    return CONTINUE_PROGRAM;
}

void RandomParticles::end() {
    // memory clean up
    for (int i = 0; i < 10; i++) {
        delete particles[i];
    }
    delete[] particles;
}