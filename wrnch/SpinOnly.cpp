#include "SpinOnly.h"
#include <math.h>
#include <iostream>
#include <string>

SpinOnly::SpinOnly() {
	quat.set(1, 0, 0, 0); // w,x,y,z
	change.set(cos(0.02), 0, 0, sin(0.02)); 
}; 


double SpinOnly::rX() { return 0;  };
double SpinOnly::rY() { return 0; };
double SpinOnly::rZ() { return 1; };

double SpinOnly::xAcc() { return 0; };
double SpinOnly::yAcc() { return 0; };
double SpinOnly::zAcc() { return -9.81; };

void SpinOnly::update() {
	quat = change.multiply(quat); 
}

