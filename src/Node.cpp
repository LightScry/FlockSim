#include "Node.h"

Node::Node(){
	for (int i=0; i<DIMENSION; i++){
		pos[i]=0;
		vel[i]=0;
	}
}

