CC = g++
CFLAGS= -g -Wall -std=c++0x

default: compile

compile: Swarm.o Particle.o
	$(CC) $? -o pso

Swarm.o: Swarm.cpp Swarm.h
	$(CC) $(CFLAGS) -c $< -o $@

Particle.o: Particle.cpp Particle.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *~ pso
