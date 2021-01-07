#include "Camera.h"
#include <cmath>

float Camera::GetFOV() const
{
	return FOV;
}

const Vec3& Camera::GetViewAngles() const
{
	return viewAngles;
}

Vec3 Camera::GetViewVector() const
{
	return Vec3{
		std::cos(DEG_TO_RAD(GetPitch())) * std::cos(DEG_TO_RAD(GetYaw())),
		std::cos(DEG_TO_RAD(GetPitch())) * std::sin(DEG_TO_RAD(GetYaw())),
		std::sin(DEG_TO_RAD(GetPitch()))
	};
}

const Vec3& Camera::GetPosition() const
{
	return position;
}

const float Camera::GetYaw() const
{
	return viewAngles[0];
}

const float Camera::GetPitch() const
{
	return viewAngles[1];
}

Camera& Camera::SetPosition(Vec3 position)
{
	this->position = position;
	return *this;
}

Camera& Camera::SetViewAngles(Vec3 viewAngles)
{
	this->viewAngles = viewAngles;
	return *this;
}

Camera& Camera::Move(Vec3 delta)
{
	position += delta;
	return *this;
}

Camera& Camera::MoveForward(float amount)
{
	Move(amount * GetViewVector());
	return *this;
}

Camera& Camera::MoveBackward(float amount)
{
	MoveForward(-amount);
	return *this;
}

Camera& Camera::MoveLeft(float amount)
{
	MoveRight(-amount);
	return *this;
}

Camera& Camera::MoveRight(float amount)
{
	Move({
		amount * std::cos(DEG_TO_RAD(GetPitch())) * std::cos(DEG_TO_RAD(GetYaw() + 90)),
		amount * std::cos(DEG_TO_RAD(GetPitch())) * std::sin(DEG_TO_RAD(GetYaw() + 90)),
		0
	});
	return *this;
}

Camera& Camera::Rotate(Vec3 delta)
{
	viewAngles += delta;
	ClipAngles();

	return *this;
}

Camera& Camera::ClipAngles()
{
	if (viewAngles[0] >= 180)
		viewAngles[0] -= 360;
	else if (viewAngles[0] <= -180)
		viewAngles[0] += 360;

	if (viewAngles[1] >= 90)
		viewAngles[1] = 90;
	else if (viewAngles[1] <= -90)
		viewAngles[1] = -90;

	return *this;
}

Vec3 Camera::ToCameraCoordinates(const Vec3& vector) const
{
	return RotationMatrixXZ(-GetPitch()) *
		(RotationMatrixXY(-GetYaw()) * (vector - position));
}

Vec3 Camera::ApplyProjection(const Screen& screen, const Vec3& vector) const
{
	float scaler = 1 / tan(DEG_TO_RAD(FOV / 2));

	return Vec3(
		vector[1] * screen.GetAspectRatio() * scaler / vector[0],
		vector[2] * scaler / vector[0],
		0);
}

Vec2 Camera::WorldToScreen(const Screen& screen, const Vec3& vector) const
{
	Vec3 relative = ToCameraCoordinates(vector);
	float scaler = 1 / tan(DEG_TO_RAD(FOV / 2));

	if (relative[0] < scaler / 2)
		return Vec2(-1, -1);
	
	Vec3 screenPosition = ApplyProjection(screen, relative);

	return Vec2(
		(screenPosition[0] + 1) * screen.GetWidth() / 2.0f, 
		(1 - screenPosition[1]) * screen.GetHeight() / 2.0f);
}

Vec2 Camera::WorldToScreen(const Screen& screen, const Vec4& vector) const
{
	return Vec2(0, 0);
}
