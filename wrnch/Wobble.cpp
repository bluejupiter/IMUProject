#include "Wobble.h"

Wobble::Wobble() {
	quat.set(1, 0, 0, 0); // w,x,y,z
	change.set(cos(0.02), sin(0.02) / sqrt(3.0), sin(0.02) / sqrt(3.0), sin(0.02) / sqrt(3.0));
};

double Wobble::rX() { return 0; };
double Wobble::rY() { return 0; };
double Wobble::rZ() { return 1; };

double Wobble::xAcc() { return gravityX(); };
double Wobble::yAcc() { return gravityY(); };
double Wobble::zAcc() { return gravityZ(); };

void Wobble::update() {
	quat = change.multiply(quat);
}; 