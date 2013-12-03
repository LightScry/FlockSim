#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"
#include <vector>
class Graph {
	//xAlgo alg;
	public:
		//could switch to fixed arrays if we want to
		static std::vector<Node *> nodes;
		static std::vector<std::vector<int> > edges;
		static void init();
		static void update();
		static void updateLocal(int a, int b);
};
#endif

/*
Graph
	- Node Set
	- 2D Array  (Edges)
	+ Update [Clock Tick]
		- Should the computations go here or in Algo?
		- Global
			- Compute Alignment
			- Compute Cohesion
			- Compute Separation
			- Set Position
		- Local (between any 2 nodes)
			- Compute Alignment
			- Compute Cohesion 
			- Compute Separation
			- Set Edge Weights
*/
