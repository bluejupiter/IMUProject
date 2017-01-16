#include "testObject.h"
#include "Clock.h"
#include <gl/freeglut.h>
#include <cmath>


testObject::testObject(GLfloat r, int sl, int st, double x, double y, double z) :
	radius(r), slices(sl), stacks(st), x(x), y(y), z(z) {
	time = Clock::getInstance(); 
}

void testObject::update() {
	time->tick(0.01);
	x = sin(time->getTime());
	z = cos(time->getTime());

	glPushMatrix();
	glTranslated(x, y, z);
	glutWireSphere(radius, slices, stacks);
	glPopMatrix();
}
