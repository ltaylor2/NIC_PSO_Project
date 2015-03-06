CC = g++
CFLAGS= -g -Wall -std=c++0x

default: compile

compile: Main.o Swarm.o Particle.o
	$(CC) $? -o pso

Main.o: Main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

Swarm.o: Swarm.cpp Swarm.h
	$(CC) $(CFLAGS) -c $< -o $@

Particle.o: Particle.cpp Particle.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *~ pso
