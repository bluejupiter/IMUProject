#pragma once
#include "Motion.h" 
#include "Quaternion.h"
#include <utility> // Pair

class Mock3DSensor {
public: 
	Motion * xMotion;
	Motion * cMotion; 
	Mock3DSensor(Motion *, Motion *); 

	Quaternion getApparentPositionOfX(); 
};