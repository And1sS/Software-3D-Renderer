#pragma once

#include "Vec3.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include <array>

class Mesh
{
private:
	std::vector<Vec3> vertices;

public:
	Mesh(const std::vector<Vec3>& vertices) : vertices(vertices) {}

	void Draw(Camera camera, Screen& screen);
};