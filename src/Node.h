#ifndef NODE_H
#define NODE_H
#include "Vector.h"

enum node_type { node_norm, node_goal, node_pred };

class Node {
	public:
		vec pos;
		vec vel;

		Node() : pos(), vel() {} //initialize with zeroes
		Node(vec &p, vec &v) {pos=p; vel=v;}
		Node(dvec &p, dvec &v) : pos(p), vel(v) {}

		std::string toString();
		node_type type;
};

inline double distance(Node &a, Node&b){
	return distance(a.pos, b.pos);
}

#endif

/*
Node
	- Position
	- Velocity
	- Other (goal, type, etc.)?
*/
