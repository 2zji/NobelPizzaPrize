#include "description.h"

// 설명 화면을 그리는 함수 정의
void drawDescriptionScreen(sf::RenderWindow& window, sf::Font& font, sf::RectangleShape& startButton, sf::Text& startButtonText) {
    sf::Text descriptionText;
    descriptionText.setFont(font);
    descriptionText.setString(
        L"1. 주문에 따라 페퍼로니, 또는 포테이토 피자를 만든다.\n"
        L"2. 피자도우->토마토 소스->치즈->페퍼로니 or 포테이토 순으로 넣는다.\n"
        L"3. 오븐에 넣는다.(오븐에 넣을 시, 구워지면 자동 제출)\n\n"
        L"★순서가 틀릴 시, -1000원 / 페퍼로니 1500원, 포테이토 2000원★");
    descriptionText.setCharacterSize(25);
    descriptionText.setFillColor(sf::Color::Black);
    descriptionText.setPosition(50, 50);

    // 설명 화면에 필요한 요소 그리기
    window.draw(descriptionText);
    window.draw(startButton);
    window.draw(startButtonText);
}
