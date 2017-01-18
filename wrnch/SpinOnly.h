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
	double wX();
	double wY();
	double wZ();

	void increment(double) {};
};