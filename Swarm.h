#include <vector>

#include "Particle.h"

class Swarm {
public:
    Swarm(int numParticles, int dim, Particle::toOptimize f, int maxIterations);
    void run(int maxIterations);

    const std::vector<Particle>& getParticles() const { return particles; }
    const std::vector<Particle>& getGBest() const { return gBest; }
    double getGBest() const { return gBestEval; }

private:
    virtual void updateLocalBests() = 0;
    
    std::vector<Particle> particles;
    std::vector<double> gBest;
    double gBestEval;
};

class GlobalSwarm : public Swarm {
public:
    GlobalSwarm(int numParticles, int dim, Particle::toOptimize f, int maxIterations);
    void updateGlobalBests();
};

double ackley(const std::vector<double>& x); 
double rastrigin(const std::vector<double>& x); 
double rosenbrock(const std::vector<double>& x); 
