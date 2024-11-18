#include <SFML/Graphics.hpp>
#include "description.h"
#include "common.h" // isButtonClicked �Լ� ����

// ���� �Լ�
int main() {
    // â ����
    sf::RenderWindow window(sf::VideoMode(800, 600), L"�뺧���ڻ�");

    // ��Ʈ �ε�
    sf::Font font = loadFontFromData();

    // ���� �ؽ�Ʈ ����
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString(L"�뺧���ڻ�");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(300, 100);

    // ���� ��ư ����
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color(234, 187, 101));
    startButton.setPosition(300, 200);

    sf::Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString(L"���� ����");
    startButtonText.setCharacterSize(30);
    startButtonText.setFillColor(sf::Color::Black);
    centerText(startButtonText, startButton);

    // ���� ���� ��ư ����
    sf::RectangleShape instructionsButton(sf::Vector2f(200, 50));
    instructionsButton.setFillColor(sf::Color(234, 187, 101));
    instructionsButton.setPosition(300, 300);

    sf::Text instructionsButtonText;
    instructionsButtonText.setFont(font);
    instructionsButtonText.setString(L"���� ����");
    instructionsButtonText.setCharacterSize(30);
    instructionsButtonText.setFillColor(sf::Color::Black);
    centerText(instructionsButtonText, instructionsButton);

    // �ڷ� ���� ��ư ���� (���� ȭ���)
    Button backButton(
        sf::Vector2f(200, 50), sf::Vector2f(300, 500), sf::Color(200, 100, 100),
        L"�ڷ� ����", font, 30, sf::Color::White
    );

    bool showDescription = false;

    // ���� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (!showDescription) {
                    // ���� ��ư Ŭ��
                    if (isButtonClicked(startButton, mousePos)) {
                        titleText.setString(L"������ ���۵˴ϴ�!");
                    }

                    // ���� ���� ��ư Ŭ��
                    if (isButtonClicked(instructionsButton, mousePos)) {
                        showDescription = true; // ���� ȭ������ ��ȯ
                    }
                }
                else {
                    // �ڷ� ���� ��ư Ŭ��
                    if (backButton.isClicked(mousePos)) {
                        showDescription = false; // ���� ȭ������ ���ư���
                    }
                }
            }
        }

        // ȭ�� �׸���
        window.clear(sf::Color(255, 241, 184));

        if (!showDescription) {
            // ���� ȭ��
            window.draw(titleText);
            window.draw(startButton);
            window.draw(startButtonText);
            window.draw(instructionsButton);
            window.draw(instructionsButtonText);
        }
        else {
            // ���� ȭ��
            drawDescriptionScreen(window, font, backButton);
        }

        window.display();
    }

    return 0;
}
