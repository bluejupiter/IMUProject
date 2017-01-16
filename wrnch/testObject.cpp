#include "testObject.h"
#include <gl/freeglut.h>
#include <cmath>


testObject::testObject(GLfloat r, int sl, int st, double x, double y, double z) :
	radius(r), slices(sl), stacks(st), x(x), y(y), z(z) {}

void testObject::update() {
	time += 0.01;
	x = sin(time);
	z = cos(time);

	glPushMatrix();
	// Rotate so y is vertical on the xz plane
	//glRotatef(-90.0, 1.0, 0.0, 0.0);
	glTranslated(x, y, z);
	// Translate to current position
	glutWireSphere(radius, slices, stacks);
	glPopMatrix();
}
