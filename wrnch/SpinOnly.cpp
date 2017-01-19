#include "SpinOnly.h"
#include <math.h>
#include <iostream>
#include <string>

SpinOnly::SpinOnly() {
	quat.set(1, 0, 0, 0); // w,x,y,z
}; 


double SpinOnly::rX() { return 0;  };
double SpinOnly::rY() { return 0; };
double SpinOnly::rZ() { return 1; };

double SpinOnly::xAcc() { return 0; };
double SpinOnly::yAcc() { return 0; };
double SpinOnly::zAcc() { return 0; };
double SpinOnly::wX() { return 0; };
double SpinOnly::wY() { return 0; };
double SpinOnly::wZ() { return 0.04; }; //Spin about z axis at 0.04 rad/s

void SpinOnly::increment() {
	clock->tick();
	Quaternion previousChange(cos(0.02), 0, 0, sin(0.02));
	quat = previousChange * quat; 
}

