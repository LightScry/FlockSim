#include "Manager.h"

#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h> 
#include <string>
#include <pthread.h>

#define NUM_NODES 150
#define DATA_FILE "node_data.json"
#define VERBOSE false
typedef std::chrono::milliseconds milliseconds;

// Static initialization
double Manager::CurrentAlignment = 15.0 / POS_BOUND;
double Manager::CurrentSeparation = 50.0 / POS_BOUND;
double Manager::CurrentCohesion = 7.5 / POS_BOUND;
Graph Manager::g;

// Game loop Params
int still_looping = 1;
const int FPS = 30.0;
int tick = 0;
pthread_t t;
void* Manager::gameLoop(void *data){
	while(still_looping){
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
	std::cout << "Exited gameLoop" << std::endl;
	return 0;
}

void catch_thread(){
	pthread_join(t, NULL);
}

void Manager::update(){
	if (VERBOSE)
		printf( "Updating Manager...\n" );
	g.update(1.0/FPS);
}

void Manager::init(){
	if (VERBOSE)
		printf( "Manager init...\n" );

	still_looping = true;
	//run simulation on another thread
    pthread_create(&t, NULL, Manager::gameLoop, NULL);
	Manager::g = Graph(NUM_NODES, CurrentSeparation, CurrentCohesion, CurrentAlignment, time(NULL));
}

void Manager::main(){
	Manager::init();
	
	while(true){
		std::string input; 
		std::cout << "Enter Command: ";
		std::cin >> input;
		//std::cout << "out:" << input.compare("exit") << std::endl;
		
		if (input.compare("exit") == 0){
			still_looping = false;
			catch_thread();
			break;
		}
		else if (input.compare("restart") == 0){
			still_looping = false;
			catch_thread();
			Manager::init();
		}
	}
	
	std::cout << "Goodbye" << std::endl;
}



