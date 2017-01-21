#pragma once
#include <string>

class Quaternion {
public:
	double x; 
	double y; 
	double z; 
	double w; // Rotation about vector pointed by x,y,z

 
	Quaternion() : w(1.0), x(0), y(0), z(0) {};
	Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {};
	void normalize(); 
	Quaternion& multiply(const Quaternion&); 
	void set(double w, double x, double y, double z); 
	std::string toString(); 
	Quaternion& conjugate(Quaternion&); 

};