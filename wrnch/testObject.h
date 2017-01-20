#pragma once
#include <gl/freeglut.h>
#include "Clock.h"
#include "Path.h"
#include "MockIMU.h"

class testObject {
	GLfloat radius;
	int slices;
	int stacks;
	Motion * path;

public:
	testObject(GLfloat r, int sl, int st, Motion * p);
	void update();

	//Path tracing - disabled
	//void updateTrace(double, double, double); 
	//void drawTrace();
};