#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.hpp>

// Button 클래스 선언
class Button {
public:
    Button(sf::Vector2f size, sf::Vector2f position, sf::Color color, const sf::String& text, sf::Font& font, unsigned int textSize, sf::Color textColor);
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2i mousePos);

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
};

#endif
