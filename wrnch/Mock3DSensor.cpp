#include "Mock3DSensor.h"

Mock3DSensor::Mock3DSensor(Motion * x, Motion * c) : xMotion(x), cMotion(c) {}; 

Quaternion Mock3DSensor::getApparentPositionOfX() {
	// Use a quaternion to represent X's location. Given vector p = (px, py, pz) the corresponding Quaternion is q = (0, px, py, pz); 
	Quaternion xLocation; 
	
	// Calculate distances based in Global reference frame with origin at Camera
	xLocation.set(0, xMotion->rX() - cMotion->rX(), xMotion->rY() - cMotion->rY(), xMotion->rZ() - cMotion->rZ());

	// Rotate global position vector into Camera's reference frame
	Quaternion xLocInCFrame = cMotion.quat.conjugate(xLocation); 

	// Return X's position in Camera's reference frame
	return xLocInCFrame; 
}