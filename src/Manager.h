#ifndef MANAGER_H
#define MANAGER_H


class Manager {
	//do we really want the manager to store these? or should it just
	//initialize an Algo that deals with them? only place we actually
	//need these values is in update(), wherever we decide to put that
	static int CurrentAlignment;
	static int CurrentSeperation;
	static int CurrentCohesion;
	public:
	 	static void gameLoop();
	 	static void update();
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
