#include "Particle.h"

#include <limits>
#include <iostream>

toOptimize Particle::f;

Particle::Particle(int dim)
    : position(dim, 0), 
      velocity(dim, 0), 
      pBest(dim, 0), 
      lBest(dim, 0),
      pBestEval(std::numeric_limits<double>::max()), 
      lBestEval(std::numeric_limits<double>::max()) {}

void Particle::randInit(double lpos, double rpos, double lvel, double rvel)
{
    for (unsigned int i = 0; i < position.size(); i++) {
        position[i] = Particle::getRandFromZeroTo(rpos - lpos) + lpos;
        velocity[i] = Particle::getRandFromZeroTo(rvel - lvel) - lvel;
    }
}

void Particle::update() {
    updateVelocity();
    updatePosition();
    updatePersonalBest();
}

void Particle::updateVelocity() {
    for (unsigned int i = 0; i < position.size(); i++) {
        velocity[i] = cf * (velocity[i] + (Particle::getRandFromZeroTo(phiP) * 
                            (pBest[i] - position[i]) + Particle::getRandFromZeroTo(phiG) * 
                            (lBest[i] - position[i])));    
    }
}

void Particle::updatePosition() {
    for (unsigned int i = 0; i < position.size(); i++) { 
        position[i] += velocity[i];
    }
}

void Particle::updatePersonalBest() {
    double eval = f(position);
    if (eval < pBestEval) {
        pBestEval = eval;
        pBest = position;
    }
}
