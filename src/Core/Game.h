#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <string>

#include "../Objects/Player.h"
#include "../Objects/Asteroid.h"
#include "../Objects/Bullet.h"
#include "../Objects/HealthBoost.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();

	void Update(float dt);
	void Render();
	void GameOverScreen();

	bool IsRunning();

private:
	sf::RenderWindow& window;

	// Game Objects
	Player player;
	std::vector<Bullet> bullets;
	std::vector<Asteroid> asteroids;
	std::vector<HealthBoost> health_boosts;

	// Resources
	sf::Font my_font;
	sf::Texture player_texture;
	sf::Texture asteroid_texture;
	sf::Texture bullet_texture;
	sf::Texture background_texture;
	sf::Sprite background;
	sf::Texture health_texture;
	sf::SoundBuffer explosion_sound_buffer;
	sf::Sound explosion_sound;
	sf::SoundBuffer bullet_sound_buffer;
	sf::Sound heal_sound;
	sf::SoundBuffer heal_sound_buffer;
	sf::Sound bullet_sound;
	sf::Text score_text;
	sf::Text gameover_text;
	sf::Text health_text;

	// Variables
	float asteroid_cooldown = 3.0f;
	float health_boost_cooldown = rand() % 6 + 10;

	int score;
};