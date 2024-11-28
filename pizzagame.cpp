#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

// --- ��� ---
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GAME_TIME = 60;

// --- ��� Ŭ���� ---
class Ingredient {
public:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string name;
    int price;

    Ingredient(const std::string& textureFile, const std::string& ingredientName, int ingredientPrice) {
        texture.loadFromFile(textureFile);
        sprite.setTexture(texture);
        name = ingredientName;
        price = ingredientPrice;
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

// --- ���� Ŭ���� ---
class PizzaGame {
private:
    int totalMoney;
    int elapsedTime;
    bool gameEnded;
    sf::Font font;
    sf::Text moneyText, timerText;
    sf::Clock clock;

    Ingredient* dough;
    Ingredient* tomato;
    Ingredient* cheese;
    Ingredient* pepperoni;
    Ingredient* potato;

public:
    PizzaGame() {
        totalMoney = 0;
        elapsedTime = 0;
        gameEnded = false;

        if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
            std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        }

        moneyText.setFont(font);
        moneyText.setCharacterSize(24);
        moneyText.setFillColor(sf::Color::White);
        moneyText.setPosition(650, 10);

        timerText.setFont(font);
        timerText.setCharacterSize(24);
        timerText.setFillColor(sf::Color::White);
        timerText.setPosition(10, 10);

        // ��� �ʱ�ȭ
        dough = new Ingredient("dou.png", "Dough", 0);
        tomato = new Ingredient("tomato.png", "Tomato", 0);
        cheese = new Ingredient("cheese.png", "Cheese", 0);
        pepperoni = new Ingredient("pepperoni.png", "Pepperoni", 1200);
        potato = new Ingredient("potato.png", "Potato", 1500);
    }

    ~PizzaGame() {
        delete dough;
        delete tomato;
        delete cheese;
        delete pepperoni;
        delete potato;
    }

    void updateGame() {
        if (gameEnded) return;

        elapsedTime = clock.getElapsedTime().asSeconds();
        int remainingTime = GAME_TIME - elapsedTime;

        if (remainingTime <= 0) {
            gameEnded = true;
            if (totalMoney >= 10000) {
                showEnd1();
            }
            else {
                showEnd2();
            }
        }

        timerText.setString("Time: " + std::to_string(remainingTime));
        moneyText.setString("Money: " + std::to_string(totalMoney));
    }

    void renderGame(sf::RenderWindow& window) {
        window.clear();
        dough->draw(window);
        tomato->draw(window);
        cheese->draw(window);
        pepperoni->draw(window);
        potato->draw(window);
        window.draw(moneyText);
        window.draw(timerText);
        window.display();
    }

    void handleInput(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (pepperoni->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    totalMoney += pepperoni->price;
                }
                else if (potato->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    totalMoney += potato->price;
                }
            }
        }
    }
};

// --- ���� ���� ȭ�� ---
void showEnd1() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"���� ����");
    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return;
    }

    sf::Text text(L"�����մϴ�! ��ǥ�� �޼��߽��ϴ�!", font, 30);
    text.setFillColor(sf::Color::Green);
    text.setPosition(150, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 241, 184));
        window.draw(text);
        window.display();
    }
}

// --- ���� ���� ȭ�� ---
void showEnd2() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"���� ����");
    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return;
    }

    sf::Text text(L"�ƽ����� ��ǥ�� �޼����� ���߽��ϴ�.", font, 30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(100, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 241, 184));
        window.draw(text);
        window.display();
    }
}

// --- ���� ���� ȭ�� ---
void showDescription() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"���� ����");
    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return;
    }

    sf::Text text(L"1. �ֹ��� ���� ���ڸ� ���弼��.\n"
        L"2. ���ڵ��� -> �ҽ� -> ġ�� -> ���� ���Դϴ�.\n"
        L"3. ��ǥ �ݾ�: 10,000��\n", font, 20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(50, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 241, 184));
        window.draw(text);
        window.display();
    }
}

// --- ���� ȭ�� ---
void startGame() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), L"���� ����� ����");
    PizzaGame game;

    while (window.isOpen()) {
        game.handleInput(window);
        game.updateGame();
        game.renderGame(window);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"�뺧���ڻ�");
    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return -1;
    }

    sf::Text title(L"�뺧���ڻ�", font, 50);
    title.setFillColor(sf::Color::Black);
    title.setPosition(240, 100);

    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color(234, 187, 101));
    startButton.setPosition(300, 200);

    sf::Text startText(L"���� ����", font, 30);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(320, 205);

    sf::RectangleShape descriptionButton(sf::Vector2f(200, 50));
    descriptionButton.setFillColor(sf::Color(234, 187, 101));
    descriptionButton.setPosition(300, 300);

    sf::Text descriptionText(L"���� ����", font, 30);
    descriptionText.setFillColor(sf::Color::Black);
    descriptionText.setPosition(320, 305);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                    startGame();
                }
                else if (descriptionButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                    showDescription();
                }
            }
        }

        window.clear(sf::Color(255, 241, 184));
        window.draw(title);
        window.draw(startButton);
        window.draw(startText);
        window.draw(descriptionButton);
        window.draw(descriptionText);
        window.display();
    }

    return 0;
}
