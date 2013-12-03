#ifndef NODE_H
#define NODE_H
#define DIMENSION 3 //number of dimensions through which to move
#define MAXPOS 100 //arbitrary choice for size of our space

//makes passing/returning these cleaner
typedef float fvec[DIMENSION];

class Node {
	public:
		float pos[DIMENSION];
		float vel[DIMENSION];

		Node() : pos(), vel() {} //initialize with zeroes
		Node(fvec &p, fvec &v);
};

#endif

/*
Node
	- Position
	- Velocity
	- Other (goal, type, etc.)?
*/
