#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

#include "Core/Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Space Invader!");
    window.setFramerateLimit(60);

    Game game(window);
    
    // Clock
    sf::Clock dclock;

    while (game.IsRunning()) {
        // Handle Events
        sf::Event e;
        while (window.pollEvent(e)) {
            // Input
            switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        // Update
        float dt = dclock.restart().asSeconds();
        game.Update(dt);

        // Render
        game.Render();
    }

    game.GameOverScreen();

    while (window.isOpen()){
        sf::Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
    }

    return 0;
}