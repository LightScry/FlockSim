#include "Graph.h"

// Initialize
std::vector<Node *> Graph::nodes;
std::vector< std::vector<int> > Graph::edges;

int NUM_NODES = 50;

void Graph::init(){
	Graph::nodes.clear();
	
	Node *newNode;
	for(int x = 0; x < NUM_NODES; x ++){
		fvec t_pos;
		fvec t_vel;
		newNode = new Node();
		Graph::nodes.push_back( newNode );
	}
}

void Graph::update(){
	for(Node *n : Graph::nodes){
		n->pos[0] += 0;
	}
}

// Will not be used yet
void Graph::updateLocal(int a, int b){
	
}