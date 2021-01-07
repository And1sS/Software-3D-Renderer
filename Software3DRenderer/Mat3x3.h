#pragma once

#include <array>

#define M_PI 3.141592653f
#define DEG_TO_RAD(x) (x) / 180 * M_PI

typedef std::array<float, 9> Mat3x3;

Mat3x3 RotationMatrixXY(float degrees);
Mat3x3 RotationMatrixXZ(float degrees);
Mat3x3 RotationMatrixYZ(float degrees);