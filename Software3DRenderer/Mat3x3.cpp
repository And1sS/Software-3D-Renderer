#include "Mat3x3.h"

Mat3x3 RotationMatrixXY(float degrees) // angle with x axis
{
	float rad = DEG_TO_RAD(degrees);
	return Mat3x3
	{ 
		cosf(rad), -sinf(rad), 0, 
		sinf(rad),  cosf(rad), 0,
			   0,         0, 1
	};
}

Mat3x3 RotationMatrixXZ(float degrees) // angle with x axis
{
	float rad = DEG_TO_RAD(degrees);
	return Mat3x3
	{
		cosf(rad), 0, -sinf(rad),
		       0, 1,         0,
		sinf(rad), 0,   cosf(rad)
	};
}
