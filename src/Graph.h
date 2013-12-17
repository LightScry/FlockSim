#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"
#include "Vector.h"
#include "Algo.h"
#include <fstream>
#include <vector>
#define POS_BOUND 500.0
#define MAX_SPEED POS_BOUND/10.0
#define PERIODIC_BOUNDARIES true 

class Graph {
	Algo alg;

	std::vector<Node*> nodes;
	std::vector<std::vector<double> > edges;
	//edges[a][b] is the weight of nodes[b] as seen by nodes[a]

	void updateVelocities();
	void updatePositions(double timestep);

	public:
		Graph() : alg() {}
		Graph(double sep, double coh, double ali) : alg(sep,coh,ali) {}
		Graph(int numNodes) : alg() {init(numNodes);}
		Graph(int numNodes, double sep, double coh, double ali) : alg(sep,coh,ali) {init(numNodes);}
		Graph(int numNodes, double sep, double coh, double ali, unsigned int seed) : alg(sep,coh,ali) {initRandom(numNodes,seed);}

		void init(int numNodes);
		void initRandom(int numNodes, unsigned int seed);
		
		void addNode();
		void addNode(Node* n);
		void addNode(vec &pos, vec &vel);
		void addNode(dvec &pos, dvec &vel);
		void addNodeRandom();
		void removeNode(int index);
	
		void update(double timestep);
		void updateRandomMove(unsigned int seed);

		void writeNodes(std::string filename);
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
