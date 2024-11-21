#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Game.h"
#include "Description.h"

class MainMenu {
public:
    MainMenu();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text title;
    sf::RectangleShape startButtonBox, descriptionButtonBox;
    sf::Text startButtonText, descriptionButtonText;

    void handleEvents();
    void render();
};

#endif // MAINMENU_H
