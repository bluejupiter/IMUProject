#pragma once
#include <gl/freeglut.h>
#include "Clock.h"
#include "Path.h"

class testObject {
	GLfloat radius;
	int slices;
	int stacks;
	double x;
	double y = 4;
	double z;
	Path * path; 

	//Path tracing - disabled
	double pointsTrace[100][3];
	int pointsCount; 
	bool fullTrace; 

public:
	testObject(GLfloat r, int sl, int st, double x, double y, double z, Path * p);
	void update();

	//Path tracing - disabled
	void updateTrace(double, double, double); 
	void drawTrace();
};