#pragma once

#include "Mat3x3.h"

class Vec3
{
private:
	float x, y, z;

public: 
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	float& operator[](size_t index) const { return ((float*)this)[index]; }
	
	float& operator[](size_t index) { return ((float*)this)[index]; }

	Vec3& operator=(const Vec3& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;

		return *this;
	}

	Vec3 operator*(float number) const
	{
		return Vec3(x * number, y * number, z * number);
	}

	Vec3 operator/(float number) const
	{
		return Vec3(x / number, y / number, z / number);
	}

	friend Vec3 operator*(float number, const Vec3& vector)
	{
		return vector * number;
	}

	friend Vec3 operator*(const Mat3x3& matrix, const Vec3& vector)
	{ 
		const auto& m = matrix;
		const auto& v = vector;

		#define ROW(r, v) m[r * 3] * v[0] + m[r * 3 + 1] * v[1] + m[r * 3 + 2] * v[2]
		return Vec3(ROW(0, v), ROW(1, v), ROW(2, v));
		#undef ROW
	}

	Vec3 operator+(const Vec3& vector) const
	{
		return Vec3(x + vector.x, y + vector.y, z + vector.z);
	}

	Vec3 operator-(const Vec3& vector) const
	{
		return Vec3(x - vector.x, y - vector.y, z - vector.z);
	}

	void operator*=(float number)
	{
		this->x *= number; this->y *= number; this->z *= number;
	}

	void operator/=(float number)
	{
		this->x /= number; this->y /= number; this->z /= number;
	}

	void operator+=(const Vec3& vector)
	{
		*this = *this + vector;
	}

	void operator-=(const Vec3& vector)
	{
		*this = *this - vector;
	}

	float DotProduct(const Vec3& vector) const
	{
		return x * vector.x + y * vector.y + z * vector.z;
	}

	Vec3 CrossProduct(const Vec3& vector) const
	{
		return Vec3(
			y * vector.z - z * vector.y,
			z * vector.x - x * vector.z,
			x * vector.y - y * vector.x
		);
	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vec3& Normalise()
	{
		float length = Length();
		if (length != 0)
			*this /= length;

		return *this;
	}
};

