#include "Mock3DSensor.h"
#include <math.h>

Mock3DSensor::Mock3DSensor(Motion * x, Motion * c) : xMotion(x), cMotion(c) {
	clock = Clock::getInstance(); 
	maxError = 0.05; // Error of 5 cm 
}; 

Quaternion Mock3DSensor::getApparentPositionOfX() {
	// Use a quaternion to represent X's location. Given vector p = (px, py, pz) the corresponding Quaternion is q = (0, px, py, pz); 
	Quaternion xLocation; 
	
	// Calculate distances based in Global reference frame with origin at Camera WITH UP TO 5cm ERROR
	xLocation.set(0, 
		xMotion->rX() - cMotion->rX() + error(), 
		xMotion->rY() - cMotion->rY() + error(),
		xMotion->rZ() - cMotion->rZ() + error());

	// Rotate global position vector into Camera's reference frame
	Quaternion xLocInCFrame = cMotion->quat.intoBodyFrame(xLocation);

	// Return X's position in Camera's reference frame
	return xLocInCFrame; 
}

pair<Quaternion, double> Mock3DSensor::query3DSensor() {
	// Return data sporadically
	double r = ((double)rand() / (RAND_MAX));	// 0 < r < 1
	if (r < 0.2) {
		pair<Quaternion, double> noResult(getApparentPositionOfX(), clock->getTime());
	}
	else {
		Quaternion empty(0, 0, 0, 0); 
		pair<Quaternion, double> noResult(empty, -1.0); 
		return noResult; 
	}
}

double Mock3DSensor::error() {
	double r = ((double)rand() / (RAND_MAX));	// 0 < r < 1
	r *= 2;										// 0 < r < 2
	r--;										// -1 < r < 1

	double error = r* maxError;	
	return error; 
}

