#include <SFML/Graphics.hpp>
#include <iostream>

void showEnd2() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"���� ����");

    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return;
    }

    sf::Text text(L"�ƽ����� ��ǥ�� �޼����� ���߽��ϴ�.", font, 30);
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
