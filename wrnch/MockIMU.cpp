#include "MockIMU.h"
#include <random>

MockIMU::MockIMU(Motion * p) : path(p) {
	northGlobalFrame.set(0, 1, 0, 0); // Represent north as unit vector (in quaternion format) pointing to x
}

double MockIMU::error() {
	/*
	double r = ((double)rand() / (RAND_MAX));	// 0 < r < 1
	r *= 2;										// 0 < r < 2
	r--;										// -1 < r < 1

	// Return 1% error
	return 1.0 + 0.01*r;
	*/

	return 1.0; // Start with no error
}

double MockIMU::xAcc() {
	return path->xAcc()*error(); 
}

double MockIMU::yAcc() {
	return path->yAcc()*error(); 
}

double MockIMU::zAcc() {
	return path->zAcc()*error(); 
}

double MockIMU::wX() {
	return path->wX()*error(); 
}
double MockIMU::wY() {
	return path->wY()*error(); 
}

double MockIMU::wZ() {
	return path->wZ()*error(); 
}

// STUBS - Fix when quaternion math is figured out
double MockIMU::mX() {
	Quaternion north = path->quat.conjugate(northGlobalFrame); 

	//Get x component of north quaternion
	double s = sqrt(1 - north.w*north.w); 
	return north.x / s * error(); 
}
double MockIMU::mY() {
	Quaternion north = path->quat.conjugate(northGlobalFrame);

	//Get y component of north quaternion
	double s = sqrt(1 - north.w*north.w);
	return north.y / s * error();
}
double MockIMU::mZ() {
	Quaternion north = path->quat.conjugate(northGlobalFrame);

	//Get z component of north quaternion
	double s = sqrt(1 - north.w*north.w);
	return north.z / s * error();
}
