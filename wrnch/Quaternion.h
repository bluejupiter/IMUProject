#pragma once

class Quaternion {

	double x; 
	double y; 
	double z; 
	double w; // Rotation about vector pointed by x,y,z

public: 
	Quaternion() : x(0), y(0), z(0), w(1.0) {}; 
	Quaternion(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {};
	void normalize(); 
	Quaternion& operator * (const Quaternion&); 

};