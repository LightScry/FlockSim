#include "Manager.h"

#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h> 

#define NUM_NODES 150
#define DATA_FILE "node_data.json"
#define VERBOSE false
typedef std::chrono::milliseconds milliseconds;

// Static initialization
double Manager::CurrentAlignment = 20.0 / POS_BOUND;
double Manager::CurrentSeparation = 10.0 / POS_BOUND;
double Manager::CurrentCohesion = 10.0 / POS_BOUND;
Graph Manager::g = Graph(NUM_NODES, CurrentSeparation, CurrentCohesion, CurrentAlignment, time(NULL));

// Game loop Params
const int FPS = 30.0;
int tick = 0;
void Manager::gameLoop(){
	while(true){
		// Sleep this thread depending on desired FPS.
		// NOTE: 	Sleeping thread here may prove VERY inefficient.
		//			If performance issues happen, break into 2 threads
		//			or don't use threads at all.
		int time_to_sleep = 1000.0 / FPS;
		tick ++;
	   	std::this_thread::sleep_for(milliseconds(time_to_sleep));
		
		if (VERBOSE)
			std::cout << "-------" << std::endl << "Tick:" << tick << std::endl;
		
		g.writeNodes(DATA_FILE);
		
		// Update all Managers once per tick
		Manager::update();
	}
}

void Manager::update(){
	if (VERBOSE)
		printf( "Updating Manager...\n" );
	g.update(1.0/FPS);

	//move node randomly
	//g.updateRandomMove(time(NULL));
}

void Manager::init(){
	if (VERBOSE)
		printf( "Manager init...\n" );
	Manager::gameLoop();
}
