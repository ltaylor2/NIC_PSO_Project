#include "Particle.h"

#include <limits>
#include <iostream>

toOptimize Particle::f;

// TODO generalize randomization
Particle::Particle(int dim)
    : position(dim, 0), 
      velocity(dim, 0), 
      pBest(dim, 0), 
      lBest(dim, 0),
      pBestEval(std::numeric_limits<double>::max()), 
      lBestEval(std::numeric_limits<double>::max())
{
    // NOTE hard coded for Rosenbrock
    for (int i = 0; i < dim; i++) {
        position[i] = Particle::getRandFromZeroTo(15.0) + 15.0;
        velocity[i] = Particle::getRandFromZeroTo(4.0) - 2.0;
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
    int eval = f(position);
    if (eval < pBestEval) {
        pBestEval = eval;
        pBest = position;
    }
}
