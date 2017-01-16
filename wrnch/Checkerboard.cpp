#include "Checkerboard.h"
#include <gl/freeglut.h>

Checkerboard::Checkerboard(int width, int depth) : width(width), depth(depth) {};

void Checkerboard::create() {
	GLfloat WHITE[] = { 1, 1, 1 };
	GLfloat RED[] = { 1, 0, 0 };
	displayListId = glGenLists(1);
	glNewList(displayListId, GL_COMPILE);
	GLfloat lightPosition[] = { 4, 3, 7, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	for (int x = -width / 2; x < width / 2; x++) {
		for (int z = -depth / 2; z < depth / 2; z++) {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
				(x + z) % 2 == 0 ? RED : WHITE);
			glVertex3d(x, 0, z);
			glVertex3d(x + 1, 0, z);
			glVertex3d(x + 1, 0, z + 1);
			glVertex3d(x, 0, z + 1);
		}
	}
	glEnd();
	glEndList();
}
void Checkerboard::draw() {
	glCallList(displayListId);
}
