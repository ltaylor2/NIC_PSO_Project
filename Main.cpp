#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include "Swarm.h"

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
	return -20.0 * exp(-0.2 * sqrt(firstSum/2.0)) - exp(secondSum/2.0) + 20.0 + E;
}

double rastrigin(const std::vector<double>& x) {
	double retVal = 0;
	for (unsigned int i = 0; i < x.size(); i++) {
		retVal += (x[i] * x[i]) - 10.0 * cos(2.0 * PI * x[i]) + 10.0;
	}
	return retVal;
}

int main(int argc, char** argv)
{
    if (argc != 6) {
        std::cout << "USAGE topology [gl | ri | vn | ra] sizeOfSwarm numOfIterations function [rok | ack | ras] dimOfFunction" << std::endl;
        return -1;
    }

    srand(time(NULL));

    // TODO hard coded for Rosenbrock
    std::string topology(argv[1]);
    if (topology == "gl") {
        PlainSwarm swarm(atoi(argv[2]), atoi(argv[3]), rosenbrock, atoi(argv[5]));
    }

    return 0;
}
