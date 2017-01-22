#pragma once
#include <gl/freeglut.h>
#include "Clock.h"
#include "Motion.h"
#include "MockIMU.h"

class Predict {
	GLfloat radius;
	int slices;
	int stacks;

public:
	Predict(GLfloat r, int sl, int st);
	void update();
};