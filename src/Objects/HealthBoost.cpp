#include "HealthBoost.h"

HealthBoost::HealthBoost(sf::Texture* texture, int screen_width, int screen_height){
	this->screen_width = screen_width;
	this->screen_height = screen_height;

	boost_sprite.setTexture(*texture);
	boost_sprite.setOrigin(sf::Vector2f(boost_sprite.getLocalBounds().width / 2.0f, boost_sprite.getLocalBounds().height / 2.0f));
	boost_sprite.setPosition(screen_width + 100.0f, rand() % screen_height);

	speed = 200.0f;
	std::cout << 'h';
}

HealthBoost::~HealthBoost(){

}

void HealthBoost::Update(float dt){
	boost_sprite.move(-speed * dt, 0);
}

void HealthBoost::Render(sf::RenderWindow& window){
	window.draw(boost_sprite);
}

bool HealthBoost::IsOutOfBounds(){
	return (boost_sprite.getPosition().x < -boost_sprite.getLocalBounds().width) ? true : false;
}