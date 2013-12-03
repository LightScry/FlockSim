#ifndef ALGO_H
#define ALGO_H
#include "Node.h"

class Algo {
	float separation;
	float cohesion;
	float alignment;
	public:
		Algo() : separation(), cohesion(), alignment() {}
		Algo(float sep, float coh, float ali) : separation(sep), cohesion(coh), alignment (ali) {}
		float calcWeight(Node &a, Node &b);
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
