#pragma once

#include <array>

typedef std::array<float, 16> Mat4x4;

Mat4x4 ProjectionMatrix(float aratio, float FOV);