#pragma once
#include "Path.h"

class CircularPathWithSpin : public Path {
public: 
	CircularPathWithSpin();

	double rX(); 
	double rY();
	double rZ();

	double xAcc();
	double yAcc();
	double zAcc();
	double wX();
	double wY();
	double wZ();

	void increment(double); 
};