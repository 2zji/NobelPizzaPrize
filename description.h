#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Game.h"

class Description {
public:
    Description();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text descriptionText;
    sf::RectangleShape startButtonBox;
    sf::Text startButtonText;

    void handleEvents();
    void render();
};

#endif // DESCRIPTION_H
