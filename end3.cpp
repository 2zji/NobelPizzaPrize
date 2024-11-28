#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "Success!");

    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        return -1;
    }

    sf::Text message;
    message.setFont(font);
    message.setString("Congratulations! You earned over 10,000 Won!");
    message.setCharacterSize(20);
    message.setFillColor(sf::Color::Green);
    message.setPosition(20, 80);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(message);
        window.display();
    }

    return 0;
}
