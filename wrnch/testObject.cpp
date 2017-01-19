#include "testObject.h"
#include "Clock.h"
#include <gl/freeglut.h>
#include <cmath>
#include <vector>


testObject::testObject(GLfloat r, int sl, int st, Path * p, MockIMU * i) :
	radius(r), slices(sl), stacks(st), path(p), imu(i) {}

void testObject::update() {
	path->increment(); 
	std::vector<double> rotation = path->convertQuaternionForGl(); 

	glPushMatrix();
	glRotated(-90, 1, 0, 0);		// Make z vector vertical instead of y
	glTranslated(path->rX(), path->rY(), path->rZ());	//Move to current location
	//glRotated(6.28 * path->clock->getTime(), 1, 0, 0);			
	glRotated(rotation[0], rotation[1], rotation[2], rotation[3]); 
	glutWireSphere(radius, slices, stacks);
	glPopMatrix();
}

/*void testObject::updateTrace(double x, double y, double z) {
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

}*/