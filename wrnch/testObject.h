#pragma once
#include <gl/freeglut.h>
#include "Clock.h"
#include "Path.h"

class testObject {
	GLfloat radius;
	int slices;
	int stacks;
	Path * path; 

public:
	testObject(GLfloat r, int sl, int st, Path * p);
	void update();

	//Path tracing - disabled
	void updateTrace(double, double, double); 
	void drawTrace();
};