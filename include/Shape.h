#pragma once

#include "ViewPortGL.h"

class Shape {
public:
	Shape(int red, int green, int blue);
	virtual void prepare(ViewPortGL& vp, int centerX, int centerY, int size) = 0;

protected:
	int red, green, blue;
};

