#include <SFML/Graphics.hpp>
#include <iostream>
#include "end.h"

void showEnd1() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"게임 성공");

    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "폰트를 불러올 수 없습니다!" << std::endl;
        return;
    }

    sf::Text text(L"축하합니다! 목표를 달성했습니다!", font, 30);
    text.setFillColor(sf::Color::Green);
    text.setPosition(150, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 241, 184));
        window.draw(text);
        window.display();
    }
}
