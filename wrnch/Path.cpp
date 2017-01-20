#include "Path.h"
#include <math.h>
#include <iostream>

std::vector<double> Path::convertQuaternionForGl() {
	double angle = 2 * acos(quat.w) * 180 / 3.14;
	double s = sqrt(1 - quat.w * quat.w);
	std::vector<double> forGlrotated = { angle, quat.x / s, quat.y / s, quat.z / s };
	return forGlrotated;
}


double Path::wX() { 
	double term1 = 2 * (change.w * change.x + change.y * change.z);
	double term2 = 1 - 2 * (change.x * change.x + change.y * change.y);

	double roll = atan2(term1, term2); 
	double angularVel = roll / Clock::increment; 

	return angularVel; 
}

double Path::wY() { 
	double term = 2 * (change.w*change.y - change.z*change.x);

	double pitch = asin(term); 
	double angularVelocity = pitch / Clock::increment; 

	return angularVelocity; 
}

double Path::wZ() { 
	double term1 = 2 * (change.w * change.z + change.x * change.y);
	double term2 = 1 - 2 * (change.y * change.y + change.z * change.z);

	double yaw = atan2(term1,term2);
	double angularVelocity = yaw / Clock::increment; 

	return angularVelocity; 
}