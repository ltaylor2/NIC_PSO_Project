#include "Swarm.h"

#include <limits>
#include <iostream>

// TODO use constants from standard lib
const double PI = 3.141592653589793238463;
const double E =  2.71828182845904523536;

double rosenbrock(const std::vector<double>& x) {
	double retVal = 0;
	for (unsigned int i = 0; i < x.size() - 1; i++) {
		retVal += 100.0 * pow(x[i+1] - (x[i] * x[i]), 2.0) + pow(x[i] - 1.0, 2.0);
	}
	return retVal;
}

double ackley(const std::vector<double>& x) {
	double firstSum = 0;
	double secondSum = 0;
	for (unsigned int i = 0; i < x.size(); i++) {
		firstSum += (x[i] * x[i]);
		secondSum += cos(2.0 * PI * x[i]);
	}
	return -20.0 * exp(-0.2 * sqrt(firstSum/x.size())) - exp(secondSum/x.size()) + 20.0 + E;
}

double rastrigin(const std::vector<double>& x) {
	double retVal = 0;
	for (unsigned int i = 0; i < x.size(); i++) {
		retVal += (x[i] * x[i]) - 10.0 * cos(2.0 * PI * x[i]) + 10.0;
	}
	return retVal;
}

PlainSwarm::PlainSwarm(int numParticles, int iterations, TestFunction func, int dim)
    : particles(numParticles, Particle(dim)),
      gBest(dim, 0), gBestEval(std::numeric_limits<double>::max())
{
    if (func == TestFunction::Rosenbrock) {
        Particle::f = rosenbrock;
        for (unsigned int i = 0; i < particles.size(); i++)
            particles[i].randInit(15.0, 30.0, -2.0, 2.0);
    }
    else if (func == TestFunction::Ackley) {
        Particle::f = ackley;
        for (unsigned int i = 0; i < particles.size(); i++)
            particles[i].randInit(16.0, 32.0, -2.0, 4.0);
    }
    else {
        Particle::f = rastrigin;
        for (unsigned int i = 0; i < particles.size(); i++)
            particles[i].randInit(2.56, 5.12, -2.0, 4.0);
    }

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
