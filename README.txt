**************************************************************************************
A Comparison of Neighborhood Topologies in Particle Swarm Optimization
***************************************************************************************
Dan Cohen, Josh Imhoff, and Liam Taylor
March 6, 2015
Project 2
CS3445

This project is designed to produce benchmarks for a Particle Swarm Optimization (PSO) algorithm with different topologies. Four topologies are implemented here: Global, Ring, Von Neumann, and Random. The specifics of these topologies can be seen in the code documentation or the associated report. The PSO algorithm can be run with three different functions: Rosenbrock, Ackley, and Rastrigin.

TO RUN:
After running the makefile in the project folder directory, run the program from the command line using the following syntax:

“./pso”

then,
	* topology (decides the particle’s neighborhood knowledge):
				“gl” - Global
				“ri” - Ring
				“vn” - Von Neumann
				“ra” - Random

	* sizeOfSwarm: Total number of particles in the swarm
		
	* numOfIterations: Number of iterations the algorithm will run

	* function (decides what function assesses the particles’ position):
				“rok” - Rosenbrock
				“ack” - Ackley
				“ras” - Rastrigin

	* dimOfFunction: The number of dimensions the function will assess

For example, to run the PSO with Ring topology on the Ackley function, with 50 particles, 50000 iterations, and 30 dimensions enter:
“./pso ri 50 50000 ack 30”

