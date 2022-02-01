#pragma once

#include "SFML/Graphics.hpp"
#include "Bullet.h"

class Player {
public:
    Player();
    ~Player();

    void Update(float dt, int screen_width, int screen_height);
    void Render(sf::RenderWindow& window);

    void Heal();
    void Damage();

    bool IsAlive();
    int GetHealth();

    bool is_shooting;

    sf::Sprite shape;

private:
    int score;
    float cooldown;

    int HP;
    int HPM;
    float speed;
};