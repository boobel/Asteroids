#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, sf::Vector2f pos, int screen_width, int screen_height){
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    shape.setTexture(*texture);
    shape.setScale(1.5f, 1.5f);
    shape.setPosition(pos);
    shape.setOrigin(sf::Vector2f(shape.getLocalBounds().width / 2.0f, shape.getLocalBounds().height / 2.0f));

    speed = 550.0f;
}

Bullet::~Bullet(){

}

void Bullet::Update(float dt){
    shape.move(speed * dt, 0);
}

void Bullet::Render(sf::RenderWindow& window){
    window.draw(shape);
}

bool Bullet::IsOutOfBounds(){
    return (shape.getPosition().x > screen_width) ? true : false;
}