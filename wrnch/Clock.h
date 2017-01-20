#pragma once

class Clock {
private:
	double timeInSeconds; 
	static bool instanceFlag; 
	static Clock* INSTANCE; 
	Clock();
public: 
	static double increment;
	static Clock* getInstance(); 
	~Clock() { instanceFlag = false; }
	void tick(); 
	void reset() { timeInSeconds = 0; };
	double getTime() { return timeInSeconds; };
	static void setIncrement(double seconds); 
};

