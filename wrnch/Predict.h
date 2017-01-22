#pragma once
#include <gl/freeglut.h>
#include "Clock.h"
#include "Motion.h"
#include "MockIMU.h"
#include "PositionEstimator.h"

class Predict {
	GLfloat radius;
	int slices;
	int stacks;
	PositionEstimator pe; 
	Motion * cameraMotion; 

public:
	Predict(GLfloat r, int sl, int st, PositionEstimator & pe, Motion & cam);
	void update();
	double getX(); 
	double getY();
	double getZ();
};