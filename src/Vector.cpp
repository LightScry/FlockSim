#include "Vector.h"
#include <math>

vec::vec(const dvec& dv){
	for (int i=0; i<DIMENSION; i++)
		d[i]=dv[i];
}

vec& vec::operator+=(const vec& rhs){
	for (int i=0; i<DIMENSION; i++)
		d[i]+=rhs[i];
	return *this;
}

vec& vec::operator-=(const vec& rhs){
	for (int i=0; i<DIMENSION; i++)
		d[i]-=rhs[i];
	return *this;
}

vec& vec::operator*=(const double& scalar){
	for (int i=0; i<DIMENSION; i++)
		d[i]*=scalar;
	return *this;
}

vec& vec::operator/=(const double& scalar){
	for (int i=0; i<DIMENSION; i++)
		d[i]/=scalar;
	return *this;
}

vec& vec::operator=(const vec& rhs){
	for (int i=0; i<DIMENSION; i++)
		d[i]=rhs[i];
	return *this;
}

double vec::magnitude(){
	double sum = 0;
	for (int i=0; i<DIMENSION; i++){
		sum+=pow(d[i],2);
	}
	return sqrt(sum);
}
