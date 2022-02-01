#include "Asteroid.h"

Asteroid::Asteroid(sf::Texture* texture, int screen_width, int screen_height){
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    HPM = rand() % 3 + 1;
    HP = HPM;
    speed = 200.0f;

    shape.setTexture(*texture);
    shape.setPosition(screen_width + 100.0f, rand() % (screen_height - (int)shape.getLocalBounds().height));
}

Asteroid::~Asteroid(){

}

void Asteroid::Update(float dt){
    shape.move(-speed * dt, 0);
}

void Asteroid::Render(sf::RenderWindow& window){
    window.draw(shape);
}

bool Asteroid::IsOutOfBounds(){
    return (shape.getPosition().x < -shape.getLocalBounds().width) ? true : false;
}