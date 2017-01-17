#include "testObject.h"
#include "Clock.h"
#include <gl/freeglut.h>
#include <cmath>


testObject::testObject(GLfloat r, int sl, int st, double x, double y, double z) :
	radius(r), slices(sl), stacks(st), x(x), y(y), z(z), pointsCount(0), fullTrace(false) {
	time = Clock::getInstance(); 
}

void testObject::update() {
	time->tick(0.01);
	x = 2*sin(time->getTime());
	z = 2*cos(time->getTime());

	glPushMatrix();
	glRotated(time->getTime()*100, 0, 1, 0); 
	glTranslated(x, y, z);
	glutWireSphere(radius, slices, stacks);
	glPopMatrix();
}

void testObject::updateTrace(double x, double y, double z) {
	pointsTrace[pointsCount][0] = x; 
	pointsTrace[pointsCount][1] = y;
	pointsTrace[pointsCount][2] = z;
	pointsCount++; 

	if (pointsCount == 100) {
		fullTrace = true;
		pointsCount = 0;
	}
}

void testObject::drawTrace() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 3 * sizeof(double), pointsTrace);
	if (!fullTrace)
		glDrawArrays(GL_POINTS, 0, pointsCount);
	else
		glDrawArrays(GL_POINTS, 0, 99);

}