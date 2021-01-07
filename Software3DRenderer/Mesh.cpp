#include "Mesh.h"
#include <stdlib.h>

void Mesh::Draw(Camera camera, Screen& screen)
{
	for (auto i = 0; i < vertices.size() / 3; i++)
	{
		sf::ConvexShape convex;
		convex.setPointCount(3);
		convex.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		//convex.setFillColor(sf::Color::White);

		Vec3 vec1 = vertices[i * 3] - vertices[i * 3 + 1];
		Vec3 vec2 = vertices[i * 3 + 2] - vertices[i * 3 + 1];
		Vec3 normal = vec1.CrossProduct(vec2);
		float collinearity = normal.DotProduct(vertices[i * 3] - camera.GetPosition());
		if (collinearity < 0)
			continue;

		bool shouldContinue = false;
		std::array<Vec2, 3> triangle =
		{
			camera.WorldToScreen(screen, vertices[i * 3]),
			camera.WorldToScreen(screen, vertices[i * 3 + 1]),
			camera.WorldToScreen(screen, vertices[i * 3 + 2])
		};

		for (auto vertex : triangle)
			if (vertex[0] == -1 && vertex[1] == -1)
			{
				shouldContinue = true;
				break;
			}

		if (shouldContinue)
			continue;

		convex.setPoint(0, sf::Vector2f(triangle[0][0], triangle[0][1]));
		convex.setPoint(1, sf::Vector2f(triangle[1][0], triangle[1][1]));
		convex.setPoint(2, sf::Vector2f(triangle[2][0], triangle[2][1]));

		//sf::Vertex* line = 
		//	new sf::Vertex[2] {
		//	sf::Vector2f(triangle[0][0], triangle[0][1]),
		//	sf::Vector2f(triangle[1][0], triangle[1][1])
		//};
		//screen.GetWindow().draw(line, 2, sf::Lines);
		//delete[] line;
		//line =
		//	new sf::Vertex[2]{
		//	sf::Vector2f(triangle[0][0], triangle[0][1]),
		//	sf::Vector2f(triangle[2][0], triangle[2][1])
		//};
		//screen.GetWindow().draw(line, 2, sf::Lines);
		//delete[] line;
		//line = 
		//	new sf::Vertex[2]{
		//	sf::Vector2f(triangle[1][0], triangle[1][1]),
		//	sf::Vector2f(triangle[2][0], triangle[2][1])
		//};
		//screen.GetWindow().draw(line, 2, sf::Lines);
		//delete[] line;
		screen.GetWindow().draw(convex);
	}
}
