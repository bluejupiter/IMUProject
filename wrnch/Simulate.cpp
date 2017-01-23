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
#include "WobbleAndMove.h"
#include "Stationary.h"
#include "Mock3DSensor.h"
#include "PositionEstimator.h"
#include "Predict.h"
using std::to_string; 

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

WobbleAndMove xpath(2, 0, 1); 
MockIMU imuX(&xpath); 
testObject test(0.5, 8, 8, &xpath);
OrientationEstimator xOE(&imuX); 

Wobble cpath(-2, 0, 1); 
MockIMU imuC(&cpath); 
testObject testC(0.5, 8, 8, &cpath); 
OrientationEstimator cOE(&imuC); 

Mock3DSensor threeD(&xpath, &cpath); 
PositionEstimator PE(xOE, cOE, threeD); 

Predict predictionVisual(0.2, 8, 8, PE, cpath);


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
	testC.update(); 
	cOE.updateDCM(); 
	xOE.updateDCM(); 
	PE.update();
	predictionVisual.update();
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
	WobbleAndMove xTest(1, 0, 1);
	MockIMU imuXTest(&xTest);
	OrientationEstimator xOETest(&imuXTest);

	Wobble cTest(-2, 0, 1);
	MockIMU imuCTest(&cTest);
	OrientationEstimator cOETest(&imuCTest);

	Mock3DSensor cam(&xTest, &cTest);
	PositionEstimator PETest(xOETest, cOETest, cam);

	for (int i = 0; i < 50; i++) {
		clock->tick();
		xTest.update();
		cTest.update();
		cOETest.updateDCM();
		xOETest.updateDCM();
		PETest.update();

		std::cout << "X Quaternion is: " + xTest.quat.toString();
		std::cout << "X OE Quaternion is: " + xOETest.getQuaternion().toString();
		std::cout << "X position is: " + to_string(xTest.rX()) + " " + to_string(xTest.rY()) + " " + to_string(xTest.rZ()) + "\n"; 

		std::cout << "C Quaternion is: " + cTest.quat.toString();
		std::cout << "C OE Quaternion is: " + cOETest.getQuaternion().toString();
		std::cout << "C position is: " + to_string(cTest.rX()) + " " + to_string(cTest.rY()) + " " + to_string(cTest.rZ()) + "\n";

		Quaternion apparentPosition = cam.getApparentPositionOfX(); 
		std::cout << "X position (in C frame) is " + to_string(apparentPosition.x) + " " + to_string(apparentPosition.y) + " " + to_string(apparentPosition.z) + "\n";
		apparentPosition = cTest.quat.intoGlobalFrame(apparentPosition); 
		std::cout << "X position (in rel. to C) is " + to_string(apparentPosition.x) + " " + to_string(apparentPosition.y) + " " + to_string(apparentPosition.z) + "\n";
		std::cout << "\n\n"; 
		
		if (!PETest.estimatedPositionGlobalFrame.empty()) {
			pair<Quaternion, double> XrelativeToC = PETest.estimatedPositionGlobalFrame.front(); PETest.estimatedPositionGlobalFrame.pop(); 
			double xP = XrelativeToC.first.x - cTest.rXatTime(XrelativeToC.second);
			double yP = XrelativeToC.first.y - cTest.rYatTime(XrelativeToC.second);
			double zP = XrelativeToC.first.z - cTest.rZatTime(XrelativeToC.second);
			std::cout << "X position according to X at time " + std::to_string(XrelativeToC.second)
				+ "sec is [" + std::to_string(xTest.rXatTime(XrelativeToC.second)) + "][" + std::to_string(xTest.rYatTime(XrelativeToC.second))
				+ "][" + std::to_string(xTest.rZatTime(XrelativeToC.second)) + "]\n"; 
			std::cout << "X position according to PE at time " + std::to_string(XrelativeToC.second)
				+ "sec is [" + std::to_string(xP) + "][" + std::to_string(yP) + "][" + std::to_string(zP) + "]\n\n"; 
		}
		
	}


	Quaternion vec(0, 5, 6, 7); 
	Quaternion quat(cos(0.5), 0, 0, sin(0.5)); 
	Quaternion mod = quat.intoBodyFrame(vec); 
	mod = quat.intoGlobalFrame(vec); 
	std::cout << "Vec is : " + std::to_string(vec.w) + " " + std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z) + "\n";

	system("pause");
	
	
}

//std::cout << "Start Quaternion is: " + spin.quat.toString();
//std::cout << "Start OE Quaternion is: " + oe.getQuaternion().toString() + "\n";
