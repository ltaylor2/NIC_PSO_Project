#pragma once

#include <cstdlib>
#include <vector>
#include <cmath>

typedef double (*toOptimize)(const std::vector<double>& x);

class Particle {
public:
    Particle(int dim);
    void randInit(double lpos, double rpos, double lvel, double rvel);
    void update();
    double getPersonalBestEval() const { return pBestEval; }
    const std::vector<double>& getPersonalBest() const { return pBest; }
    void updateLocalBest(const std::vector<double>& lBest_) { lBest = lBest_; }
    
    static toOptimize f;                  // pointer to function to optimize 

private:
    void updateVelocity();
    void updatePosition();
    void updatePersonalBest();

    std::vector<double> position;         // current position
    std::vector<double> velocity;         // current velocity
    std::vector<double> pBest;            // personal best
    std::vector<double> lBest;            // global best of all particles

    double pBestEval;                     // f(personal best)
    double lBestEval;                     // f(local best)

    static constexpr double phiP = 2.05;  // local scale factor
    static constexpr double phiG = 2.05;  // global scale factor
    static constexpr double cf = 0.7298;  // constriction factor

    // Returns random number between 0 and x inclusive
    static double getRandFromZeroTo(double x) {
        return static_cast<double>(rand()) / RAND_MAX * x;
    }
};
