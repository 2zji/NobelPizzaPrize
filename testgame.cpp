#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

// ���� ����
int money = 0;
int timeLeft = 60; // 60�� Ÿ�̸�
std::vector<std::string> selectedIngredients;

void resetGame() {
    money = 0;
    selectedIngredients.clear();
}

bool checkPizza(std::string type) {
    if (type == "pepperoni" && selectedIngredients == std::vector<std::string>{"dou", "tomato", "cheese", "peproni"}) {
        return true;
    }
    if (type == "potato" && selectedIngredients == std::vector<std::string>{"dou", "tomato", "cheese", "potato"}) {
        return true;
    }
    return false;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pizza Making Game");
    sf::Clock clock;
    std::srand(std::time(nullptr));

    // Ÿ�̸�, ��Ʈ ����
    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "Font not found!" << std::endl;
        return -1;
    }

    sf::Text timerText, moneyText, orderText, resultText;
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10, 10);

    moneyText.setFont(font);
    moneyText.setCharacterSize(24);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(10, 40);

    orderText.setFont(font);
    orderText.setCharacterSize(24);
    orderText.setFillColor(sf::Color::White);
    orderText.setPosition(10, 70);

    resultText.setFont(font);
    resultText.setCharacterSize(24);
    resultText.setFillColor(sf::Color::Red);
    resultText.setPosition(300, 500);

    std::string currentOrder = (std::rand() % 2 == 0) ? "pepperoni" : "potato";

    // �̹��� �ؽ�ó �� ��������Ʈ ����
    sf::Texture douTexture, tomatoTexture, cheeseTexture, peproniTexture, potatoTexture;
    douTexture.loadFromFile("dou.png");
    tomatoTexture.loadFromFile("tomato.png");
    cheeseTexture.loadFromFile("cheese.png");
    peproniTexture.loadFromFile("peproni.png");
    potatoTexture.loadFromFile("potato.png");

    sf::Sprite douSprite(douTexture), tomatoSprite(tomatoTexture), cheeseSprite(cheeseTexture),
        peproniSprite(peproniTexture), potatoSprite(potatoTexture);

    std::vector<sf::Sprite> ingredientSprites;

    // ���� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // ��ư Ŭ�� �̺�Ʈ
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::D) { // ����
                    selectedIngredients.push_back("dou");
                    ingredientSprites.push_back(douSprite);
                }
                else if (event.key.code == sf::Keyboard::T) { // �丶��ҽ�
                    selectedIngredients.push_back("tomato");
                    ingredientSprites.push_back(tomatoSprite);
                }
                else if (event.key.code == sf::Keyboard::C) { // ġ��
                    selectedIngredients.push_back("cheese");
                    ingredientSprites.push_back(cheeseSprite);
                }
                else if (event.key.code == sf::Keyboard::P) { // ���۷δ�
                    selectedIngredients.push_back("peproni");
                    ingredientSprites.push_back(peproniSprite);
                }
                else if (event.key.code == sf::Keyboard::O) { // ��������
                    selectedIngredients.push_back("potato");
                    ingredientSprites.push_back(potatoSprite);
                }
                else if (event.key.code == sf::Keyboard::Enter) { // ���� ��ư
                    if (checkPizza(currentOrder)) {
                        money += (currentOrder == "pepperoni") ? 1200 : 1500;
                        resultText.setString("Correct! + " + std::to_string((currentOrder == "pepperoni") ? 1200 : 1500) + " Won");
                    }
                    else {
                        money -= 1000;
                        resultText.setString("Wrong! -1000 Won");
                    }
                    selectedIngredients.clear();
                    ingredientSprites.clear();
                    currentOrder = (std::rand() % 2 == 0) ? "pepperoni" : "potato";
                }
            }
        }

        // Ÿ�̸� ����
        sf::Time elapsed = clock.getElapsedTime();
        timeLeft = 60 - static_cast<int>(elapsed.asSeconds());
        if (timeLeft <= 0) {
            if (money >= 10000) {
                // end1.cpp ����
                system("end3.exe");
            }
            else {
                // end2.cpp ����
                system("end4.exe");
            }
            resetGame();
            break;
        }

        // UI ������Ʈ
        timerText.setString("Time: " + std::to_string(timeLeft) + "s");
        moneyText.setString("Money: " + std::to_string(money) + " Won");
        orderText.setString("Order: " + currentOrder);

        // ȭ�� ������
        window.clear();
        window.draw(timerText);
        window.draw(moneyText);
        window.draw(orderText);

        // ��� �̹��� �׸���
        float yOffset = 200.0f;
        for (auto& sprite : ingredientSprites) {
            sprite.setPosition(300, yOffset);
            window.draw(sprite);
            yOffset += 50.0f; // ��� ����
        }

        window.draw(resultText);
        window.display();
    }

    return 0;
}
