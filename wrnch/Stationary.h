#pragma once
#include "Motion.h"

class Stationary : public Motion {
public:

	Stationary();

	double rX();
	double rY();
	double rZ();

	double xAcc();
	double yAcc();
	double zAcc();

	void update();
};