#include <gl/freeglut.h>
#include <cmath>
#include "Camera.h"
#include "testObject.h"
#include "Checkerboard.h"
#include "CircularPathWithSpin.h"
#include "Clock.h"
#include "SpinOnly.h"
#include <iostream>
#include "OrientationEstimator.h"
#include "Wobble.h"

// Colors
GLfloat WHITE[] = { 1, 1, 1 };
GLfloat RED[] = { 1, 0, 0 };
GLfloat GREEN[] = { 0, 1, 0 };
GLfloat MAGENTA[] = { 1, 0, 1 };

// Global variables: a camera, a checkerboard and some balls.
Checkerboard checkerboard(8, 8);
Camera camera;
Clock * clock = Clock::getInstance(); 

//Add path to object and corresponding imu
//SpinOnly path; 
Wobble path; 
MockIMU imuX(&path); 
testObject test(0.5, 8, 8, &path);


// Application-specific initialization: Set up global lighting parameters
// and create display lists.
void init() {
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	checkerboard.create();
}

// Draws one frame, the checkerboard then the balls, from the current camera
// position.
void display() {
	clock->tick(); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
		checkerboard.centerx(), 0.0, checkerboard.centerz(),
		0.0, 1.0, 0.0);
	checkerboard.draw();
	test.update(); 
	glFlush();
	glutSwapBuffers();
}

// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
	glMatrixMode(GL_MODELVIEW);
}

// Requests to draw the next frame.
void timer(int v) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, v);
}

// Moves the camera according to the key pressed, then ask to refresh the
// display.
void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: camera.moveLeft(); break;
	case GLUT_KEY_RIGHT: camera.moveRight(); break;
	case GLUT_KEY_UP: camera.moveUp(); break;
	case GLUT_KEY_DOWN: camera.moveDown(); break;
	} 
	glutPostRedisplay();
}

void simulate(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Simulation");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutTimerFunc(100, timer, 0);
	init();
	glutMainLoop();
}

std::string convert(Quaternion q) {
	double angle = 2 * acos(q.w) * 180/3.14;
	double s = sqrt(1 - q.w * q.w);
	if (s < 0)
		s *= -1; 
	return "(" + std::to_string(angle) + ", " + std::to_string(q.x / s) + ", " + std::to_string(q.y / s) + ", " + std::to_string(q.z / s) + ")\n"; 
}
// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {

	//simulate(argc, argv); 

	/*
	Quaternion start(1, 0, 0, 0); 
	Quaternion rotate(cos(0.05), 0, 0, sin(0.05));
	std::cout << "Start Quaternion is: " + start.toString(); 
	std::cout << "Rotate Quaternion is: " + rotate.toString(); 
	for (int i = 0; i < 80; i++) {
		start = rotate * start; 
		std::cout << "\n"; 
		std::cout << "Quaternion is now: " + start.toString(); 
		std::cout << "Rotated vector is now: " + convert(start); 
	}
	system("pause");
	
	

	SpinOnly spin; 
	MockIMU testIMU(&spin); 
	std::cout << "\nOriginal North in local frame is given by mx = " + std::to_string(testIMU.mX()) + "   my = " + std::to_string(testIMU.mY()) + "   mz = " + std::to_string(testIMU.mZ()) + "/n";
	clock->tick(); 
	spin.update(); 
	std::cout << "Increment is " + std::to_string(Clock::increment); 
	std::cout << "Start Quaternion is: " + spin.quat.toString();
	std::cout << "Rotate Quaternion is: " + spin.change.toString();
	std::cout << "\nAngular velocities are: \n\t wX = " + std::to_string(spin.wX()) + "\n\t wY = " + std::to_string(spin.wY()) + "\n\t wZ = " + std::to_string(spin.wZ()); 
	std::cout << "\nNorth in local frame is given by mx = " + std::to_string(testIMU.mX()) + "   my = " + std::to_string(testIMU.mY()) + "   mz = " + std::to_string(testIMU.mZ()) + "/n"; 
	
	clock->tick();
	spin.update();
	std::cout << "\nNorth in local frame is given by mx = " + std::to_string(testIMU.mX()) + "   my = " + std::to_string(testIMU.mY()) + "   mz = " + std::to_string(testIMU.mZ()) + "/n";
	clock->tick();
	spin.update();
	std::cout << "\nNorth in local frame is given by mx = " + std::to_string(testIMU.mX()) + "   my = " + std::to_string(testIMU.mY()) + "   mz = " + std::to_string(testIMU.mZ()) + "/n";

	*/
	
	
	Wobble spin;
	MockIMU testIMU(&spin);
	OrientationEstimator oe(&testIMU); 
	std::cout << "Start Quaternion is: " + spin.quat.toString();
	std::cout << "Start OE Quaternion is: " + oe.getQuaternion().toString() + "\n";
	std::cout << "Initial DCM is: \n" + oe.getNorth() + "\n" + oe.getWest() + "\n" + oe.getZenith() + "\n"; 

	for (int i = 0; i < 50; i++) {
		clock->tick(); 
		spin.update(); 
		oe.updateDCM(); 
		std::cout << "\nActual Quaternion is: " + spin.quat.toString();
		std::cout << "OE Quaternion is: " + oe.getQuaternion().toString();
	}
	system("pause");
	
}