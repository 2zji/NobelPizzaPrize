#include <SFML/Graphics.hpp>
#include <iostream>

void startGame() {
    sf::RenderWindow gameWindow(sf::VideoMode(800, 600), L"���� ����� ����");

    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }

        gameWindow.clear(sf::Color::White);
        // ���� ���� ���� �߰�
        gameWindow.display();
    }
}
