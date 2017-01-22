#include "Stationary.h"

Stationary::Stationary(double x, double y, double z) : Motion(x, y, z) {
	quat.set(1, 0, 0, 0); // w,x,y,z
	change.set(0, 1.0, 0, 0); 
};

double Stationary::rX() { return xOffset; };
double Stationary::rY() { return yOffset; };
double Stationary::rZ() { return zOffset; };

double Stationary::xAcc() { return gravityX(); };
double Stationary::yAcc() { return gravityY(); };
double Stationary::zAcc() { return gravityZ(); };

void Stationary::update() {
	// do nothing
};