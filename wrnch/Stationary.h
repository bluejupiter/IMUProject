#pragma once
#include "Motion.h"

class Stationary : public Motion {
public:

	Stationary(double, double, double);

	double rX();
	double rY();
	double rZ();

	double xAcc();
	double yAcc();
	double zAcc();

	void update();
};