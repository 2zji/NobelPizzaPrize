#include "description.h"

// 설명 화면을 렌더링하는 함수 정의
void drawDescriptionScreen(sf::RenderWindow& window, sf::Font& font) {
    sf::Text descriptionText;
    descriptionText.setFont(font);
    descriptionText.setString(
        L"게임 설명\n\n"
        L"1. 주문된 피자를 만드세요.\n"
        L"2. 제한 시간은 60초입니다.\n"
        L"3. 피자를 잘 만들면 점수를 얻습니다.\n\n"
        L"ESC를 눌러 돌아가기");
    descriptionText.setCharacterSize(25);
    descriptionText.setFillColor(sf::Color::Black);
    descriptionText.setPosition(50, 50);

    window.draw(descriptionText);
}
