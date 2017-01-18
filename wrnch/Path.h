#pragma once
#include "Clock.h";

class Path {
public:
	double x;
	double y;
	double z;
	double pitch;
	double yaw;
	double tilt;
	double realDCM[3][3]; 
	Clock * clock; 

	Path() { clock = Clock::getInstance(); };
	virtual double rX() = 0;		//x coordinate in global frame
	virtual double rY() = 0;		//y coordinate in global frame
	virtual double rZ() = 0;		//z coordinate in global frame 
	virtual double thetaX() = 0;	//Angle between the objects x-axis and the global frame's x-axis
	virtual double thetaY() = 0;	//Angle between the objects x-axis and the global frame's x-axis
	virtual double thetaZ() = 0;	//Angle between the objects x-axis and the global frame's x-axis

	// For accelerometer to collect
	virtual double xAcc() = 0;		//x-axis Acceleration in the object's frame
	virtual double yAcc() = 0;		//y-axis Acceleration in the object's frame
	virtual double zAcc() = 0;		//z-axis Acceleration in the object's frame
	virtual double wX() = 0;		//angular velocity about the object's x-axis
	virtual double wY() = 0;		//angular velocity about the object's y-axis
	virtual double wZ() = 0;		//angular velocity about the object's z-axis
};