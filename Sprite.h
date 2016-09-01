#pragma once

#include <vector>

#include "Point.h"
#include "util.h"

class Sprite{
	public:
	Sprite();
	virtual ~Sprite();
	
	virtual void draw();

	Point pos; 
	float rotation;
	float scale;
};
