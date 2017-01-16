#include "Clock.h"

Clock* Clock::INSTANCE = nullptr;

bool Clock::instanceFlag = false;

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

void Clock::tick(double seconds) {
	timeInSeconds += seconds;
}

