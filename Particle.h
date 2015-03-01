#pragma once

#include <cstdlib>
#include <vector>
#include <cmath>

// TODO use constants from standard lib
const double PI = 3.141592653589793238463;
const double E =  2.71828182845904523536;

typedef double (*toOptimize)(const std::vector<double>& x);

class Particle {
public:
    Particle(int dim, double phiP_, double phiG_);  // TODO constructor should randomly intialize position according to write up
    void update();
    double getPersonalBestEval() const { return pBestEval; }
    const std::vector<double>& getPersonalBest() const { return pBest; }
    void updateGlobalBest(const std::vector<double>& gBest_) { gBest = gBest_; }

private:
    void updateVelocity();
    void updatePosition();
    void updatePersonalBest();

    std::vector<double> position;     // current position
    std::vector<double> velocity;     // current velocity
    std::vector<double> pBest;        // personal best
    std::vector<double> gBest;        // global best of all particles
    // TODO gBest should be called lBest for local best, not a global best bc/ of topologies

    double pBestEval;                 // f(personal best)
    double gBestEval;                 // f(global best)

    double phiP;                      // local scale factor
    double phiG;                      // global scale factor
    double cf;                        // constriction factor
    // TODO cf currently ever set? should be const?
    
    // Pointer to function to optimize
    static toOptimize f;

    // Returns random number between 0 and x inclusive
    static double getRandFromZeroTo(double x) {
        return static_cast<double>(rand()) / RAND_MAX * x;
    }
};
