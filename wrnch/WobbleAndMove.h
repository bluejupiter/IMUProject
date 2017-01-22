#pragma once
#include "Motion.h"

class WobbleAndMove : public Motion {
public:
	Quaternion GlobalFrameAcc; 

	WobbleAndMove(double, double, double);

	double rX();
	double rY();
	double rZ();

	double xAcc();
	double yAcc();
	double zAcc();

	void update();
};