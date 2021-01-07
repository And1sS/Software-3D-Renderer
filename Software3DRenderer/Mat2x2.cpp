#include <cmath>
#include "Mat2x2.h"

Mat2x2 RotationMatrix(float degrees)
{
	return Mat2x2
	{ 
		cos(degrees), -sin(degrees),
		sin(degrees), cos(degrees) 
	};
}