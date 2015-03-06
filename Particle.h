#pragma once

#include <cstdlib>
#include <vector>
#include <cmath>

// Function pointer to function to optimize
// NOTE typedef allows us to have the function pointer as static 
//      variable of Particle
typedef double (*toOptimize)(const std::vector<double>& x);

// Particle stores a position in the function domain, a velocity to control
// movement thru the space, and includes functions for updating the particle
// according to its position and velocity, evaluating the function at its position,
// and storing its personal best found and its topology-dependent local best found
// position and evaluation.
class Particle {
public:
    // Constructor
    // @param dim -- dimensionality of function being optimized and hence particle
    Particle(unsigned int dim);

    // Two phase construction, randInit sets position[i] between lpos and rpos
    // and velocity[i] between lvel and rvel for all i
    // @param lpos -- min value of position[i] for all i
    // @param rpos -- max value of position[i] for all i
    // @param lvel -- min value of velocity[i] for all i
    // @param rvel -- max value of velocity[i] for all i
    void randInit(double lpos, double rpos, double lvel, double rvel);

    // Updates particle according to position, velocity, personal best, and local best
    // Called once per iteration of PSO
    void update();

    // Simple getters
    double getPersonalBestEval() const { return pBestEval; }
    const std::vector<double>& getPersonalBest() const { return pBest; }

    // Set topology-dependent local best, called in updateLocalBests in Swarm classes
    // @param lBest -- the new local best
    void updateLocalBest(const std::vector<double>& lBest_) { lBest = lBest_; }

    // Function pointer to function to optimize 
    // NOTE alllows Particle to evaluate its position and update
    //      its local best if necessary, static since all 
    //      particles are optimizing same function
    static toOptimize f;

private:
    // Helper methods called by update()
    void updateVelocity();
    void updatePosition();
    void updatePersonalBest();

    // Positions, velocities, personal and local bests
    std::vector<double> position;         // current position
    std::vector<double> velocity;         // current velocity
    std::vector<double> pBest;            // personal best
    std::vector<double> lBest;            // global best of all particles
    double pBestEval;                     // f(personal best)

    // Constants
    static constexpr double phiP = 2.05;  // local scale factor
    static constexpr double phiG = 2.05;  // global scale factor
    static constexpr double cf = 0.7298;  // constriction factor

    // Static helper method
    // @param x
    // @returns random number between 0 and x inclusive
    static double getRandFromZeroTo(double x) {
        return static_cast<double>(rand()) / RAND_MAX * x;
    }
};
