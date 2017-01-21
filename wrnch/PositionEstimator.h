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
	pair<Quaternion, double> previousEstimatedPosition; //Coordinates of X in C's frame

	queue<pair<Quaternion, double>> xQueueOE;	// To simulate lag from the IMU/Orientation Estimator
	queue<pair<Quaternion, double>> cQueueOE;	// To simulate lag from the IMU/Orientation Estimator
	queue<pair<Quaternion, double>> cQueue3D;	// To simulate lag from the Mock 3D Camera

	queue<pair<Quaternion, double>> estimatedPosition; // To store predicted position until time occurs

	Clock * clock; 
	OrientationEstimator xOE; 
	OrientationEstimator cOE; 
	Mock3DSensor c3D; 

	PositionEstimator(OrientationEstimator&, OrientationEstimator&, Mock3DSensor&); 
	void update(); 


}; 