#pragma once

class Camera {
	double theta;      // determines the x and z positions
	double y;          // the current y position
	double dTheta;     // increment in theta for swinging the camera around
	double dy;         // increment in y for moving the camera up/down
public:
	Camera();
	double getX();
	double getY();
	double getZ();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
};
