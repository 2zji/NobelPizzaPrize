#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

// ��� ����
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GAME_TIME = 60;

// �¸� �� �й� ȭ�� �Լ� ����
void showEnd1();
void showEnd2();

// ��� Ŭ����
class Ingredient {
public:
    sf::Texture texture;
    sf::Sprite sprite;
    std::string name;
    int price;

    Ingredient(const std::string& textureFile, const std::string& ingredientName, int ingredientPrice) {
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Error loading texture: " << textureFile << std::endl;
        }
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
        if (!font.loadFromFile("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\BagelFatOne-Regular.ttf")) {
            std::cout << "Error loading font" << std::endl;
        }

        moneyText.setFont(font);
        moneyText.setCharacterSize(24);
        moneyText.setFillColor(sf::Color::Black);
        moneyText.setPosition(650, 10);

        timerText.setFont(font);
        timerText.setCharacterSize(24);
        timerText.setFillColor(sf::Color::Black);
        timerText.setPosition(10, 10);

        // ��� �ʱ�ȭ
        dough = new Ingredient("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\dou.png", "Dough", 0);
        tomato = new Ingredient("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\tomato.png", "Tomato", 0);
        cheese = new Ingredient("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\cheese.png", "Cheese", 0);
        pepperoni = new Ingredient("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\pepperoni.png", "Pepperoni", 1200);
        potato = new Ingredient("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\potato.png", "Potato", 1500);

        // ��� ��ġ ����
        dough->setPosition(50, 100);
        tomato->setPosition(200, 100);
        cheese->setPosition(350, 100);
        pepperoni->setPosition(500, 100);
        potato->setPosition(650, 100);
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

        elapsedTime = static_cast<int>(clock.getElapsedTime().asSeconds());
        int remainingTime = GAME_TIME - elapsedTime;

        if (remainingTime <= 0) {
            gameEnded = true;
            if (totalMoney >= 10000) {
                showEnd1(); // �¸� ȭ��
            }
            else {
                showEnd2(); // �й� ȭ��
            }
        }

        // Ÿ�̸� �ؽ�Ʈ ������Ʈ
        timerText.setString("Time: " + std::to_string(remainingTime));

        // �� �ؽ�Ʈ ������Ʈ
        moneyText.setString("Money: " + std::to_string(totalMoney));
    }

    void renderGame(sf::RenderWindow& window) {
        window.clear(sf::Color(255, 241, 184)); // ��� �� ����

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
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                // ��� ��ư Ŭ�� ó��
                if (pepperoni->sprite.getGlobalBounds().contains(mousePosF)) {
                    totalMoney += pepperoni->price;
                }
                else if (potato->sprite.getGlobalBounds().contains(mousePosF)) {
                    totalMoney += potato->price;
                }
            }
        }
    }
};

// �¸� ȭ��
void showEnd1() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"���� ����");

    sf::Font font;
    if (!font.loadFromFile("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return;
    }

    sf::Text text(L"�����մϴ�! ��ǥ�� �޼��߽��ϴ�!", font, 30);
    text.setFillColor(sf::Color::Black);
    text.setPosition(150, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 241, 184)); // ��� �� ����
        window.draw(text);
        window.display();
    }
}

// �й� ȭ��
void showEnd2() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"���� ����");

    sf::Font font;
    if (!font.loadFromFile("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return;
    }

    sf::Text text(L"�ƽ����� ��ǥ�� �޼����� ���߽��ϴ�.", font, 30);
    text.setFillColor(sf::Color::Black);
    text.setPosition(100, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 241, 184)); // ��� �� ����
        window.draw(text);
        window.display();
    }
}

// ���� �Լ�
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pizza Game");

    PizzaGame game;

    while (window.isOpen()) {
        game.handleInput(window);
        game.updateGame();
        game.renderGame(window);
    }

    return 0;
}
