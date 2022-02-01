#include "Player.h"

Player::Player(){
    HPM = 10;
    HP = HPM;
    speed = 10.0f;

    shape.setScale(0.5, 0.5);
}

Player::~Player(){

}

void Player::Update(float dt, int screen_width, int screen_height){
    cooldown -= dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && shape.getPosition().y > 0)
        shape.move(0, -speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && shape.getPosition().x > 0)
        shape.move(-speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && shape.getPosition().y + shape.getLocalBounds().height / 2.0f < screen_height)
        shape.move(0, speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && shape.getPosition().x + shape.getLocalBounds().width / 2.0f < screen_width)
        shape.move(speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && cooldown <= 0.0f)
    {
        is_shooting = true;
        cooldown = 0.2f;
    }
}

void Player::Render(sf::RenderWindow& window){
    window.draw(shape);
}

void Player::Heal(){
    HP += (HP <= 90) ? 10 : 0;
}

void Player::Damage(){
    HP -= 10;
}

bool Player::IsAlive(){
    return (HP > 0) ? true : false;
}

int Player::GetHealth(){
    return HP;
}