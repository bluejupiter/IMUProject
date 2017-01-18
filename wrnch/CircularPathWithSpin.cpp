#include "CircularPathWithSpin.h"
#include <math.h>

CircularPathWithSpin::CircularPathWithSpin() {


}

double CircularPathWithSpin::rX() {
	return 2 * sin(clock->getTime());
} 
double CircularPathWithSpin::rY() {
	return 2 * cos(clock->getTime());
}
double CircularPathWithSpin::rZ() {
	return 1.0;
}

double CircularPathWithSpin::xAcc() {
	return 2 * cos(clock->getTime()); 
}

double CircularPathWithSpin::yAcc() {
	return -2 * sin(clock->getTime());
};

double CircularPathWithSpin::zAcc() {
	return -9.81; 
}

double CircularPathWithSpin::thetaX() { return 6.28 * clock->getTime(); }
double CircularPathWithSpin::thetaY() { return 0;  }
double CircularPathWithSpin::thetaZ() { return 0;  }

double CircularPathWithSpin::wX() { return 0; }
double CircularPathWithSpin::wY() { return 0; }
double CircularPathWithSpin::wZ() { return 0; }

void CircularPathWithSpin::increment(double seconds) {
	clock->tick(seconds);
}