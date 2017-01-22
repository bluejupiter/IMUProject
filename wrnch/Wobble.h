#pragma once
#include "Motion.h"

class Wobble : public Motion {
public: 
	Wobble(double, double, double); 

	double rX();
	double rY();
	double rZ();

	double xAcc();
	double yAcc();
	double zAcc();

	void update();
};