#include "Swarm.h"

#include <limits>
#include <iostream>

PlainSwarm::PlainSwarm(int numParticles, int iterations, toOptimize f, int dim)
    : particles(numParticles, Particle(dim)),
      gBest(dim, 0), gBestEval(std::numeric_limits<double>::max())
{
    Particle::f = f;
    run(iterations);
}

void PlainSwarm::run(int iterations) 
{
    for (int i = 1; i <= iterations; i++) {
        std::cout  << "At iteration " << i << ", ";

        for (unsigned int i = 0; i < particles.size(); i++) {
            particles[i].update();
            double pBestEval = particles[i].getPersonalBestEval();
            if (pBestEval < gBestEval) {
                gBestEval = pBestEval;
                gBest = particles[i].getPersonalBest();
            }
        }
        updateLocalBests();

        std::cout << "global best is " << gBestEval << "." << std::endl;
    }
}

void PlainSwarm::updateLocalBests()
{
    for (unsigned int i = 0; i < particles.size(); i++)
        particles[i].updateLocalBest(gBest);
}

