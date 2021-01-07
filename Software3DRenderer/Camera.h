#pragma once

#include "Screen.h"

#include "Vec4.h"
#include "Vec3.h"
#include "Vec2.h"

class Camera
{
private:
	Vec3 position;
	Vec3 viewAngles;

	float FOV;

public:
	Camera(Vec3 position, Vec3 viewAngles, float FOV)
		: position(position), viewAngles(viewAngles), FOV(FOV) {}

	float GetFOV() const;
	const Vec3& GetViewAngles() const;
	Vec3 GetViewVector() const;
	const Vec3& GetPosition() const;
	const float GetYaw() const;
	const float GetPitch() const;

	Camera& SetPosition(Vec3 position);
	Camera& SetViewAngles(Vec3 viewAngles);

	Camera& Move(Vec3 delta);
	Camera& MoveForward(float amount);
	Camera& MoveBackward(float amount);
	Camera& MoveLeft(float amount);
	Camera& MoveRight(float amount);
	Camera& Rotate(Vec3 delta);
	Camera& ClipAngles();

	Vec3 ToCameraCoordinates(const Vec3& vector) const;
	Vec3 ApplyProjection(const Screen& screen, const Vec3& vector) const;

	Vec2 WorldToScreen(const Screen& screen, const Vec3& vector) const;
	Vec2 WorldToScreen(const Screen& screen, const Vec4& vector) const;
};

