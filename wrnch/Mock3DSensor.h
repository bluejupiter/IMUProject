#pragma once
#include "Motion.h"; 
#include "Quaternion.h"

class Mock3DSensor {
public: 
	Motion xMotion;
	Motion cMotion; 
	Mock3DSensor(Motion &, Motion &); 

	Quaternion getApparentPositionOfX(); 
};