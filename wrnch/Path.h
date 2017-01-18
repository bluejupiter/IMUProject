#pragma once
#include "Clock.h";
#include "Quaternion.h"

class Path {
public:
	Clock * clock; 
	Quaternion quat; 

	Path() { clock = Clock::getInstance(); };
	virtual double rX() = 0;		//x coordinate in global frame
	virtual double rY() = 0;		//y coordinate in global frame
	virtual double rZ() = 0;		//z coordinate in global frame 

	// For accelerometer to collect
	virtual double xAcc() = 0;		//x-axis Acceleration in the object's frame
	virtual double yAcc() = 0;		//y-axis Acceleration in the object's frame
	virtual double zAcc() = 0;		//z-axis Acceleration in the object's frame
	virtual double wX() = 0;		//angular velocity about the object's x-axis
	virtual double wY() = 0;		//angular velocity about the object's y-axis
	virtual double wZ() = 0;		//angular velocity about the object's z-axis

	virtual void increment(double) = 0; 
};

