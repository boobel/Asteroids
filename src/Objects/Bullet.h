#pragma once

#include "SFML/Graphics.hpp"

class Bullet {
public:
    Bullet(sf::Texture* texture, sf::Vector2f pos, int screen_width, int screen_height);
    ~Bullet();

    void Update(float dt);
    void Render(sf::RenderWindow& window);

    bool IsOutOfBounds();

    sf::Sprite shape;

private:
    int screen_width, screen_height;
    float speed;
};