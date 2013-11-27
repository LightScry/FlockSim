#include "Graph.h"

void Graph::addNode(Node &n){
	nodes.push_back(n);
	edges.push_back(std::vector<float>());
	
	int index = nodes.size()-1;
	
	//set weights from new node to and from others
	for (int i=0; i<index+1; i++){
		//from new node (to ith node)
		edges[index].push_back(alg.calcWeight(nodes[index],nodes[i]));
	}
	
	for (int i=0; i<index; i++){
		//to new node (from ith node)
		edges[i].push_back(alg.calcWeight(nodes[i],nodes[index]));
	}
}

void Graph::addNode(){
	addNode(Node());
}

void Graph::addNode(fvec &pos, fvec &vel){
	addNode(Node(pos,vel));
}

void Graph::removeNode(int index);
	//remove edges from nodes[index]
	edges.erase[index];	

	for (int i=0; i<nodes.size(); i++){
		//remove edges to nodes[index]
		edges[i].erase(index);
	}
}
