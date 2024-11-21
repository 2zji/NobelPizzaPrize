#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;

    void handleEvents();
    void gameLoop();
};

#endif // GAME_H
