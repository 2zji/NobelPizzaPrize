#include "description.h"
#include <SFML/Graphics.hpp>

// �Լ� ����
sf::Font loadFontFromData() {
    sf::Font font;
    if (font.loadFromMemory(font_data, font_data_len)) {
        return font;
    }
    return sf::Font();  // ���н� �� ��Ʈ ��ȯ
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
        L"1. �ֹ��� ���� ���۷δ�, �Ǵ� �������� ���ڸ� �����.\n"
        L"2. ���ڵ���->�丶�� �ҽ�->ġ��->���۷δ� or �������� ������ �ִ´�.\n"
        L"3. ���쿡 �ִ´�.(���쿡 ���� ��, �������� �ڵ� ����)\n\n"
        L"�ڼ����� Ʋ�� ��, -1000�� / ���۷δ� 1500��, �������� 2000����"
    );
    descriptionText.setCharacterSize(25);
    descriptionText.setFillColor(sf::Color::Black);
    descriptionText.setPosition(50, 50);

    // ���� ȭ�� �׸���
    window.clear(sf::Color(255, 241, 184));
    window.draw(descriptionText);
    backButton.draw(window);
    window.display();
}
