#include "Algo.h"
#include <cmath>

double Algo::calcWeight(Node* a, Node* b){
	//inversely proportional to distance squared
	//damping is better this way than with simple inverse
	double dist = distance(a->pos, b->pos);
	if (dist==0.0)
		return 0.0;
	else
		return 1.0 / pow(dist,2);
}