#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <SFML/Graphics.hpp>

// 함수 선언만 합니다.
void drawDescriptionScreen(sf::RenderWindow& window, sf::Font& font, class Button& backButton);
void centerText(sf::Text& text, const sf::RectangleShape& button);
bool isButtonClicked(sf::RectangleShape& button, sf::Vector2i mousePos);
sf::Font loadFontFromData();

// 폰트 데이터 외부 선언
extern unsigned char font_data[];
extern unsigned int font_data_len;

#endif
