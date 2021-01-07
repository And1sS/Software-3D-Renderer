#pragma once

#include "Mat2x2.h"

class Vec2
{
private:
	float x, y;

public:
	Vec2(float x, float y) : x(x), y(y) {}

	float& operator[](size_t index) const { return ((float*)this)[index]; }

	float& operator[](size_t index) { return ((float*)this)[index]; }

	Vec2 operator=(const Vec2& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
	}

	Vec2 operator*(float number) const
	{
		return Vec2(x * number, y * number);
	}

	friend Vec2 operator*(float number, const Vec2& vector)
	{
		return vector * number;
	}

	friend Vec2 operator*(const Mat2x2& matrix, const Vec2& vector)
	{
		const auto& m = matrix;
		const auto& v = vector;

		#define ROW(r, v) m[r * 2] * v[0] + m[r * 2 + 1] * v[1]
		return Vec2(ROW(0, v), ROW(1, v));
		#undef ROW
	}

	Vec2 operator+(const Vec2& vector) const
	{
		return Vec2(x + vector.x, y + vector.y);
	}

	Vec2 operator-(const Vec2& vector) const
	{
		return Vec2(x - vector.x, y - vector.y);
	}

	void operator*=(float number)
	{
		this->x *= number;
		this->y *= number;
	}

	void operator+=(const Vec2& vector)
	{
		*this = *this + vector;
	}

	void operator-=(const Vec2& vector)
	{
		*this = *this - vector;
	}
};