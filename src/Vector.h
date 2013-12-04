#ifndef VECTOR_H
#define VECTOR_H
#define DIMENSION 3

//useful to typedef this for cleaner passing/returning by reference
typedef double dvec[DIMENSION];

class vec {
	dvec d;
	public:
		//CONSTRUCTORS
		vec() : d() {} //initialize with zeroes
		vec(const dvec& dv); //initialize from 3-array of doubles
		
		//OPERATORS
		vec& operator+=(const vec& rhs);
		vec& operator-=(const vec& rhs);
		vec& operator*=(const double& scalar);
		vec& operator/=(const double& scalar);
		vec& operator=(const vec& rhs);
		float& operator[](int index) {return d[index];}
		float operator[](int index) const {return d[index];}

		//MATH
		double magnitude();
}

inline vec operator+(vec lhs, const vec& rhs){
	lhs += rhs;
	return lhs;
}

inline vec operator-(vec lhs, const vec& rhs){
	lhs -= rhs;
	return lhs;
}

inline vec operator*(vec lhs, const double& scalar){
	lhs *= scalar;
	return lhs;
}

inline vec operator*(const double& scalar, vec rhs){
	rhs *= scalar;
	return rhs;
}

inline vec operator/(vec lhs, const double& scalar){
	lhs /= scalar;
	return lhs;
}

double distance(const vec& lhs, const vec& rhs){
	return magnitude(lhs-rhs);
}

#endif
