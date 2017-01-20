#include "Path.h"

std::vector<double> Path::convertQuaternionForGl() {
	double angle = 2 * acos(quat.w) * 180 / 3.14;
	double s = sqrt(1 - quat.w * quat.w);
	std::vector<double> forGlrotated = { angle, quat.x / s, quat.y / s, quat.z / s };
	return forGlrotated;
}

double Path::wX() { return 0; }
double Path::wY() { return 0; }
double Path::wZ() { return 0; }