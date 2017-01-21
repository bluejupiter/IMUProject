#include "Quaternion.h"
#include <math.h>

void Quaternion::normalize() {
	double magnitudeSquared = w*w + x*x + y*y + z*z; 
	if (1.001 < magnitudeSquared || 0.999 > magnitudeSquared) {
		double magnitude = sqrt(magnitudeSquared); 
		w /= magnitude; 
		x /= magnitude; 
		y /= magnitude; 
		z /= magnitude; 
	}
}

Quaternion & Quaternion::multiply(const Quaternion & q2)
{
	double wNew = w*q2.w - x*q2.x - y*q2.y - z*q2.z;
	double xNew = w*q2.x + x*q2.w + y*q2.z - z*q2.y; 
	double yNew = w*q2.y - x*q2.z + y*q2.w + z*q2.x; 
	double zNew = w*q2.z + x*q2.y - y*q2.x + z*q2.w; 
	Quaternion result(wNew, xNew, yNew, zNew); 
	return result; 
}

void Quaternion::set(double wNew, double xNew, double yNew, double zNew) {
	w = wNew; x = xNew; y = yNew; z = zNew;
};

std::string Quaternion::toString() {
	std::string output = "(" + std::to_string(w) + ", " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")\n"; 
	return output; 
}

Quaternion& Quaternion::conjugate(Quaternion& vector) {
	Quaternion inverse(w, -1 * x, -1 * y, -1 * z); 
	Quaternion result = vector.multiply(inverse);
	result = this->multiply(result); 
	return result; 
}

