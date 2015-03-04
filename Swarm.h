#pragma once

#include <vector>

#include "Particle.h"

enum class TestFunction {
    Rosenbrock,
    Ackley,
    Rastrigin
};

class PlainSwarm {
public:
    PlainSwarm(int numParticles, int iterations, TestFunction func, int dim);
    void run(int iterations);

    const std::vector<Particle>& getParticles() const { return particles; }
    const std::vector<double>& getGBest() const { return gBest; }
    double getGBestEval() const { return gBestEval; }

private:
    void updateLocalBests();
    
    std::vector<Particle> particles;
    std::vector<double> gBest;
    double gBestEval;
};
