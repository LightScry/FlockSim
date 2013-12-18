#ifndef NODE_H
#define NODE_H
#include "Vector.h"

enum node_type { node_norm, node_goal, node_pred };

class Node {
	public:
		vec pos;
		vec vel;
		node_type type;

		Node() : pos(), vel() {type=node_norm;} //initialize with zeroes
		Node(node_type tp) : pos(), vel() {type=tp;} //initialize with zeroes
		Node(vec &p, vec &v) {pos=p; vel=v;}
		Node(vec &p, vec &v, node_type tp) {pos=p; vel=v; type=tp;}
		Node(dvec &p, dvec &v) : pos(p), vel(v) {}
		Node(dvec &p, dvec &v, node_type tp) : pos(p), vel(v) {type=tp;}

		std::string toString();
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
