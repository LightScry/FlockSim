#include "Manager.h"
#include "Graph.h"

#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h> 
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


void moveNodesRandomly(){
	
	srand (time(NULL));
   /* generate secret number between 1 and 10: */
	for( Node *n : Graph::nodes ){
		int randNum1 = rand() % 4 + 1 - 2;
		int randNum2 = rand() % 4 + 1 - 2;
		n->pos[0] += randNum1;
		n->pos[1] += randNum2;
		
		if( n->pos[0] > 500 ||  n->pos[0] < 0)
			n->pos[0] = 250;
		else if( n->pos[1] > 500 ||  n->pos[1] < 0 )
			n->pos[1] = 200;
	}
}

void Manager::update(){
	printf( "Updating Manager...\n" );
	Graph::update();
	moveNodesRandomly();
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
	for( Node *n : Graph::nodes ){
		myfile << Manager::nodeToString(n);
	}
	myfile.close();
}

std::string Manager::nodeToString(Node * n){
	std::stringstream ss;
	ss << n->pos[0] << "," << n->pos[1] << "|";
	
	std::string retString;
	ss >> retString;
	return retString;
}
