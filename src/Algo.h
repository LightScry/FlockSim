#ifndef ALGO_H
#define ALGO_H
#include "Node.h"

class Algo { 
	public:
		double separation;
		double cohesion;
		double alignment;

		Algo() : separation(), cohesion(), alignment() {}
		Algo(double sep, double coh, double ali) : separation(sep), cohesion(coh), alignment (ali) {}
		double calcWeight(Node* a, Node* b);
};

#endif

/*
Algo
	- Params
	* We could use this as an abstract class:
       		- update(Graph g)
		* children implement different flocking algorithms
		* this would mean Graph is basically just a data structure
*/
