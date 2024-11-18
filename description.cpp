#include "description.h"
#include <SFML/Graphics.hpp>

// 함수 정의
sf::Font loadFontFromData() {
    sf::Font font;
    if (font.loadFromMemory(font_data, font_data_len)) {
        return font;
    }
    return sf::Font();  // 실패시 빈 폰트 반환
}

void centerText(sf::Text& text, const sf::RectangleShape& button) {
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    text.setPosition(
        buttonBounds.left + (buttonBounds.width - textBounds.width) / 2 - textBounds.left,
        buttonBounds.top + (buttonBounds.height - textBounds.height) / 2 - textBounds.top
    );
}

bool isButtonClicked(sf::RectangleShape& button, sf::Vector2i mousePos) {
    return button.getGlobalBounds().contains(sf::Vector2f(mousePos));
}

void drawDescriptionScreen(sf::RenderWindow& window, sf::Font& font, Button& backButton) {
    sf::Text descriptionText;
    descriptionText.setFont(font);
    descriptionText.setString(
        L"1. 주문에 따라 페퍼로니, 또는 포테이토 피자를 만든다.\n"
        L"2. 피자도우->토마토 소스->치즈->페퍼로니 or 포테이토 순으로 넣는다.\n"
        L"3. 오븐에 넣는다.(오븐에 넣을 시, 구워지면 자동 제출)\n\n"
        L"★순서가 틀릴 시, -1000원 / 페퍼로니 1500원, 포테이토 2000원★"
    );
    descriptionText.setCharacterSize(25);
    descriptionText.setFillColor(sf::Color::Black);
    descriptionText.setPosition(50, 50);

    // 설명 화면 그리기
    window.clear(sf::Color(255, 241, 184));
    window.draw(descriptionText);
    backButton.draw(window);
    window.display();
}
