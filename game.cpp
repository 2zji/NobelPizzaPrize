#include <SFML/Graphics.hpp>
#include <iostream>

void startGame() {
    sf::RenderWindow gameWindow(sf::VideoMode(800, 600), L"피자 만들기 게임");

    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }

        gameWindow.clear(sf::Color::White);
        // 게임 관련 로직 추가
        gameWindow.display();
    }
}
