#pragma once
#include "Clock.h"
#include "Quaternion.h"
#include <vector>

class Motion {
public:
	Clock * clock; 
	Quaternion quat; 
	Quaternion change; 
	Quaternion downGlobalFrame; //(unit vector, points straight down in global frame)

	Motion();
	virtual double rX() = 0;		//x coordinate in global frame
	virtual double rY() = 0;		//y coordinate in global frame
	virtual double rZ() = 0;		//z coordinate in global frame 

	// For accelerometer to collect
	virtual double xAcc() = 0;		//x-axis Acceleration in the object's frame
	virtual double yAcc() = 0;		//y-axis Acceleration in the object's frame
	virtual double zAcc() = 0;		//z-axis Acceleration in the object's frame
	double wX();		//angular velocity about the object frame's x-axis (rad/s)
	double wY();		//angular velocity about the object frame's y-axis (rad/s)
	double wZ();		//angular velocity about the object frame's z-axis (rad/s)

	// Helper functions
	std::vector<double> convertQuaternionForGl(); 
	virtual void update() = 0; 
	double gravityX();				//Gravity's contribution to the object frame's x-axis;
	double gravityY();				//Gravity's contribution to the object frame's x-axis;
	double gravityZ();				//Gravity's contribution to the object frame's x-axis;
};

