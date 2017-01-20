#pragma once
#include "Path.h"

class SpinOnly : public Path {
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