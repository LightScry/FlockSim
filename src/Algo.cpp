#include "Algo.h"

double Algo::calcWeight(Node &a, Node &b){
	//inversely proportional to distance squared
	//damping is better this way than with simple inverse
	return 1.0 / pow(distance(a.pos, b.pos),2);
}
