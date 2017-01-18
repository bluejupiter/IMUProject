#pragma once
#include "MockIMU.h";
#include "Quaternion.h"
#include <vector>
using std::vector; 

class OrientationEstimator {
	MockIMU * imu;
	vector<double> North;          // First row of DCM matrix. "North" in the body frame
	vector<double> West;			// Second row of DCM matrix. "West" in the body frame
	vector<double> Zenith;			// Third row of DCM matrix. "Zenith" in the body frame
	Quaternion estimatedQuat; 
	

public: 
	OrientationEstimator(MockIMU * i); 
	void normalize(vector<double> &); 
	void orthonormalize(vector<double> &, vector<double> &, vector<double> &);
	vector<double> crossProduct(vector<double>, vector<double>); 
	void updateDCM(); 
	void updateQuaternion(); 
}