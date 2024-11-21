#include <SFML/Graphics.hpp>
#include <iostream>

void startGame();

void showDescription() {
    sf::RenderWindow descriptionWindow(sf::VideoMode(800, 600), L"노벨피자상");

    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "폰트를 불러올 수 없습니다!" << std::endl;
        return;
    }

    // 게임 설명 텍스트
    sf::Text description(L"1. 주문에 따라 페퍼로니, 또는 포테이토 피자를 만든다.\n"
        L"2. 피자도우->토마토 소스->치즈->페퍼로니 or 포테이토 순으로 넣는다.\n"
        L"3. 오븐에 넣는다.(오븐에 넣을 시, 구워지면 자동 제출)\n\n"
        L"★순서가 틀릴 시, -1000원 / 페퍼로니 1500원, 포테이토 2000원★", font, 20);
    description.setFillColor(sf::Color::Black);
    description.setPosition(50, 100);

    // 게임 시작 버튼
    sf::RectangleShape startButtonBox(sf::Vector2f(200, 50));
    startButtonBox.setFillColor(sf::Color(234, 187, 101));
    startButtonBox.setPosition(300, 450);

    sf::Text startButtonText(L"게임 시작", font, 30);
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

                    // 게임 시작 버튼 클릭 처리
                    if (startButtonBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        descriptionWindow.close();
                        startGame();
                    }
                }
            }
        }

        descriptionWindow.clear(sf::Color(255, 241, 184)); // 배경색
        descriptionWindow.draw(description);
        descriptionWindow.draw(startButtonBox);
        descriptionWindow.draw(startButtonText);
        descriptionWindow.display();
    }
}