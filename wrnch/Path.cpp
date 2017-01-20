#include "Path.h"
#include <math.h>

std::vector<double> Path::convertQuaternionForGl() {
	double angle = 2 * acos(quat.w) * 180 / 3.14;
	double s = sqrt(1 - quat.w * quat.w);
	std::vector<double> forGlrotated = { angle, quat.x / s, quat.y / s, quat.z / s };
	return forGlrotated;
}


double Path::wX() { 
	double roll = atan2(2 * (change.w * change.x + change.y * change.z) , 1 - 2 * (change.x * change.x + change.y * change.y)); 
	double angularVel = roll / Clock::increment; 
	return angularVel; 
}

double Path::wY() { 
	double pitch = asin(2 * (change.w*change.y - change.z*change.x)); 
	double angularVelocity = pitch / Clock::increment; 
	return angularVelocity; 
}

double Path::wZ() { 
	double yaw = atan2(2 * (change.w * change.z + change.x * change.y), 1 - 2 * (change.y * change.y + change.z * change.z));
	double angularVelocity = yaw / Clock::increment; 
	return angularVelocity; 
}