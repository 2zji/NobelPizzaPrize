#include <SFML/Graphics.hpp>
#include <iostream>

void startGame();

void showDescription() {
    sf::RenderWindow descriptionWindow(sf::VideoMode(800, 600), L"�뺧���ڻ�");

    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return;
    }

    // ���� ���� �ؽ�Ʈ
    sf::Text description(L"1. �ֹ��� ���� ���۷δ�, �Ǵ� �������� ���ڸ� �����.\n"
        L"2. ���ڵ���->�丶�� �ҽ�->ġ��->���۷δ� or �������� ������ �ִ´�.\n"
        L"3. ���쿡 �ִ´�.(���쿡 ���� ��, �������� �ڵ� ����)\n\n"
        L"�ڼ����� Ʋ�� ��, -1000�� / ���۷δ� 1500��, �������� 2000����", font, 20);
    description.setFillColor(sf::Color::Black);
    description.setPosition(50, 100);

    // ���� ���� ��ư
    sf::RectangleShape startButtonBox(sf::Vector2f(200, 50));
    startButtonBox.setFillColor(sf::Color(234, 187, 101));
    startButtonBox.setPosition(300, 450);

    sf::Text startButtonText(L"���� ����", font, 30);
    startButtonText.setFillColor(sf::Color::Black);
    startButtonText.setPosition(330, 455);

    while (descriptionWindow.isOpen()) {
        sf::Event event;
        while (descriptionWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                descriptionWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(descriptionWindow);

                    // ���� ���� ��ư Ŭ�� ó��
                    if (startButtonBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        descriptionWindow.close();
                        startGame();
                    }
                }
            }
        }

        descriptionWindow.clear(sf::Color(255, 241, 184)); // ����
        descriptionWindow.draw(description);
        descriptionWindow.draw(startButtonBox);
        descriptionWindow.draw(startButtonText);
        descriptionWindow.display();
    }
}