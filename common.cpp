#include "common.h"

Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, const sf::String& text, sf::Font& font, unsigned int textSize, sf::Color textColor) {
    buttonShape.setSize(size);
    buttonShape.setPosition(position);
    buttonShape.setFillColor(color);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(textSize);
    buttonText.setFillColor(textColor);
    // 텍스트를 버튼의 중앙에 정렬
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    sf::FloatRect buttonBounds = buttonShape.getGlobalBounds();
    buttonText.setPosition(buttonBounds.left + (buttonBounds.width - textBounds.width) / 2 - textBounds.left, buttonBounds.top + (buttonBounds.height - textBounds.height) / 2 - textBounds.top);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(buttonShape);
    window.draw(buttonText);
}

bool Button::isClicked(sf::Vector2i mousePos) {
    return buttonShape.getGlobalBounds().contains(sf::Vector2f(mousePos));
}
