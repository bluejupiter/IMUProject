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
	normalize(Zenith); 

	// North can be measured by magnetometer. Assume no interference
	North = { imu->mX() , imu->mY() , imu->mZ() }; 
	normalize(North); 

	// West is the cross product of Zenith and North
	West = crossProduct(Zenith, North); 
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
	vector<double> result = {	u[2] * v[3] - u[3] * v[2],
								u[3] * v[1] - u[1] * v[3],
								u[1] * v[2] - u[2] * v[1] };
	return result; 	
}

void OrientationEstimator::updateDCM() {
	// Find angular displacement according to the three sensors
	vector<double> accAngle = accelerometerDeltaAngle(); 
	vector<double> gyroAngle = gyroscopeDeltaAngle();
	vector<double> magAngle = magnetDeltaAngle();

	// Combine and weight
	vector<double> angleDisplacement = { accAngle[0] / 3 + gyroAngle[0] / 3 + magAngle[0] / 3,
										accAngle[1] / 3 + gyroAngle[1] / 3 + magAngle[1] / 3,
										accAngle[2] / 3 + gyroAngle[2] / 3 + magAngle[2] / 3 };

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
		q.x = s * (Zenith[1] - West[2]);
		q.y = s * (North[2] - Zenith[0]);
		q.z = s * (West[0] - North[1]);
	}
	else
		std::cout << "Error, DCM trace less than zero"; 

	return q; 
}