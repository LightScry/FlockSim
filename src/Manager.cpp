#include "Manager.h"
#include "Graph.h"

#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
typedef std::chrono::milliseconds milliseconds;

// Static initialization
int Manager::CurrentAlignment = 0;
int Manager::CurrentSeperation = 0;
int Manager::CurrentCohesion = 0;

// Game loop Params
int FPS = 30.0;
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
		std::cout << "-------" << std::endl << "Tick:" << tick << std::endl;
		
		// Update all Managers once per tick
		Manager::update();
	}
}

void Manager::update(){
	printf( "Updating Manager...\n" );
}
