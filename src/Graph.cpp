#include "Graph.h"
#include <cstdlib>

void Graph::init(int numNodes){
	//remove any existing nodes
	nodes.clear();
	
	//add new nodes
	for(int x = 0; x < numNodes; x ++){
		addNode();
	}
}

void Graph::initRandom(int numNodes, unsigned int seed){
	//seed the rand
	srand(seed);
	
	//remove any existing nodes
	nodes.clear();
	
	//add new nodes
	for(int x = 0; x < numNodes; x ++){
		addNodeRandom();
	}
}

void Graph::addNode(Node* n){
	nodes.push_back(n);
	edges.push_back(std::vector<double>());
	
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
	addNode(new Node());
}

void Graph::addNode(vec &pos, vec &vel){
	addNode(new Node(pos,vel));
}

void Graph::addNode(dvec &pos, dvec &vel){
	addNode(new Node(pos,vel));
}

void Graph::addNodeRandom(){
	vec pos;
	vec vel;
	for (int i=0; i<DIMENSION; i++){
		pos[i] = ((double) rand()/RAND_MAX) * POS_BOUND;
		vel[i] = ((double) rand()/RAND_MAX) * POS_BOUND/30 - POS_BOUND/60;
	}
	addNode(new Node(pos,vel));
}

void Graph::removeNode(int index){
	//free memory
	delete nodes[index];
	//remove node
	nodes.erase(nodes.begin() + index);

	//remove edges from nodes[index]
	edges.erase(edges.begin() + index);

	for (int i=0; i<nodes.size(); i++){
		//remove edges to nodes[index]
		edges[i].erase(edges[i].begin() + index);
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
		newVelocities[i]=nodes[i]->vel;
		vec avgPos; //"center of mass"
		vec avgVel; //average velocity
		vec avgDisp;//average displacement (from nodes[i])

		bool separate = false;
		double totalWeight = 0.0;
		double sepWeight = 0.0;
		
		for (int j=0; j<numNodes; j++){
			if (j==i) continue;
			//calculate contribute of node j to the new velocity
			//of node i, based on [i,j] weight and the 
			//separation, cohesion, and cohesion parameters stored
			//in alg

			if ((nodes[i]->pos-nodes[j]->pos).magnitude() < SEPARATION_RADIUS){
				//SEPARATION
				avgDisp+=edges[i][j]*(nodes[i]->pos-nodes[j]->pos);
				sepWeight+=edges[i][j];
				separate=true;
			}
			
					
			//ALIGNMENT
			avgVel+=edges[i][j]*nodes[j]->vel;
			
			//COHESION
			avgPos+=edges[i][j]*nodes[j]->pos;
	
			//weighting
			totalWeight+=edges[i][j];
		}

		//algorithm, continued
		if (totalWeight > 0.0){
			//weighted averages
			avgPos/=totalWeight;
			avgVel/=totalWeight;

			if (separate){
				avgDisp/=sepWeight;
				newVelocities[i]+=alg.separation*avgDisp;
			}
			//else {
				newVelocities[i]+=alg.cohesion*(avgPos-nodes[i]->pos);
				newVelocities[i]+=alg.alignment*avgVel;
			//}
			
			//normalize to maximum speed (if needed)
			double mag = newVelocities[i].magnitude();
			if (mag > MAX_SPEED)
				newVelocities[i]*=(MAX_SPEED/mag);
		}
	}

	//now loop through a final time to update velocities
	for (int i=0; i<numNodes; i++){
		nodes[i]->vel=newVelocities[i];
	}

	delete[] newVelocities;
}

void Graph::updatePositions(double timestep){
	for (int i=0; i<nodes.size(); i++){
		nodes[i]->pos+=timestep*nodes[i]->vel;

		//bound-checking
		for (int j=0; j<DIMENSION; j++){
			if (nodes[i]->pos[j] > POS_BOUND){
				//Periodic boundary (wrapping)
				if (PERIODIC_BOUNDARIES){
					nodes[i]->pos[j]-=POS_BOUND;
				}
				
				//Reflective boundary
				else {
					//reflect
					nodes[i]->vel[j]=-nodes[i]->vel[j];
					//kick away
					nodes[i]->pos[j]-=POS_BOUND/200.0;
				}
			}
			if (nodes[i]->pos[j] < 0.0){
				//Periodic boundary (wrapping)
				if (PERIODIC_BOUNDARIES){
					nodes[i]->pos[j]+=POS_BOUND;
				}
				
				//Reflective boundary
				else {
					//reflect
					nodes[i]->vel[j]=-nodes[i]->vel[j];
					//kick away
					nodes[i]->pos[j]+=POS_BOUND/200.0;
				}
			}
		}
	}
}

void Graph::update(double timestep){
	updatePositions(timestep);
	updateVelocities();
}

void Graph::updateRandomMove(unsigned int seed){
	srand(seed);

	for (Node* n : nodes){
		int randNum1 = rand() % 4 + 1 - 2;
		int randNum2 = rand() % 4 + 1 - 2;
		n->pos[0] += randNum1;
		n->pos[1] += randNum2;

		if (n->pos[0] > POS_BOUND || n->pos[0] < 0)
			n->pos[0] = POS_BOUND/2;
		if (n->pos[1] > POS_BOUND || n->pos[1] < 0)
			n->pos[1] = POS_BOUND/3;
	}
}

void Graph::writeNodes(std::string filename){
	std::ofstream myfile;
	myfile.open(filename);
	for (Node* n : nodes){
		myfile << n->toString() << "|";
	}
	myfile.close();
}
