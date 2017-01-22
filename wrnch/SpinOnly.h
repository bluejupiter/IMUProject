#pragma once
#include "Motion.h"

class SpinOnly : public Motion {
public:
	SpinOnly(double, double, double);

	double rX();
	double rY();
	double rZ();

	double xAcc();
	double yAcc();
	double zAcc();

	void update();
};