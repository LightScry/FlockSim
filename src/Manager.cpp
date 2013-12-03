#include "Manager.h"
#include "Graph.h"

#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
typedef std::chrono::milliseconds milliseconds;

// Static initialization
int Manager::CurrentAlignment = 0;
int Manager::CurrentSeperation = 0;
int Manager::CurrentCohesion = 0;

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
		std::cout << "-------" << std::endl << "Tick:" << tick << std::endl;
		
		writeNodes();
		
		// Update all Managers once per tick
		Manager::update();
	}
}

void Manager::update(){
	printf( "Updating Manager...\n" );
	Graph::update();
}

void Manager::init(){
	printf( "Manager init...\n" );
	Graph::init();
	Manager::gameLoop();
}

void Manager::writeNodes(){
	//printf("Writing...");
	std::ofstream myfile;
	myfile.open ("node_data.json");
	myfile << "{ \"nodes\":[" << std::endl;
	for( Node *n : Graph::nodes ){
		myfile << Manager::nodeToString(n) << std::endl;
	}
	myfile << "]}";
	myfile.close();
}

std::string Manager::nodeToString(Node * n){
	std::stringstream ss;
	//ss << "\"node\":{";
	ss << "{\"pos\":[" << n->pos[0] << "," << n->pos[1] << "]},";
	//ss << "},";
	
	std::string retString;
	ss >> retString;
	return retString;
}
