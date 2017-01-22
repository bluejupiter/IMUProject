#pragma once
#include "OrientationEstimator.h"
#include "Mock3DSensor.h"
#include "Quaternion.h"
#include <queue>
#include <utility>
using std::queue; 
using std::pair; 

class PositionEstimator {
public: 
	double lag; // lag (in seconds) from the sensors
	double imuPeriod; 
	double predictPeriod; 
	pair<Quaternion, double> previousEstimatedPosition; //Coordinates of X in C's frame

	queue<pair<Quaternion, double>> xQueueOE;	// To simulate lag from the Orientation Estimator
	queue<pair<Quaternion, double>> xQueueAcc;	// To simulate lag from the IMU
	queue<pair<Quaternion, double>> cQueueOE;	// To simulate lag from the Orientation Estimator
	queue<pair<Quaternion, double>> cQueueAcc;	// To simulate lag from the IMU
	queue<pair<Quaternion, double>> cQueue3D;	// To simulate lag from the Mock 3D Camera

	queue<pair<Quaternion, double>> estimatedPositionGlobalFrame; // To store predicted position until time occurs
	queue<pair<Quaternion, double>> estimatedPositionCFrame; // To store predicted position until time occurs

	vector<double> cVelGlobalFrame; 
	vector<double> xVelGlobalFrame; 

	Clock * clock; 
	OrientationEstimator xOE; 
	OrientationEstimator cOE; 
	Mock3DSensor c3D; 

	PositionEstimator(OrientationEstimator&, OrientationEstimator&, Mock3DSensor&); 
	void update(); 
	void gatherLagData(); 
	void incorporate3Dposition(); 
	void estimatePosition(); 


}; 