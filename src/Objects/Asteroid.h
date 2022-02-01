#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Asteroid {
public:
    Asteroid(sf::Texture* texture, int screen_width, int screen_height);
    ~Asteroid();

    void Update(float dt);
    void Render(sf::RenderWindow& window);

    bool IsOutOfBounds();

    sf::Sprite shape;

private:
    int screen_width, screen_height;
    float speed;

    float HP;
    float HPM;
};