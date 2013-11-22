#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Node.h"
#include "Algo.h"

class Graph {
	Algo alg;

	//could switch to fixed arrays if we want to
	std::vector<Node> nodes;
	std::vector<std::vector<float> > edges;
	//edges[a][b] is the weight from nodes[a] to nodes[b]

	void addNode();
	void addNode(Node &n);
	void addNode(fvec &pos, fvec &vel);

	public:
		Graph() : alg() {}
		Graph(float sep, float coh, float ali) : alg(sep,coh,ali) {}

		void update();
		void updateLocal(int a, int b);
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
