#include "Particle.h"

#include <limits>
#include <iostream>

/*
 
 ****************************
 *         Particle         *
 ****************************
 Daniel Cohen, Josh Imhoff, and Liam Taylor. 2015. CS3445, Bowdoin College.

*/

// Static function pointer defined
toOptimize Particle::f;

// See doc in Particle.h
Particle::Particle(unsigned int dim)
    : position(dim, 0), 
      velocity(dim, 0), 
      pBest(dim, 0), 
      lBest(dim, 0),
      pBestEval(std::numeric_limits<double>::max()) {} 

// See doc in Particle.h
void Particle::randInit(double lpos, double rpos, double lvel, double rvel)
{
    for (unsigned int i = 0; i < position.size(); i++) {
        position[i] = Particle::getRandFromZeroTo(rpos - lpos) + lpos;
        velocity[i] = Particle::getRandFromZeroTo(rvel - lvel) - lvel;
    }
}

// See doc in Particle.h
void Particle::update() {
    updateVelocity();
    updatePosition();
    updatePersonalBest();
}

// See doc in Particle.h
void Particle::updateVelocity() {
    for (unsigned int i = 0; i < position.size(); i++) {
        velocity[i] = cf * (velocity[i] + (Particle::getRandFromZeroTo(phiP) * 
                            (pBest[i] - position[i]) + Particle::getRandFromZeroTo(phiG) * 
                            (lBest[i] - position[i])));    
    }
}

// See doc in Particle.h
void Particle::updatePosition() {
    for (unsigned int i = 0; i < position.size(); i++) { 
        position[i] += velocity[i];
    }
}

// See doc in Particle.h
void Particle::updatePersonalBest() {
    double eval = f(position);
    if (eval < pBestEval) {
        pBestEval = eval;
        pBest = position;
    }
}
