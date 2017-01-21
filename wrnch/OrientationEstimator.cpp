#include "OrientationEstimator.h"
#include "MockIMU.h"
#include <math.h>
#include <iostream>
#include "Clock.h"
using std::vector; 

OrientationEstimator::OrientationEstimator(MockIMU * i) : imu(i) {
	timeIncrement = Clock::increment; 

	//CREATE INITIAL DCM MATRIX DCM = {North, West, Zenith}^T
	// Zenith is opposite of Gravity. Assume other acceleration is small compared to gravity
	Zenith = { -1 * imu->xAcc() , -1 * imu->yAcc(), -1 * imu->zAcc() };
	std::cout << "\nIn constructor. Zenith is [" + std::to_string(Zenith[0]) + "] [" + std::to_string(Zenith[1]) + "] [" + std::to_string(Zenith[2]) + "]";
	normalize(Zenith); 

	// North can be measured by magnetometer. Assume no interference
	North = { imu->mX() , imu->mY() , imu->mZ() }; 
	std::cout << "\nIn constructor. North is [" + std::to_string(North[0]) + "] [" + std::to_string(North[1]) + "] [" + std::to_string(North[2]) + "]";
	normalize(North); 

	// West is the cross product of Zenith and North
	West = crossProduct(Zenith, North); 
	std::cout << "\nIn constructor. West is [" + std::to_string(West[0]) + "] [" + std::to_string(West[1]) + "] [" + std::to_string(West[2]) + "]\n";
	normalize(West); 

	orthonormalizeDCM(); 
}

void OrientationEstimator::normalize(vector<double> & vec) {
	double magnitude = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]); 
	vec[0] /= magnitude; 
	vec[1] /= magnitude; 
	vec[2] /= magnitude; 
}

// Might want to make "North" the cross product of West and Zenith potentially (to correct for angle) OR make West the new result since
// we may not want to mess with gravity or magnetic north
void OrientationEstimator::orthonormalizeDCM() {
	double error = North[0] * West[0] + North[1] * West[1] + North[2] * West[2]; 
	error /= 2; 

	vector<double> newNorth = { North[0] - error * West[0],
								North[1] - error * West[1],
								North[2] - error * West[2] }; 
	normalize(newNorth); 
	vector<double> newWest = {	West[0] - error * North[0],
								West[1] - error * North[1],
								West[2] - error * North[2] }; 
	normalize(newWest); 

	North = newNorth; 
	West = newWest; 
	Zenith = crossProduct(North, West); 
} 

vector<double> OrientationEstimator::crossProduct(vector<double> u, vector<double> v) {
	vector<double> result = {	u[1] * v[2] - u[2] * v[1],
								u[2] * v[0] - u[0] * v[2],
								u[0] * v[1] - u[1] * v[0] };
	return result; 	
}

void OrientationEstimator::updateDCM() {
	// Weighting from three different inputs
	double accWeight = 0; 
	double gyroWeight = 1; 
	double magWeight = 0;

	// Find angular displacement according to the three sensors
	vector<double> accAngle = accelerometerDeltaAngle(); 
	vector<double> gyroAngle = gyroscopeDeltaAngle();
	vector<double> magAngle = magnetDeltaAngle();

	// Combine and weight
	vector<double> angleDisplacement = {accAngle[0] * accWeight + gyroAngle[0] * gyroWeight + magAngle[0] * magWeight,
										accAngle[1] * accWeight + gyroAngle[1] * gyroWeight + magAngle[1] * magWeight,
										accAngle[2] * accWeight + gyroAngle[2] * gyroWeight + magAngle[2] * magWeight };

	//Update DCM
	vector<double> NorthChange = crossProduct(angleDisplacement, North); 
	North = { North[0] + NorthChange[0], North[1] + NorthChange[1], North[2] + NorthChange[2] }; 

	vector<double> WestChange = crossProduct(angleDisplacement, West); 
	West = { West[0] + WestChange[0], West[1] + WestChange[1], West[2] + WestChange[2] }; 

	vector<double> ZenithChange = crossProduct(angleDisplacement, Zenith); 
	Zenith = { Zenith[0] + ZenithChange[0], Zenith[1] + ZenithChange[1], Zenith[2] + ZenithChange[2] }; 

	orthonormalizeDCM(); 
}

vector<double> OrientationEstimator::accelerometerDeltaAngle() {
	vector<double> newZenith = { -1 * imu->xAcc() , -1 * imu->yAcc(), -1 * imu->zAcc() };
	normalize(newZenith); 

	vector<double> diff = { Zenith[0] - newZenith[0],
							Zenith[1] - newZenith[1],
							Zenith[2] - newZenith[2]};

	vector<double> deltaAngle = crossProduct(Zenith, diff); 
	return deltaAngle; 
}

vector<double> OrientationEstimator::gyroscopeDeltaAngle() {
	vector<double> deltaAngle = { timeIncrement * imu->wX(),
									timeIncrement * imu->wY(),
									timeIncrement * imu->wZ() }; 
	return deltaAngle; 
}

vector<double> OrientationEstimator::magnetDeltaAngle() {
	vector<double> newNorth = { imu->mX() , imu->mY() , imu->mZ() };
	normalize(newNorth);

	vector<double> diff = { North[0] - newNorth[0],
							North[1] - newNorth[1],
							North[2] - newNorth[2] }; 
	vector<double> deltaAngle = crossProduct(North, diff); 
	return deltaAngle; 
}

Quaternion OrientationEstimator::getQuaternion() {
	Quaternion q; 
	
	double DCMTrace = North[0] + West[1] + Zenith[2]; 
	if (DCMTrace > 0) {
		double s = 0.5 / sqrt(DCMTrace + 1.0);
		q.w = 0.25 / s;
		q.x = s * - (Zenith[1] - West[2]);
		q.y = s * - (North[2] - Zenith[0]);
		q.z = s * - (West[0] - North[1]);
	}
	else {
		if (North[0] > West[1] && North[0] > Zenith[2]) {
			double s = 2.0 * sqrt(1.0 + North[0] - West[1] - Zenith[2]); 
			q.w = - (Zenith[1] - West[2]) / s; 
			q.x = 0.25 * s; 
			q.y = - (North[1] + West[0]) / s; 
			q.z = - (North[2] + Zenith[0]) / s; 
		}
		else if (West[1] > Zenith[2]) {
			double s = 2.0 * sqrt(1.0 + West[1] - North[0] - Zenith[2]); 
			q.w = - (North[2] - Zenith[0]) / s; 
			q.x = - (North[1] + West[0]) / s; 
			q.y = 0.25 * s; 
			q.z = - (West[2] + Zenith[1]) / s; 
		}
		else {
			double s = 2.0 * sqrt(1.0 + Zenith[2] - North[0] - West[1]); 
			q.w = - (West[0] - North[1]) / s;
			q.x = - (North[2] + Zenith[0]) / s; 
			q.y = - (West[2] + Zenith[1]) / s; 
			q.z = 0.25 * s; 
		}
	}

	return q; 
}

string OrientationEstimator::getNorth() {
	return "[" + std::to_string(North[0]) + "] [" + std::to_string(North[1]) + "] [" + std::to_string(North[2]) + "]"; 
}

string OrientationEstimator::getWest() {
	return "[" + std::to_string(West[0]) + "] [" + std::to_string(West[1]) + "] [" + std::to_string(West[2]) + "]";
}

string OrientationEstimator::getZenith() {
	return "[" + std::to_string(Zenith[0]) + "] [" + std::to_string(Zenith[1]) + "] [" + std::to_string(Zenith[2]) + "]";
}