#include "MockIMU.h"
#include <random>

MockIMU::MockIMU(Motion * p) : path(p) {}

double MockIMU::error() {
	double r = ((double)rand() / (RAND_MAX));	// 0 < r < 1
	r *= 2;										// 0 < r < 2
	r--;										// -1 < r < 1

	// Return 1% error
	return 1.0 + 0.01*r;
}

double MockIMU::xAcc() {
	return path->xAcc()*error(); 
}

double MockIMU::yAcc() {
	return path->yAcc()*error(); 
}

double MockIMU::zAcc() {
	return path->yAcc()*error(); 
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
	return 0; 
}
double MockIMU::mY() {
	return 0;
}
double MockIMU::mZ() {
	return 0;
}
