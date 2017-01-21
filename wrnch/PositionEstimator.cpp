#include "PositionEstimator.h"

PositionEstimator::PositionEstimator(OrientationEstimator& x, OrientationEstimator& c, Mock3DSensor& pos) : xOE(x), cOE(c), c3D(pos) {
	clock = Clock::getInstance(); 
	previousEstimatedPosition.first = c3D.getApparentPositionOfX(); 
	previousEstimatedPosition.second = 0.0; // All clocks are synchronized at start of simulation to time = 0.0 seconds
	lag = 0.2;
}; 

void PositionEstimator::update() {
	// Poll the Orientation Estimators (add to queue to simulate lag)
	xQueueOE.push(xOE.queryEstimatedOrientation()); 
	cQueueOE.push(cOE.queryEstimatedOrientation()); 

	// Check if 3D sensor acquired data
	pair<Quaternion, double> temp = c3D.query3DSensor(); 
	if (temp.second >= 0)	// time = -1.0 indicates that 3D sensor did not collect data
		cQueue3D.push(temp); 

	//Check for new data from buffer (with artificial lag added) and update position
	pair<Quaternion, double> position = cQueue3D.front(); 
	if (clock->getTime() - position.second <= lag) {
		cQueue3D.pop(); 

		// If our predicted position is larger than the error, correct. Otherwise combine
		if (previousEstimatedPosition.first.x - position.first.x > c3D.maxError)
			previousEstimatedPosition.first.x = position.first.x + c3D.maxError;
		else if (previousEstimatedPosition.first.x - position.first.x < -1 * c3D.maxError)
			previousEstimatedPosition.first.x = position.first.x - c3D.maxError;
		else
			previousEstimatedPosition.first.x = (position.first.x + previousEstimatedPosition.first.x) / 2; 

		// If our predicted position is larger than the error, correct. Otherwise combine
		if (previousEstimatedPosition.first.y - position.first.y > c3D.maxError)
			previousEstimatedPosition.first.y = position.first.y + c3D.maxError;
		else if (previousEstimatedPosition.first.y - position.first.y < -1 * c3D.maxError)
			previousEstimatedPosition.first.y = position.first.y - c3D.maxError;
		else
			previousEstimatedPosition.first.y = (position.first.y + previousEstimatedPosition.first.y) / 2;

		// If our predicted position is larger than the error, correct. Otherwise combine
		if (previousEstimatedPosition.first.z - position.first.z > c3D.maxError)
			previousEstimatedPosition.first.z = position.first.z + c3D.maxError;
		else if (previousEstimatedPosition.first.z - position.first.z < -1 * c3D.maxError)
			previousEstimatedPosition.first.z = position.first.z - c3D.maxError;
		else
			previousEstimatedPosition.first.z = (position.first.z + previousEstimatedPosition.first.z) / 2;

		previousEstimatedPosition.second = position.second; 
	}

	// Predict future position 
}