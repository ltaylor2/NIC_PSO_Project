#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <iostream>
#include <fstream>

#include "Swarm.h"

// This file includes the main function.
// Commandline options:
// @arg1 topology [gl=global | ri=ring | vn=von neum | ra=random] (string)
// @arg2 sizeOfSwarm (int)
// @arg3 numberOfIterations (int)
// @arg4 function [rok=rosenbrock | ack=ackley | ras=rastrigin] (string)
// @arg5 dimensionalityOfFunction (int)
int main(int argc, char** argv)
{
    if (argc != 6) {
        std::cout << "USAGE topology [gl | ri | vn | ra] sizeOfSwarm numOfIterations function [rok | ack | ras] dimOfFunction" << std::endl;
        return -1;
    }

    srand(time(NULL));
    
    std::clock_t start = std::clock();

    TestFunction func;
    std::string function(argv[4]);
    if (function == "rok")
        func = TestFunction::Rosenbrock;
    else if (function == "ack")
        func = TestFunction::Ackley;
    else if (function == "ras")
        func = TestFunction::Rastrigin;
    else {
        std::cout << "Invalid function. Closing." << std::endl;
        return -1;
    }

    std::string topology(argv[1]);
    
    if (topology == "gl") {
        PlainSwarm swarm(atoi(argv[2]), func, atoi(argv[5]));
        swarm.run(atoi(argv[3]));
    } else if (topology == "ri") {
        RingSwarm swarm(atoi(argv[2]), func, atoi(argv[5]));
        swarm.run(atoi(argv[3]));
    } else if (topology == "vn") {
        VonNeumannSwarm swarm(atoi(argv[2]), func, atoi(argv[5]));
        swarm.run(atoi(argv[3]));
    } else if (topology == "ra") {
        RandomSwarm swarm(atoi(argv[2]), func, atoi(argv[5]));
        swarm.run(atoi(argv[3]));
    }

    std::clock_t end = std::clock();
    double timeInSeconds = (end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Time elapsed: " << timeInSeconds << " seconds" << std::endl;
    
    return 0;
}
