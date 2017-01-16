#pragma once

class Clock {
private:
	double timeInSeconds; 
	static bool instanceFlag; 
	static Clock* INSTANCE; 
	Clock();
public: 
	static Clock* getInstance(); 
	~Clock() { instanceFlag = false; }
	void tick(double); 
	void reset() { timeInSeconds = 0; };
	double getTime() { return timeInSeconds; };
};

