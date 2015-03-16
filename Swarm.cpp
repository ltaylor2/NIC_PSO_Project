#include "Swarm.h"

#include <limits>
#include <iostream>
#include <fstream>
#include <iomanip>

/*
 
 ****************************
 *           Swarm          *
 ****************************
 Daniel Cohen, Josh Imhoff, and Liam Taylor. 2015. CS3445, Bowdoin College.
 
*/

// NOTE issue including appropriate constants from stdlib led to us
//      writing out these constants by hand
const double PI = 3.141592653589793238463;
const double E =  2.71828182845904523536;

// Functions for testing PSO implementation. Take a vector as param to allow for 
// arbitrary dimensional functions.
//
// Rosenbrock function
// @param x -- input to function
// @returns f(x) as double
double rosenbrock(const std::vector<double>& x) {
	double retVal = 0;
	for (unsigned int i = 0; i < x.size() - 1; i++) {
		retVal += 100.0 * pow(x[i+1] - (x[i] * x[i]), 2.0) + pow(x[i] - 1.0, 2.0);
	}
	return retVal;
}

// Ackley function
// @param x -- input to function
// @returns f(x) as double
double ackley(const std::vector<double>& x) {
	double firstSum = 0;
	double secondSum = 0;
	for (unsigned int i = 0; i < x.size(); i++) {
		firstSum += (x[i] * x[i]);
		secondSum += cos(2.0 * PI * x[i]);
	}
	return -20.0 * exp(-0.2 * sqrt(firstSum/x.size())) - exp(secondSum/x.size()) + 20.0 + E;
}

// Rastrigin function
// @param x -- input to function
// @returns f(x) as double
double rastrigin(const std::vector<double>& x) {
	double retVal = 0;
	for (unsigned int i = 0; i < x.size(); i++) {
		retVal += (x[i] * x[i]) - 10.0 * cos(2.0 * PI * x[i]) + 10.0;
	}
	return retVal;
}

// See doc in Swarm.h
PlainSwarm::PlainSwarm(unsigned int numParticles, TestFunction func, unsigned int dim)
    : particles(numParticles, Particle(dim)),
      gBest(dim, 0), 
      gBestEval(std::numeric_limits<double>::max())
{
    // NOTE for testing purposes, particles initial position and velocity
    //      are constrained based on the function being optimized
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
}

// See doc in Swarm.h
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

// See doc in Swarm.h
// In global topology, global best is local best of all particles.
void PlainSwarm::updateLocalBests()
{
    for (unsigned int i = 0; i < particles.size(); i++)
        particles[i].updateLocalBest(gBest);
}

// See doc in Swarm.h
// In ring topology, best of two closest particles to particle in vector is
// the local best of the particle.
void RingSwarm::updateLocalBests() {
    for (unsigned int i = 0; i < particles.size(); i++) {
        unsigned int leftIndex, rightIndex;
        unsigned int ringBestIndex = i;
        
        if (i == 0)
            leftIndex = (unsigned int)particles.size() - 1;
        else
            leftIndex = i - 1;
    
        rightIndex = (i + 1) % particles.size();
        
        if (particles[leftIndex].getPersonalBestEval() < particles[i].getPersonalBestEval())
            ringBestIndex = leftIndex;
        
        if (particles[rightIndex].getPersonalBestEval() < particles[i].getPersonalBestEval()
            && particles[rightIndex].getPersonalBestEval() < particles[leftIndex].getPersonalBestEval())
            ringBestIndex = rightIndex;
        
        
        particles[i].updateLocalBest(particles[ringBestIndex].getPersonalBest());
    }
}

// See doc in Swarm.h
// In Von Neumann topology, the particles are arranged into a 2D grid, and the 
// best of a particle's four neighbors and itself is the local best
// of the particle.
void VonNeumannSwarm::updateLocalBests() {
    // Find size (rows and cols) of closest to square 2D grid such that
    // rows*cols = numParticles
    // NOTE probably should happen in the constructor
    unsigned int rows, cols;
    for (unsigned int i = sqrt(particles.size()); i < particles.size(); i++) {
        if (particles.size() % i == 0) {
            rows = i;
            cols = particles.size()/i;
            break;
        }
    }

    // Find indexes of particles in neighborhood
    unsigned int up, down, left, right;
    for (unsigned int i = 0; i < particles.size(); i++) {
        // Setting left
        if (i % cols == 0)
            left = i + cols - 1;
        else
            left = i - 1;
        
        // Setting above
        if (i < cols)
            up = (rows - 1) * cols + i;
        else
            up = i - cols;

        // Setting right
        if ((i+1)% cols == 0)
            right = i - cols + 1;
        else
            right = i + 1;
        
        // Setting below
        if (i >= particles.size() - cols)
            down = i - ((rows - 1) * cols);
        else
            down = i + cols;
        
        // Find best of four neighbors plus self
        unsigned int neighborhood[5] = {i, left, up, right, down};
        unsigned int bestIndex = i;
        double bestEval = particles[i].getPersonalBestEval();
        
        for (unsigned int j = 0; j < 5; j++) {
            if (particles[neighborhood[j]].getPersonalBestEval() < bestEval) {
                bestIndex = neighborhood[j];
                bestEval = particles[neighborhood[j]].getPersonalBestEval();
            }
        }

        particles[i].updateLocalBest(particles[bestIndex].getPersonalBest());
    }
}

// See doc in Swarm.h
// In random topology, at each iteration for every particle, k=5 randomly selected
// particles are compared to find local best of particle.
void RandomSwarm::updateLocalBests() {
    for (unsigned int i = 0; i < particles.size(); i++) {
        
        unsigned int nsize = 5; // Neighborhood size

        // Initialize a vector with increasing integers up to the number of particles
        std::vector<unsigned int> nums;
        while (nums.size() < nsize) {
            unsigned int newRand = static_cast<int>(rand()) % particles.size();
            if (!contains(nums, newRand) && newRand != i)
                nums.push_back(newRand);
        }
        
        // Let the first k numbers of the vector be the random particles in neighborhood
        unsigned int randomBestIndex = i;
        double randomBestEval = particles[i].getPersonalBestEval();
        
        for (unsigned int n = 0; n < nums.size(); n++) {
            if (particles[nums[n]].getPersonalBestEval() < randomBestEval) {
                randomBestIndex = nums[n];
                randomBestEval = particles[nums[n]].getPersonalBestEval();
            }
        }
        
        particles[i].updateLocalBest(particles[randomBestIndex].getPersonalBest());
    }
}

// Helper method for RandomSwarm::updateLocalBests
bool RandomSwarm::contains(const std::vector<unsigned int>& nums, unsigned int index) {
    for(unsigned int i = 0; i < nums.size(); i++) {
        if (nums[i] == index)
            return true;
    }
    return false;
}
