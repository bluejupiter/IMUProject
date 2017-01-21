#pragma once
#include "Motion.h"
#include "Quaternion.h"

class MockIMU {
	Motion * path; 
	Quaternion northGlobalFrame;

public: 
	MockIMU(Motion * p); 
	
	double xAcc();		//x-axis Acceleration in the object's frame
	double yAcc();		//y-axis Acceleration in the object's frame
	double zAcc();		//z-axis Acceleration in the object's frame
	double wX();		//angular velocity about the object's x-axis
	double wY();		//angular velocity about the object's y-axis
	double wZ();		//angular velocity about the object's z-axis
	double error();		//returns 1 plus value between -errorMagnitude and +errorMagnitude
	double mX();		//Magnetic field strength in the object frame's x-axis
	double mY();		//Magnetic field strength in the object frame's x-axis
	double mZ();		//Magnetic field strength in the object frame's x-axis
};