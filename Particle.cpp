#include "Particle.h"

Particle::Particle(int dim, double phiP_, double phiG_) : 
            position(dim, 0),
            velocity(dim, 0),
            pBest(dim, 0),
            gBest(dim, 0),
            phiP(phiP_),
            phiG(phiG_),
            cg(0)
{}

void Particle::update() {
    updateVelocity();
    updatePosition();
    updatePersonalBest();
}

void Particle::updateVelocity() {
    for (int i = 0; i < position.size(); i++) {
        velocity[i] = cf * (velocity[i] + (Particle::getRandFromZeroTo(phiP) * 
                            (pBest[i] - position[i]) + Particle::getRandFromZeroTo(phiG) * 
                            (gBest[i] - position[i])));    
    }
}

void Particle::updatePosition() {
    for (int i = 0; i < position.size(); i++) { 
        position[i] += velocity[i];
    }
}

void Particle::updatePersonalBest() {
    if (f(position) > pBestEval)
        pBest = position;
}
