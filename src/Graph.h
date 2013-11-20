#include "Node.h"

class Graph {
	Algo alg;
	//could switch to fixed arrays if we want to
	std::vector<Node> nodes;
	std::vector<std::vector<int> > edges;
	public:
		void update();
		void updateLocal(int a, int b);
};

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
