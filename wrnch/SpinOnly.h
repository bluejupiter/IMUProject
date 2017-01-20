#pragma once
#include "Path.h"

class SpinOnly : public Motion {
public:
	SpinOnly();

	double rX();
	double rY();
	double rZ();

	double xAcc();
	double yAcc();
	double zAcc();

	void update();
};