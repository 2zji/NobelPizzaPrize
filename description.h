#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <SFML/Graphics.hpp>

// �Լ� ���� �մϴ�.
void drawDescriptionScreen(sf::RenderWindow& window, sf::Font& font, class Button& backButton);
void centerText(sf::Text& text, const sf::RectangleShape& button);
bool isButtonClicked(sf::RectangleShape& button, sf::Vector2i mousePos);
sf::Font loadFontFromData();

// ��Ʈ ������ �ܺ� ����
extern unsigned char font_data[];
extern unsigned int font_data_len;

#endif
