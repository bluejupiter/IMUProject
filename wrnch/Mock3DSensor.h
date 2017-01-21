#pragma once
#include "Motion.h" 
#include "Quaternion.h"
#include "Clock.h"
#include <utility> // Pair
using std::pair; 

class Mock3DSensor {
public: 
	double maxError; 
	Clock * clock; 
	Motion * xMotion;
	Motion * cMotion; 
	Mock3DSensor(Motion *, Motion *); 

	Quaternion getApparentPositionOfX(); 
	pair<Quaternion, double> query3DSensor(); 
	double error(); 
};