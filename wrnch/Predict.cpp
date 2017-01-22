#include "Predict.h"
#include "Clock.h"
#include <gl/freeglut.h>
#include <cmath>
#include <vector>
#include <utility>
using std::pair; 


Predict::Predict(GLfloat r, int sl, int st, PositionEstimator & p, Motion & cam) :
	radius(r), slices(sl), stacks(st), pe(p), cameraMotion(&cam) {}

void Predict::update() {
	if (!pe.estimatedPositionGlobalFrame.empty()) {

		glPushMatrix();
		glRotated(-90, 1, 0, 0);		// Make z vector vertical instead of y
		glTranslated(getX(), getY(), getZ());	//Move to current location	
		glutSolidSphere(radius, slices, stacks);
		glPopMatrix();

		pe.estimatedPositionGlobalFrame.pop(); 
	}
}

double Predict::getX() { 
	pair<Quaternion, double> XrelativeToC = pe.estimatedPositionGlobalFrame.front(); 
	double xPositionInSimulation = XrelativeToC.first.x - cameraMotion->rXatTime(XrelativeToC.second); 

	return xPositionInSimulation; 
};



double Predict::getY() { 
	pair<Quaternion, double> XrelativeToC = pe.estimatedPositionGlobalFrame.front();
	double yPositionInSimulation = XrelativeToC.first.y - cameraMotion->rYatTime(XrelativeToC.second);

	return yPositionInSimulation;
};

double Predict::getZ() { 
	pair<Quaternion, double> XrelativeToC = pe.estimatedPositionGlobalFrame.front();
	double zPositionInSimulation = XrelativeToC.first.z - cameraMotion->rZatTime(XrelativeToC.second);

	return zPositionInSimulation;
};