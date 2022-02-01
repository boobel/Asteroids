#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class HealthBoost
{
public:
	HealthBoost(sf::Texture* texture, int screen_width, int screen_height);
	~HealthBoost();

	void Update(float dt);
	void Render(sf::RenderWindow& window);

	bool IsOutOfBounds();

	sf::Sprite boost_sprite;
private:
	int screen_width, screen_height;
	float speed;
};