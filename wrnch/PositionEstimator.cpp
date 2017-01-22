#include "PositionEstimator.h"

PositionEstimator::PositionEstimator(OrientationEstimator& x, OrientationEstimator& c, Mock3DSensor& pos) : xOE(x), cOE(c), c3D(pos) {
	clock = Clock::getInstance(); 
	previousEstimatedPosition.first = c3D.getApparentPositionOfX(); 
	previousEstimatedPosition.second = 0.0; // All clocks are synchronized at start of simulation to time = 0.0 seconds
	lag = 0.2;
	imuPeriod = 1.0 / 30.0; 
	predictPeriod = 0.2; 
	cVelGlobalFrame = { 0, 0, 0 }; // Assume both objects start motionless
	xVelGlobalFrame = { 0, 0, 0 };

}; 

void PositionEstimator::update() {
	
	gatherLagData(); 

	incorporate3Dposition(); 

	estimatePosition(); 
}

void PositionEstimator::gatherLagData() {

	// Poll the Orientation Estimators (add to queue to simulate lag)
	xQueueOE.push(xOE.queryEstimatedOrientation());
	cQueueOE.push(cOE.queryEstimatedOrientation());

	// Poll the IMU's
	xQueueAcc.push(xOE.queryIMUAcc()); 
	cQueueAcc.push(cOE.queryIMUAcc()); 

	// Check if 3D sensor acquired data
	pair<Quaternion, double> temp = c3D.query3DSensor();
	if (temp.second >= 0)	// time = -1.0 indicates that 3D sensor did not collect data
		cQueue3D.push(temp);
}

void PositionEstimator::incorporate3Dposition() {
	//Check for new data from buffer (with artificial lag added) and update position
	if (!cQueue3D.empty()) {
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
	}

}

