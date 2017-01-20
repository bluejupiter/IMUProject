#include "Clock.h"

Clock* Clock::INSTANCE = nullptr;

bool Clock::instanceFlag = false;
double Clock::increment = (1.0/30.0); // default

Clock::Clock() : timeInSeconds(0) {};

Clock* Clock::getInstance() {
	if (!instanceFlag) {
		INSTANCE = new Clock();
		instanceFlag = true;
		return INSTANCE;
	}
	else
		return INSTANCE;
};

void Clock::tick() {
	timeInSeconds += increment;
}

void Clock::setIncrement(double seconds) { increment = seconds; }




