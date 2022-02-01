#include "Game.h"

Game::Game(sf::RenderWindow& game_window) : window(game_window){
    my_font.loadFromFile("../GIGAK NOOB/res/font.ttf");
    player_texture.loadFromFile("../GIGAK NOOB/res/ShipTexture.png");
    asteroid_texture.loadFromFile("../GIGAK NOOB/res/AsteroidTexture.png");
    bullet_texture.loadFromFile("../GIGAK NOOB/res/BulletTexture.png");
    background_texture.loadFromFile("../GIGAK NOOB/res/BackgroundTexture.jpg");
    health_texture.loadFromFile("../GIGAK NOOB/res/HealthTexture.png");

    player.shape.setTexture(player_texture);
    background.setTexture(background_texture);

    explosion_sound_buffer.loadFromFile("../GIGAK NOOB/res/ExplosionSound.wav");
    explosion_sound.setBuffer(explosion_sound_buffer);
    explosion_sound.setVolume(10.0f);

    bullet_sound_buffer.loadFromFile("../GIGAK NOOB/res/BulletSound.wav");
    bullet_sound.setBuffer(bullet_sound_buffer);
    bullet_sound.setVolume(10.0f);

    heal_sound_buffer.loadFromFile("../GIGAK NOOB/res/HealthSound.wav");
    heal_sound.setBuffer(heal_sound_buffer);
    heal_sound.setVolume(10.0f);

    score_text.setFont(my_font);
    score_text.setCharacterSize(20);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(10, 10);

    gameover_text.setFont(my_font);
    gameover_text.setCharacterSize(50);
    gameover_text.setFillColor(sf::Color::Red);
    gameover_text.setPosition(500, 400);
    gameover_text.setString("GAME OVER");

    health_text.setFont(my_font);
    health_text.setCharacterSize(20);
    health_text.setFillColor(sf::Color::Green);
    health_text.setPosition(10, 30);
}

Game::~Game(){

}

void Game::Update(float dt){
    player.Update(dt, window.getSize().x, window.getSize().y);

    // Update Asteroids
    for (int i = 0; i < asteroids.size(); i++)
        asteroids[i].Update(dt);
    asteroid_cooldown -= dt;

    // Update Bullets
    for (int i = 0; i < bullets.size(); i++)
        bullets[i].Update(dt);

    if (player.is_shooting) {
        player.is_shooting = false;
        bullets.push_back(Bullet(&bullet_texture, sf::Vector2f(player.shape.getPosition().x + player.shape.getGlobalBounds().width, player.shape.getPosition().y + player.shape.getGlobalBounds().height / 2.0f), window.getSize().x, window.getSize().y));
        bullet_sound.play();
    }

    // Collision
    for (int i = 0; i < asteroids.size(); i++){
        // Erase out of bounds asteroids
        if (asteroids[i].IsOutOfBounds()){
            asteroids.erase(asteroids.begin() + i);
            continue;
        }

        bool hit = false;
        for (int j = 0; j < bullets.size(); j++){
            // Erase out of bounds bullets
            if (bullets[j].IsOutOfBounds()){
                bullets.erase(bullets.begin() + j);
                continue;
            }

            // Erase colliding bullets
            if (bullets[j].shape.getGlobalBounds().intersects(asteroids[i].shape.getGlobalBounds())){
                bullets.erase(bullets.begin() + j);
                hit = true;
            }
        }

        // Erase colliding asteroids
        if (hit){
            asteroids.erase(asteroids.begin() + i);
            explosion_sound.play();
            score++;
        }
    }

    // Player Collision
    for (int i = 0; i < asteroids.size(); i++){
        if (asteroids[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())){
            player.Damage();
            asteroids.erase(asteroids.begin() + i);
        }
    }
    for (int i = 0; i < health_boosts.size(); i++) {
        if (health_boosts[i].boost_sprite.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
            player.Heal();
            health_boosts.erase(health_boosts.begin() + i);
            heal_sound.play();
        }
    }

    // Spawn Asteroids
    if (asteroid_cooldown <= 0.0f){
        asteroid_cooldown = 3.0f;
        asteroids.push_back(Asteroid(&asteroid_texture, window.getSize().x, window.getSize().y));
    }

    // Update Health Boosts
    health_boost_cooldown -= dt;
    for (int i = 0; i < health_boosts.size(); i++){
        health_boosts[i].Update(dt);

        // Erase out of bounds health boosts
        if (health_boosts[i].IsOutOfBounds())
            health_boosts.erase(health_boosts.begin() + i);
    }
    if (health_boost_cooldown <= 0.0f){
        health_boost_cooldown = rand() % 6 + 10;
        health_boosts.push_back(HealthBoost(&health_texture, window.getSize().x, window.getSize().y));
    }

    // Update Score and Health UI
    health_text.setString("Health: " + std::to_string(player.GetHealth()));
    score_text.setString("Score: " + std::to_string(score));

}

void Game::Render(){
    window.clear(sf::Color::Black);

    window.draw(background);

    player.Render(window);

    for (int i = 0; i < asteroids.size(); i++)
        asteroids[i].Render(window);

    for (int i = 0; i < bullets.size(); i++)
        bullets[i].Render(window);

    for (int i = 0; i < health_boosts.size(); i++)
        health_boosts[i].Render(window);

    window.draw(score_text);
    window.draw(health_text);

    window.display();
}

void Game::GameOverScreen(){
    window.draw(gameover_text);
    window.display();
}

bool Game::IsRunning(){
    return player.GetHealth() > 0 && window.isOpen();
}