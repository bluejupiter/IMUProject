#include "CircularPathWithSpin.h"
#include <math.h>

CircularPathWithSpin::CircularPathWithSpin() {

	// Start simulation with object orientation matching global orientation 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i != j)
				realDCM[i][j] = 0.0;
			else
				realDCM[i][j] = 1.0; 
		}
	}

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

double CircularPathWithSpin::thetaX() { return 0;  }
double CircularPathWithSpin::thetaY() { return 0;  }
double CircularPathWithSpin::thetaZ() { return 0;  }

double CircularPathWithSpin::wX() { return 0; }
double CircularPathWithSpin::wY() { return 0; }
double CircularPathWithSpin::wZ() { return 0; }