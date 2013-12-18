#include "Graph.h"
#include <cstdlib>
#include <iostream>
#include <math.h>

void Graph::init(int numNodes){
	//remove any existing nodes
	nodes.clear();
	
	//add new nodes
	for(int x = 0; x < numNodes; x ++){
		addNode(node_norm);
	}
	
	Node *targetNode = new Node();
}

void Graph::initRandom(int numNodes, unsigned int seed){
	//seed the rand
	srand(seed);
	
	//remove any existing nodes
	nodes.clear();
	
	//add new nodes
	for(int x = 0; x < numNodes; x ++){
		addNodeRandom(node_norm);
	}
	
	// add target node
	/*Node *targetNode = newNodeRandom(node_goal);
	for(int i = 0;i < DIMENSION; i ++)
		targetNode->vel[i] = 0;
	addNode(targetNode);
	
	addNodeRandom(node_goal);

	// add predator node
	addNodeRandom(node_pred);
	addNodeRandom(node_pred);*/
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

void Graph::addNode(node_type type){
	Node *node = new Node(type);
	addNode(node);
}

void Graph::addNode(vec &pos, vec &vel, node_type type){
	addNode(new Node(pos,vel,type));
}

void Graph::addNode(dvec &pos, dvec &vel, node_type type){
	addNode(new Node(pos,vel,type));
}

Node *Graph::newNodeRandom(node_type type){
	vec pos;
	vec vel;
	for (int i=0; i<DIMENSION; i++){
		pos[i] = ((double) rand()/RAND_MAX) * POS_BOUND;
		vel[i] = ((double) rand()/RAND_MAX) * POS_BOUND/30 - POS_BOUND/60;
	}
	Node* newNode = new Node(pos,vel,type);
	return newNode;
}

void Graph::addNodeRandom(node_type type){
	addNode(Graph::newNodeRandom(type));
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
	std::vector<int> removeNodes;
	
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
		vec avgFlee; //run away from the predator(s)!

		
		
	    double goalWeight = 1.0;
		double totalWeight = 0.0;
		double sepWeight = 0.0;
		double fleeWeight = 0.0;

		for (int j=0; j<numNodes; j++){
			if (j==i) continue;
			
			//do we need to run away?
			if (nodes[j]->type==node_pred){
				//are we eaten?
				if (nodes[i]->type==node_norm)
					if ((nodes[i]->pos-nodes[j]->pos).magnitude() < EAT_RADIUS){
						removeNodes.push_back(i);
					}
				avgFlee+=edges[i][j]*(nodes[i]->pos-nodes[j]->pos);
				fleeWeight+=edges[i][j];
				continue;
			}


			//calculate contribute of node j to the new velocity
			//of node i, based on [i,j] weight and the 
			//separation, cohesion, and cohesion parameters stored
			//in alg

			if ((nodes[i]->pos-nodes[j]->pos).magnitude() < SEPARATION_RADIUS){
				//SEPARATION
				avgDisp+=edges[i][j]*(nodes[i]->pos-nodes[j]->pos);
				sepWeight+=edges[i][j];
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

			//predator movement
			if (nodes[i]->type==node_pred){
				newVelocities[i]+=alg.cohesion*30.0*(avgPos-nodes[i]->pos);
				normToMax(newVelocities[i], MAX_SPEED*2);
			}

			//prey movement
			else if (nodes[i]->type==node_norm){
				//predator-fleeing
				if (fleeWeight > 0.0){
					avgFlee/=fleeWeight;
					newVelocities[i]+=alg.flee*avgFlee;
				}
				//separation
				if (sepWeight > 0.0){
					avgDisp/=sepWeight;
					newVelocities[i]+=alg.separation*avgDisp;
				}
				//cohesion and alignment
				newVelocities[i]+=alg.cohesion*(avgPos-nodes[i]->pos);
				newVelocities[i]+=alg.alignment*avgVel;
				//goal-seeking (avg path to goal with no-goal path)
				
				Node *closestNode = findClosestGoal(nodes[i]);
				if( closestNode != NULL )
					newVelocities[i]+=alg.cohesion*(closestNode->pos - avgPos) * goalWeight;
				if (newVelocities[i].magnitude() > MAX_SPEED)
					normToMax(newVelocities[i], MAX_SPEED);
			}
		}
	}

	//now loop through a final time to update velocities
	for (int i=0; i<numNodes; i++){
		nodes[i]->vel=newVelocities[i];
	}
	
	// Remove marked nodes
	int offset = 0;
	for(int x = 0; x < removeNodes.size(); x ++){
		removeNode(removeNodes[x] - offset);
		numNodes--;
		offset++;
	}
	

	delete[] newVelocities;
}

Node *Graph::findClosestGoal(Node *node){
	Node *closestGoal = NULL;
	for(int x = 0; x < nodes.size(); x ++){
		if( nodes[x]->type == node_goal ){
			double newDist = distance(*node,*nodes[x]);
			if(closestGoal == NULL || newDist < distance(*node,*closestGoal))
				closestGoal = nodes[x];
		}
	}
	
	return closestGoal;
}

void Graph::normToMax(vec& v, double max){
	v*=(max/v.magnitude());
}

void Graph::updatePositions(double timestep){
	//Node* targetNode = nodes[nodes.size()-1];
	//std::cout << "TARGET NODE:" << targetNode->pos[0] << "," << targetNode->pos[1] << std::endl;
	for (int i=0; i<nodes.size(); i++){
		if(nodes[i]->type == node_goal)	continue;	
		
		nodes[i]->pos+=timestep*nodes[i]->vel;
		
		//bound-checking
		for (int j=0; j<DIMENSION; j++){
			// Skip goal node
			if (nodes[i]->type == node_goal)
				continue;
			
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
	std::vector<Node*> targetNodes;
	std::vector<Node*> predatorNodes;
	
	// Pring & Organize
	for (Node *n : nodes){
		if(n->type == node_norm)
			myfile << n->toString() << "|";
		else if(n->type == node_goal)
			targetNodes.push_back(n);
		else if(n->type == node_pred)
			predatorNodes.push_back(n);
	}
	
	// Print goals
	myfile << "@"; // ^ is the separator here
	for(Node *n : targetNodes){
		myfile << n->toString() << "|";
	}
	
	// Print goals
	myfile << "@"; // ^ is the separator here
	for(Node *n : predatorNodes){
		myfile << n->toString() << "|";
	}
	
	
	myfile.close();
}
