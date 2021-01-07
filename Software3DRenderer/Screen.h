#pragma once

#include <SFML/Graphics.hpp>

class Screen
{
private:
	int width, height;
	sf::RenderWindow window;

public:
	Screen(int width, int height, std::string title) 
		: width(width), height(height), window(sf::VideoMode(width, height), title) {}

	float GetAspectRatio() const { return (float) height / width; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	sf::RenderWindow& GetWindow() { return window; }
};