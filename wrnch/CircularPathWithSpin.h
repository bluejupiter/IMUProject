#pragma once
#include "Motion.h"

class CircularPathWithSpin : public Motion {
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

	void increment(); 
};