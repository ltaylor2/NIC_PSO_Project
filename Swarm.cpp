#include "Swarm.h"
#include <limits>

Swarm::Swarm(int numParticles, int dim, Particle::toOptimize f, int maxIterations)
    : particles(numParticles, Particle(dim, TODO, TODO)),
      gBest(dim, 0), gBestEval(std::numerical_limits<int>::min())
{
    Particle::f = f;
    run(maxIterations);
}

void Swarm::run(int maxIterations) 
{
    for (int i = 1; i <= maxIterations; i++) {
        std::cout  << "At iteration " << i << ", ";

        for (int i = 0; i < particles.size(); i++) {
            particles[i].update();
            int pBestEval = particles[i].getPersonalBestEval();
            if (pBestEval > gBestEval) {
                gBestEval = pBestEval;
                gBest = particles[i].getPersonalBest();
            }
        }
        updateGlobalBests();

        std::cout << "global best is " << gBestEval << "." << std::endl;
    }
}

GlobalSwarm::GlobalSwarm(int numParticles, int dim, Particle::toOptimize f, int maxIterations)
    : Swarm(numParticles, dim, f, maxIterations)
{}

GlobalSwarm::updateLocalBests()
{
    for (int i = 0; i < particles.size(); i++)
        particles[i].updateGlobalBest(gBest);
}

double ackley(const std::vector<double>& x) {
	double firstSum = 0;
	double secondSum = 0;
	for (int i = 0; i < x.size(); i++) {
		firstSum += (x[i] * x[i]);
		secondSum += cos(2.0 * PI * x[i]);
	}
	return -20.0 * exp(-0.2 * sqrt(firstSum/2.0)) - exp(secondSum/2.0) + 20.0 + E;
}

double rastrigin(const std::vector<double>& x) {
	double retVal = 0;
	for (int i = 0; i < x.size(); i++) {
		retVal += (x[i] * x[i]) - 10.0 * cos(2.0 * PI * x[i]) + 10.0;
	}
	return retVal;
}

double rosenbrock(const std::vector<double>& x) {
	double retVal = 0;
	for (int i = 0; i < x.size() - 1; i++) {
		retVal += 100.0 * pow(x[i+1] - (x[i] * x[i]), 2.0) + pow(x[i] - 1.0, 2.0);
	}
	return retVal;
}