void PositionEstimator::estimatePosition() {
	if (!xQueueOE.empty() && !cQueueOE.empty()) {
		pair<Quaternion, double> xOrientation = xQueueOE.front();
		pair<Quaternion, double> cOrientation = cQueueOE.front();
		if (clock->getTime() - xOrientation.second <= lag) {
			xQueueOE.pop();
			cQueueOE.pop(); 

			pair<Quaternion, double> xAccData = xQueueAcc.front(); xQueueAcc.pop();
			Quaternion xLocalFrameAcc = xAccData.first;
			Quaternion xGlobalFrameAcc = xOrientation.first.intoGlobalFrame(xLocalFrameAcc);
			xGlobalFrameAcc.z += 9.81;  //Cancel gravity

			pair<Quaternion, double> cAccData = cQueueAcc.front(); cQueueAcc.pop();
			Quaternion cLocalFrameAcc = cAccData.first;
			Quaternion cGlobalFrameAcc = cOrientation.first.intoGlobalFrame(cLocalFrameAcc);
			cGlobalFrameAcc.z += 9.81; //Cancel gravity

			// Calculate displacement for next iteration
			// Displacement = initial Velocity * time + 1/2 * acceleration * time^2
			Quaternion xDisplacementGlobalFrame(0,
				xVelGlobalFrame[0] * imuPeriod + 0.5 * xGlobalFrameAcc.x * imuPeriod * imuPeriod,
				xVelGlobalFrame[1] * imuPeriod + 0.5 * xGlobalFrameAcc.y * imuPeriod * imuPeriod,
				xVelGlobalFrame[2] * imuPeriod + 0.5 * xGlobalFrameAcc.z * imuPeriod * imuPeriod);
			Quaternion cDisplacementGlobalFrame(0,
				cVelGlobalFrame[0] * imuPeriod + 0.5 * cGlobalFrameAcc.x * imuPeriod * imuPeriod,
				cVelGlobalFrame[1] * imuPeriod + 0.5 * cGlobalFrameAcc.y * imuPeriod * imuPeriod,
				cVelGlobalFrame[2] * imuPeriod + 0.5 * cGlobalFrameAcc.z * imuPeriod * imuPeriod);

			// Combine c and x's displacement into x (keep c at origin)
			xDisplacementGlobalFrame.set(0,
				xDisplacementGlobalFrame.x - cDisplacementGlobalFrame.x,
				xDisplacementGlobalFrame.y - cDisplacementGlobalFrame.y,
				xDisplacementGlobalFrame.z - cDisplacementGlobalFrame.z);

			Quaternion xDisplacementCFrame = cOrientation.first.intoBodyFrame(xDisplacementGlobalFrame);
			previousEstimatedPosition.first.set(0,
				previousEstimatedPosition.first.x + xDisplacementCFrame.x,
				previousEstimatedPosition.first.y + xDisplacementCFrame.y,
				previousEstimatedPosition.first.z + xDisplacementCFrame.z);
			previousEstimatedPosition.second = xOrientation.second + imuPeriod;

			// Predict displacement 0.2s in the future
			Quaternion xFutureDisplacementGlobalFrame(0,
				xVelGlobalFrame[0] * predictPeriod + 0.5 * xGlobalFrameAcc.x * predictPeriod * predictPeriod,
				xVelGlobalFrame[1] * predictPeriod + 0.5 * xGlobalFrameAcc.y * predictPeriod * predictPeriod,
				xVelGlobalFrame[2] * predictPeriod + 0.5 * xGlobalFrameAcc.z * predictPeriod * predictPeriod);
			Quaternion cFutureDisplacementGlobalFrame(0,
				cVelGlobalFrame[0] * predictPeriod + 0.5 * cGlobalFrameAcc.x * predictPeriod * predictPeriod,
				cVelGlobalFrame[1] * predictPeriod + 0.5 * cGlobalFrameAcc.y * predictPeriod * predictPeriod,
				cVelGlobalFrame[2] * predictPeriod + 0.5 * cGlobalFrameAcc.z * predictPeriod * predictPeriod);

			// Combine c and x's displacement into x (keep c at origin) for future prediction
			xFutureDisplacementGlobalFrame.set(0,
				xFutureDisplacementGlobalFrame.x - cFutureDisplacementGlobalFrame.x,
				xFutureDisplacementGlobalFrame.y - cFutureDisplacementGlobalFrame.y,
				xFutureDisplacementGlobalFrame.z - cFutureDisplacementGlobalFrame.z);

			// Calculate position in the future
			Quaternion xFuturePositionGlobalFrame = cOrientation.first.intoGlobalFrame(previousEstimatedPosition.first);
			xFuturePositionGlobalFrame.set(0,
				xFuturePositionGlobalFrame.x + xFutureDisplacementGlobalFrame.x,
				xFuturePositionGlobalFrame.y + xFutureDisplacementGlobalFrame.y,
				xFuturePositionGlobalFrame.z + xFutureDisplacementGlobalFrame.z);

			pair<Quaternion, double> futureGuessGlobalFrame(xFuturePositionGlobalFrame, xOrientation.second + predictPeriod);
			estimatedPositionGlobalFrame.push(futureGuessGlobalFrame);
			pair<Quaternion, double> futureGuessCFrame(cOrientation.first.intoBodyFrame(xFuturePositionGlobalFrame), xOrientation.second + predictPeriod);
			estimatedPositionCFrame.push(futureGuessCFrame);

			// Update velocities for next iteration
			xVelGlobalFrame[0] += xGlobalFrameAcc.x * imuPeriod;
			xVelGlobalFrame[1] += xGlobalFrameAcc.y * imuPeriod;
			xVelGlobalFrame[2] += xGlobalFrameAcc.z * imuPeriod;

			cVelGlobalFrame[0] += cGlobalFrameAcc.x * imuPeriod;
			cVelGlobalFrame[1] += cGlobalFrameAcc.y * imuPeriod;
			cVelGlobalFrame[2] += cGlobalFrameAcc.z * imuPeriod;

		}
	}
}
