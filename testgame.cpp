#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

// 전역 변수
int money = 0;
int timeLeft = 60; // 60초 타이머
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

    // 타이머, 폰트 설정
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

    // 이미지 텍스처 및 스프라이트 설정
    sf::Texture douTexture, tomatoTexture, cheeseTexture, peproniTexture, potatoTexture;
    douTexture.loadFromFile("dou.png");
    tomatoTexture.loadFromFile("tomato.png");
    cheeseTexture.loadFromFile("cheese.png");
    peproniTexture.loadFromFile("peproni.png");
    potatoTexture.loadFromFile("potato.png");

    sf::Sprite douSprite(douTexture), tomatoSprite(tomatoTexture), cheeseSprite(cheeseTexture),
        peproniSprite(peproniTexture), potatoSprite(potatoTexture);

    std::vector<sf::Sprite> ingredientSprites;

    // 게임 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // 버튼 클릭 이벤트
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::D) { // 도우
                    selectedIngredients.push_back("dou");
                    ingredientSprites.push_back(douSprite);
                }
                else if (event.key.code == sf::Keyboard::T) { // 토마토소스
                    selectedIngredients.push_back("tomato");
                    ingredientSprites.push_back(tomatoSprite);
                }
                else if (event.key.code == sf::Keyboard::C) { // 치즈
                    selectedIngredients.push_back("cheese");
                    ingredientSprites.push_back(cheeseSprite);
                }
                else if (event.key.code == sf::Keyboard::P) { // 페퍼로니
                    selectedIngredients.push_back("peproni");
                    ingredientSprites.push_back(peproniSprite);
                }
                else if (event.key.code == sf::Keyboard::O) { // 포테이토
                    selectedIngredients.push_back("potato");
                    ingredientSprites.push_back(potatoSprite);
                }
                else if (event.key.code == sf::Keyboard::Enter) { // 제출 버튼
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

        // 타이머 갱신
        sf::Time elapsed = clock.getElapsedTime();
        timeLeft = 60 - static_cast<int>(elapsed.asSeconds());
        if (timeLeft <= 0) {
            if (money >= 10000) {
                // end1.cpp 실행
                system("end3.exe");
            }
            else {
                // end2.cpp 실행
                system("end4.exe");
            }
            resetGame();
            break;
        }

        // UI 업데이트
        timerText.setString("Time: " + std::to_string(timeLeft) + "s");
        moneyText.setString("Money: " + std::to_string(money) + " Won");
        orderText.setString("Order: " + currentOrder);

        // 화면 렌더링
        window.clear();
        window.draw(timerText);
        window.draw(moneyText);
        window.draw(orderText);

        // 재료 이미지 그리기
        float yOffset = 200.0f;
        for (auto& sprite : ingredientSprites) {
            sprite.setPosition(300, yOffset);
            window.draw(sprite);
            yOffset += 50.0f; // 재료 간격
        }

        window.draw(resultText);
        window.display();
    }

    return 0;
}
