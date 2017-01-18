#include "OrientationEstimator.h"
#include "MockIMU.h"
#include <math.h>
using std::vector; 

OrientationEstimator::OrientationEstimator(MockIMU * i) : imu(i) {
	 
	//CREATE INITIAL DCM MATRIX DCM = {North, West, Zenith}^T
	// Zenith is opposite of Gravity. Assume other acceleration is small compared to gravity
	Zenith = { -1 * imu->xAcc() , -1 * imu->yAcc(), -1 * imu->zAcc() };
	normalize[Zenith]; 

	// North can be measured by magnetometer. Assume no interference
	North = { imu->mX() , imu->mY() , imu->mZ() }; 
	normalize[North]; 

	// West is the cross product of Zenith and North
	West = crossProduct(Zenith, North); 
	normalize[West]; 

	
}

void OrientationEstimator::normalize(vector<double> & vec) {
	double magnitude = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]); 
	vec[0] /= magnitude; 
	vec[1] /= magnitude; 
	vec[2] /= magnitude; 
}

void OrientationEstimator::orthonormalize(vector<double> &, vector<double> &, vector<double> &) {
	double error = North[0] * West[0] + North[1] * West[1] + North[2] * West[2]; 
	error /= 2; 
	vector<double> newNorth = { North [0] - error * West[0], 
								}
} 

vector<double> OrientationEstimator::crossProduct(vector<double> u, vector<double> v) {
	vector<double> result = {	u[2] * v[3] - u[3] * v[2],
								u[3] * v[1] - u[1] * v[3],
								u[1] * v[2] - u[2] * v[1] };
	return result; 	
}

void OrientationEstimator::updateDCM() {

}