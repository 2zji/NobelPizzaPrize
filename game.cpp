#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GAME_TIME = 60;

// ��� Ŭ����
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

// ���� Ŭ����
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

        // ��Ʈ �ε�
        if (!font.loadFromFile("Arial.ttf")) {
            std::cout << "Error loading font" << std::endl;
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
                std::cout << "You win!" << std::endl; // Show end1.cpp screen
            }
            else {
                std::cout << "You lose!" << std::endl; // Show end2.cpp screen
            }
        }

        // Ÿ�̸� �ؽ�Ʈ ������Ʈ
        timerText.setString("Time: " + std::to_string(remainingTime));

        // �� �ؽ�Ʈ ������Ʈ
        moneyText.setString("Money: " + std::to_string(totalMoney));
    }

    void renderGame(sf::RenderWindow& window) {
        window.clear();

        // ��� �׸���
        dough->draw(window);
        tomato->draw(window);
        cheese->draw(window);
        pepperoni->draw(window);
        potato->draw(window);

        // �ؽ�Ʈ �׸���
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

                // ��� ��ư Ŭ�� ó��
                if (pepperoni->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    totalMoney += pepperoni->price; // ���۷δ� ���� �߰�
                }
                else if (potato->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    totalMoney += potato->price; // �������� ���� �߰�
                }
            }
        }
    }

    int getTotalMoney() const {
        return totalMoney;
    }
};

int main() {
    // SFML ������ ����
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pizza Game");

    // ���� ��ü ����
    PizzaGame game;

    // ���� ����
    while (window.isOpen()) {
        game.handleInput(window);
        game.updateGame();
        game.renderGame(window);
    }

    return 0;
}
