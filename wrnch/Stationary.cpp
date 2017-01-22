#include "Stationary.h"

Stationary::Stationary() {
	quat.set(1, 0, 0, 0); // w,x,y,z
	change.set(0, 1.0, 0, 0); 
};

double Stationary::rX() { return 3; };
double Stationary::rY() { return 0; };
double Stationary::rZ() { return 1; };

double Stationary::xAcc() { return gravityX(); };
double Stationary::yAcc() { return gravityY(); };
double Stationary::zAcc() { return gravityZ(); };

void Stationary::update() {
	// do nothing
};