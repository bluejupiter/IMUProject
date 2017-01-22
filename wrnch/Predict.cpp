#include "Predict.h"
#include "Clock.h"
#include <gl/freeglut.h>
#include <cmath>
#include <vector>


Predict::Predict(GLfloat r, int sl, int st, PositionEstimator & p, Motion & cam) :
	radius(r), slices(sl), stacks(st), pe(p), cameraMotion(&cam) {}

void Predict::update() {
	glPushMatrix();
	glRotated(-90, 1, 0, 0);		// Make z vector vertical instead of y
	glTranslated(getX(), getY(), getZ());	//Move to current location	
	glutSolidSphere(radius, slices, stacks);
	glPopMatrix();
}

double Predict::getX() { return 0; };
double Predict::getY() { return 0; };
double Predict::getZ() { return 0; };