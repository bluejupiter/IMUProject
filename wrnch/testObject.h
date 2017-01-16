#pragma once
#include <gl/freeglut.h>

class testObject {
	GLfloat radius;
	int slices;
	int stacks;
	double x;
	double y = 4;
	double z;
	double time = 0;

public:
	testObject(GLfloat r, int sl, int st, double x, double y, double z);
	void update();
};