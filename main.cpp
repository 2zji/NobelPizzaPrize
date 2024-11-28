#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "game.h"

void startGame();
void showDescription();

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"�뺧���ڻ�");

    // ��Ʈ ����
    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return -1;
    }

    // Ÿ��Ʋ �ؽ�Ʈ
    sf::Text title(L"�뺧���ڻ�", font, 50);
    title.setFillColor(sf::Color::Black);
    title.setPosition(240, 100);

    // ���� ��ư
    sf::RectangleShape startButtonBox(sf::Vector2f(200, 50));
    startButtonBox.setFillColor(sf::Color(234, 187, 101));
    startButtonBox.setPosition(300, 200);

    sf::Text startButtonText(L"���� ����", font, 30);
    startButtonText.setFillColor(sf::Color::Black);
    startButtonText.setPosition(320, 205);

    // ���� ���� ��ư
    sf::RectangleShape descriptionButtonBox(sf::Vector2f(200, 50));
    descriptionButtonBox.setFillColor(sf::Color(234, 187, 101));
    descriptionButtonBox.setPosition(300, 300);

    sf::Text descriptionButtonText(L"���� ����", font, 30);
    descriptionButtonText.setFillColor(sf::Color::Black);
    descriptionButtonText.setPosition(320, 305);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // ���� ��ư Ŭ�� ó��
                    if (startButtonBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();
                        startGame();
                    }

                    // ���� ���� ��ư Ŭ�� ó��
                    if (descriptionButtonBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();
                        showDescription();
                    }
                }
            }
        }

        window.clear(sf::Color(255, 241, 184));
        window.draw(title);
        window.draw(startButtonBox);
        window.draw(startButtonText);
        window.draw(descriptionButtonBox);
        window.draw(descriptionButtonText);
        window.display();
    }

    return 0;
}
