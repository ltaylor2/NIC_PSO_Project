#pragma once

#include <vector>
#include <iostream>

#include "Particle.h"

/*
 
 ****************************
 *           Swarm          *
 ****************************
 Daniel Cohen, Josh Imhoff, and Liam Taylor. 2015. CS3445, Bowdoin College.
 
*/

// Enum used to choose function to optimize
// NOTE enum class is scoped, C++11 feature
enum class TestFunction {
    Rosenbrock,
    Ackley,
    Rastrigin
};

// PlainSwarm implements PSO with global topology.
//
// RingSwarm, RandomSwarm, VonNeumannSwarm inherit from PlainSwarm to allow
// for code reuse. updateLocalBests() is a virtual function called in run that
// is the only topology-dependent code in the class hierarchy. We override
// this method in RingSwarm, RandomSwarm, and VonNeumannSwarm.
class PlainSwarm {
public:
    // Constructor
    // @param numParticles -- number of particles in swarm as int
    // @param func -- enum specifying the function to optimize
    // @param dim -- dimensionality of the function as int
    PlainSwarm(unsigned int numParticles, TestFunction func, unsigned int dim);

    // Simple getters
    const std::vector<Particle>& getParticles() const { return particles; }
    const std::vector<double>& getGBest() const { return gBest; }
    double getGBestEval() const { return gBestEval; }
    
    // Run method used to start the optimization
    // @param -- number of iterations before halting the optimization
    // @note would be better if this was called automatically from the constructor
    //       but this is not possible since virtual functions (updateLocalBests) 
    //       cannot be called dynamically from the constructor
    void run(int iterations);
    
protected:
    // Topology-dependent function that updates the local bests of all particles
    // in the swarm
    // @note virtual so can be overriden by RingSwarm, RandomSwarm, and VonNeumannSwarm
    virtual void updateLocalBests();

    std::vector<Particle> particles;
    std::vector<double> gBest;
    double gBestEval;
};

// PSO with ring topology
class RingSwarm : public PlainSwarm {
public:
    RingSwarm(unsigned int numParticles, TestFunction func, unsigned int dim) 
        : PlainSwarm(numParticles, func, dim) {}
   
private:
    void updateLocalBests();
};

// PSO with random topology
class RandomSwarm : public PlainSwarm {
public:
    RandomSwarm(unsigned int numParticles, TestFunction func, unsigned int dim) 
        : PlainSwarm(numParticles, func, dim) {}
    
private:
    void updateLocalBests();
    bool contains(const std::vector<unsigned int>& nums, unsigned int index);
};

// PSO with Von Neumann topology
class VonNeumannSwarm : public PlainSwarm {
public:
    VonNeumannSwarm(unsigned int numParticles, TestFunction func, unsigned int dim) 
        : PlainSwarm(numParticles, func, dim) {}
    
private:
    void updateLocalBests();
};
