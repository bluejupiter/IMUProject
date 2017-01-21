#pragma once
#include "MockIMU.h"
#include "Quaternion.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class OrientationEstimator {
	MockIMU * imu;
	vector<double> North;          // First row of DCM matrix. "North" in the body frame
	vector<double> West;			// Second row of DCM matrix. "West" in the body frame
	vector<double> Zenith;			// Third row of DCM matrix. "Zenith" in the body frame
	double timeIncrement;

public:
	OrientationEstimator(MockIMU * i);
	void normalize(vector<double> &);
	void orthonormalizeDCM();
	vector<double> crossProduct(vector<double>, vector<double>);
	void updateDCM();
	Quaternion getQuaternion();
	vector<double> accelerometerDeltaAngle();
	vector<double> gyroscopeDeltaAngle();
	vector<double> magnetDeltaAngle();
	double accelerometerMagnitude(); 
	void calibrate(); 

	//For debugging
	string getNorth(); 
	string getWest(); 
	string getZenith(); 
};
