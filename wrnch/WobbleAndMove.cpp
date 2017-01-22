#include "WobbleAndMove.h"

WobbleAndMove::WobbleAndMove(double x, double y, double z) : Motion(x,y,z) {
	quat.set(1, 0, 0, 0); // w,x,y,z
	change.set(cos(0.02), sin(0.02) / sqrt(3.0), sin(0.02) / sqrt(3.0), sin(0.02) / sqrt(3.0));
	GlobalFrameAcc.set(0, 0, 0, 0); 
};

double WobbleAndMove::rX() { 
	double t = clock->getTime();
	double x; 
	if (t < 1)
		x = cos(t)* (3 * t * t - 2 * t * t * t);
	else
		x = cos(t); 
	
	return x + xOffset; 
};

double WobbleAndMove::rY() { 
	double t = clock->getTime(); 
	double y; 
	if (t < 1)
		y = sin(t) * (3 * t * t - 2 * t * t * t);
	else
		y = sin(t); 
	
	return y + yOffset; 
};

double WobbleAndMove::rZ() { return zOffset; };

double WobbleAndMove::xAcc() { 
	Quaternion accLocalFrame = quat.intoBodyFrame(GlobalFrameAcc); 
	double s = sqrt(1 - accLocalFrame.w * accLocalFrame.w); 
	double xAcc = accLocalFrame.x / s + gravityX(); 
	
	return xAcc; 
};
double WobbleAndMove::yAcc() { 
	Quaternion accLocalFrame = quat.intoBodyFrame(GlobalFrameAcc);
	double s = sqrt(1 - accLocalFrame.w * accLocalFrame.w);
	double yAcc = accLocalFrame.y / s + gravityY();

	return yAcc;
};
double WobbleAndMove::zAcc() { 
	Quaternion accLocalFrame = quat.intoBodyFrame(GlobalFrameAcc);
	double s = sqrt(1 - accLocalFrame.w * accLocalFrame.w);
	double zAcc = accLocalFrame.z / s + gravityZ();

	return zAcc;
};

void WobbleAndMove::update() {
	double t = clock->getTime();
	if (t < 1) {
		GlobalFrameAcc.x = -sin(t) * (3 * t * t - 2 * t * t * t) + cos(t) * (6 * t - 6 * t * t); 
		GlobalFrameAcc.y = cos(t) * (3 * t * t - 2 * t * t * t) + sin(t) * (6 * t - 6 * t * t);
	}
	GlobalFrameAcc.z = 0; 
	GlobalFrameAcc.w = 0; 

	quat = change.multiply(quat);
};