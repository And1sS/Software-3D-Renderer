#pragma once

#include "Mat4x4.h"
#include "Vec3.h"

class Vec4
{
private:
	float x, y, z, w;

public:
	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	Vec4(Vec3 vector) : Vec4(vector[0], vector[1], vector[2], 1) {}
	
	Vec4(float x, float y, float z) : Vec4(x, y, z, 1) {}

	float& operator[](size_t index) const { return ((float*)this)[index]; }

	float& operator[](size_t index) { return ((float*)this)[index]; }

	Vec4 operator=(const Vec4& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;
		this->w = vector.w;
	}

	Vec4 operator*(float number) const 
	{ 
		return Vec4(x * number, y * number, z * number, w * number); 
	}

	friend Vec4 operator*(float number, const Vec4& vector)
	{
		return vector * number;
	}

	friend Vec4 operator*(const Mat4x4& matrix, const Vec4& vector)
	{
		const auto& m = matrix;
		const auto& v = vector;

		#define ROW(r, v) m[r * 4] * v[0] + m[r * 4 + 1] * v[1] \
				 + m[r * 4 + 2] * v[2] + m[r * 4 + 3] * v[3]
		return Vec4(ROW(0, v), ROW(1, v), ROW(2, v), ROW(3, v));
		#undef ROW
	}

	Vec4 operator+(const Vec4& vector) const 
	{ 
		return Vec4(x + vector.x, y + vector.y, z + vector.z, w + vector.w); 
	}

	Vec4 operator-(const Vec4& vector) const 
	{ 
		return Vec4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
	}

	void operator*=(float number)
	{
		this->x *= number;
		this->y *= number;
		this->z *= number;
		this->w *= number;
	}

	void operator+=(const Vec4& vector) 
	{
		*this = *this + vector;
	}

	void operator-=(const Vec4& vector) 
	{
		*this = *this - vector;
	}
};

