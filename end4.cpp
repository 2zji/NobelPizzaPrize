#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "Failure...");

    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        return -1;
    }

    sf::Text message;
    message.setFont(font);
    message.setString("You failed to earn 10,000 Won. Try again!");
    message.setCharacterSize(20);
    message.setFillColor(sf::Color::Red);
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
