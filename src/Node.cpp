#include "Node.h"

Node::Node(fvec &p, fvec &v){
	for (int i=0; i<DIMENSION; i++){
		pos[i]=p[i];
		vel[i]=v[i];	
	}
}
