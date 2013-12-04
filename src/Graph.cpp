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

void Graph::addNode(vec &pos, vec &vel){
	addNode(Node(pos,vel));
}

void Graph::addNode(dvec &pos, dvec &vel){
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


void Graph::updateVelocities(){
	int numNodes = nodes.size();
	vec* newVelocities = new vec[numNodes];
	
	//first loop through nodes and assign weights
	for (int i=0; i<numNodes; i++){
		for (int j=0; j<numNodes; j++){
			if (i==j)
				edges[i][j]=0;
			else
				edges[i][j]=alg.calcWeight(nodes[i],nodes[j]);
		}
	}

	//now loop through again and calculate new velocity vectors
	for (int i=0; i<numNodes; i++){
		newVelocities[i]=nodes[i].vel;
		vec avgPos;
		double totalWeight;

		for (int j=0; j<numNodes; j++){
			//calculate contribute of node j to the new velocity
			//of node i, based on [i,j] weight and the 
			//separation, cohesion, and cohesion parameters stored
			//in alg
			
			//SEPARATION
			newVelocities[i]+=edges[i][j]*alg.separation*(nodes[i].pos-nodes[j].pos);

			//ALIGNMENT
			newVelocities[i]+=edges[i][j]*alg.alignment*(nodes[j].vel-nodes[i].vel);

			//COHESION
			avgPos+=edges[i][j]*nodes[j].pos;
			totalWeight+=edges[i][j];
		}

		//COHESION, continued
		avgPos/=totalWeight; //weighted average
		newVelocities[i]+=cohesion*(avgPos-nodes[i].pos)
	}

	//now loop through a final time to update velocities
	for (int i=0; i<numNodes; i++){
		nodes[i].vel=newVelocities[i];
	}

	delete[] newVelocities;
}

void Graph::updatePositions(const double& timestep){
	for (int i=0; i<nodes.size(); i++)
		nodes[i].pos+=timestep*nodes[i].vel;
}

void Graph::update(const double& timestep){
	updatePositions(timestep);
	updateVelocities();
}
