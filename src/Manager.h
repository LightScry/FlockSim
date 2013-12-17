#ifndef MANAGER_H
#define MANAGER_H
#include <stdio.h>
#include <string>
#include "Graph.h"
#include "Node.h"

class Manager {
	//do we really want the manager to store these? or should it just
	//initialize an Algo that deals with them? only place we actually
	//need these values is in update(), wherever we decide to put that
	static double CurrentAlignment;
	static double CurrentSeparation;
	static double CurrentCohesion;

	static Graph g;

	public:
	 	static void* gameLoop(void *data);
	 	static void update();
		static void init();
		static void main();
};
#endif

/*
Manager
	- Holds all global info
		- Current Params
		- Goal (or goals)
	+ Init Simulation
		- Instantiate objects
	+ Run Simulation
		- Begin game loop
	+ Update
		- Change params → Either restart or refresh all states
*/
