#include <SFML/Graphics.hpp>
#include <iostream>
#include "font_data.cpp"  // font_data.cpp ����
#include "description.h"

// ��Ʈ ������ �Ἥ sf::Font ��ü�� ��ȯ�ϴ� �Լ� (�޸𸮿� ���� �ҷ���)
sf::Font loadFontFromData() {
    sf::Font font;
    if (font.loadFromMemory(font_data, font_data_len)) {
        return font;
    }
    else {
        // ��Ʈ �ε� ���� �� �⺻ ��Ʈ�� ��ȯ or ����
        sf::Font defaultFont;
        defaultFont.loadFromFile("BagelFatOne-Regular.ttf");    //BagelFatOne-Regular(�ܺ� �ٿ�)���
        return defaultFont;
    }
}

// ��ư�� Ŭ���ߴ��� Ȯ���ϴ� �Լ� (����ڰ� Ŭ���� ��ġ�� ��ư ���� �ȿ� �ִ��� Ȯ��)
bool isButtonClicked(sf::RectangleShape& button, sf::Vector2i mousePos) {
    return button.getGlobalBounds().contains(sf::Vector2f(mousePos));
}

int main() {
    // â �����
    sf::RenderWindow window(sf::VideoMode(800, 600), L"�뺧���ڻ�");

    // ��Ʈ �ε�
    sf::Font font = loadFontFromData();

    // �ؽ�Ʈ ����
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString(L"�뺧���ڻ�");  //""�տ� L ���̸� �ѱ� ��� �� �ʤ���
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(300, 100);

    // ���� ��ư ����
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color(234, 187, 101));
    startButton.setPosition(300, 200);

    //���� ��ư �ؽ�Ʈ ����
    sf::Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString(L"���� ����");
    startButtonText.setCharacterSize(30);
    startButtonText.setFillColor(sf::Color::Black);
    startButtonText.setPosition(330, 210);

    // ���� ���� ��ư ����
    sf::RectangleShape instructionsButton(sf::Vector2f(200, 50));
    instructionsButton.setFillColor(sf::Color(234, 187, 101));
    instructionsButton.setPosition(300, 300);

    //���� ���� ��ư �ؽ�Ʈ ����
    sf::Text instructionsButtonText;
    instructionsButtonText.setFont(font);
    instructionsButtonText.setString(L"���� ����");
    instructionsButtonText.setCharacterSize(30);
    instructionsButtonText.setFillColor(sf::Color::Black);
    instructionsButtonText.setPosition(320, 310);

    // ���� ���� (â�� ���� �ִ� ���� ���� ����)
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // ���콺 Ŭ�� �̺�Ʈ ó�� (Ŭ���� ��ġ�� Ȯ��)
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // ���� ��ư Ŭ��
                if (isButtonClicked(startButton, mousePos)) {
                    // ���� ���� �ڵ�� �̵�
                    titleText.setString(L"���� ����");
                }

                // ���� ���� ��ư Ŭ��
                if (isButtonClicked(instructionsButton, mousePos)) {
                    // ���� ���� �ڵ�� �̵�
                    titleText.setString(L"���� ����: ���ڷ� �뺧�� �ޱ�!");
                }
            }
        }

        // â �׸���
        window.clear(sf::Color(255, 241, 184));  // ��� ���� ����
        window.draw(titleText);          // ���� �ؽ�Ʈ
        window.draw(startButton);        // ���� ��ư
        window.draw(startButtonText);    // ���� ��ư �ؽ�Ʈ
        window.draw(instructionsButton); // ���� ���� ��ư
        window.draw(instructionsButtonText);  // ���� ���� ��ư �ؽ�Ʈ
        window.display();
    }

    return 0;
}
