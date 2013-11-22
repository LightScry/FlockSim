#include "Graph.h"

void Graph::addNode(Node &n){
	nodes.push_back(n);
	edges.push_back(std::vector<float>());

	int index = nodes.size()-1;

	for (int i=0; i<index+1; i++){
		//set weights from new node to and from others
		//to new node (from ith node)
		edges[i].push_back(alg.calcWeight(nodes[i],nodes[index]));
		//from new node (to ith node)
		edges[index].push_back(alg.calcWeight(nodes[index],nodes[i]));
	}
}

void Graph::addNode(){
	addNode(Node());
}

void Graph::addNode(fvec &pos, fvec &vel){
	addNode(Node(pos,vel));
}
