#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include "Swarm.h"

int main(int argc, char** argv)
{
    if (argc != 6) {
        std::cout << "USAGE topology [gl | ri | vn | ra] sizeOfSwarm numOfIterations function [rok | ack | ras] dimOfFunction" << std::endl;
        return -1;
    }

    srand(time(NULL));

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
        PlainSwarm swarm(atoi(argv[2]), atoi(argv[3]), func, atoi(argv[5]));
    }

    return 0;
}
