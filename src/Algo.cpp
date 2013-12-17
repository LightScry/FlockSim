#include "Algo.h"
#include <cmath>

double Algo::calcWeight(Node* a, Node* b){
	return calcWeightVs(a,b);
}

double Algo::calcWeightSq(Node* a, Node* b){
	//inversely proportional to distance squared
	//damping is better this way than with simple inverse
	double dist = distance(a->pos, b->pos);
	if (dist==0.0)
		return 0.0;
	else {
		if (a->type==node_pred)
			return 3.0 / pow(dist,2);
		else
			return 1.0 / pow(dist,2);
	}
}

double Algo::calcWeightVs(Node* a, Node* b){
	double sight_radius = VISION_RADIUS;
	if (a->type==node_pred) sight_radius*=3;
	if (distance(a->pos, b->pos)>sight_radius)
		return 0.0;
	else
		return 1.0;
}
