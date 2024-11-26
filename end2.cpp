#include <SFML/Graphics.hpp>
#include <iostream>

void showEnd2() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"게임 실패");

    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "폰트를 불러올 수 없습니다!" << std::endl;
        return;
    }

    sf::Text text(L"아쉽지만 목표를 달성하지 못했습니다.", font, 30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(100, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
}
