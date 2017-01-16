#pragma once
#include <gl/freeglut.h>
#include "Clock.h"

class testObject {
	GLfloat radius;
	int slices;
	int stacks;
	double x;
	double y = 4;
	double z;
	Clock * time; 

public:
	testObject(GLfloat r, int sl, int st, double x, double y, double z);
	void update();
};