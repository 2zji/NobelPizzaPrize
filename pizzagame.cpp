#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

// 상수 정의
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GAME_TIME = 60;

// 승리 및 패배 화면 함수 선언
void showEnd1();
void showEnd2();

// 재료 클래스
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

// 게임 클래스
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

        // 폰트 로드
        if (!font.loadFromFile("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\BagelFatOne-Regular.ttf")) {
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

        // 재료 초기화
        dough = new Ingredient("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\dou.png", "Dough", 0);
        tomato = new Ingredient("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\tomato.png", "Tomato", 0);
        cheese = new Ingredient("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\cheese.png", "Cheese", 0);
        pepperoni = new Ingredient("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\pepperoni.png", "Pepperoni", 1200);
        potato = new Ingredient("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\potato.png", "Potato", 1500);

        // 재료 위치 설정
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
                showEnd1(); // 승리 화면
            }
            else {
                showEnd2(); // 패배 화면
            }
        }

        // 타이머 텍스트 업데이트
        timerText.setString("Time: " + std::to_string(remainingTime));

        // 돈 텍스트 업데이트
        moneyText.setString("Money: " + std::to_string(totalMoney));
    }

    void renderGame(sf::RenderWindow& window) {
        window.clear(sf::Color(255, 241, 184)); // 배경 색 변경

        // 재료 그리기
        dough->draw(window);
        tomato->draw(window);
        cheese->draw(window);
        pepperoni->draw(window);
        potato->draw(window);

        // 텍스트 그리기
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

                // 재료 버튼 클릭 처리
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

// 승리 화면
void showEnd1() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"게임 성공");

    sf::Font font;
    if (!font.loadFromFile("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\BagelFatOne-Regular.ttf")) {
        std::cerr << "폰트를 불러올 수 없습니다!" << std::endl;
        return;
    }

    sf::Text text(L"축하합니다! 목표를 달성했습니다!", font, 30);
    text.setFillColor(sf::Color::Black);
    text.setPosition(150, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 241, 184)); // 배경 색 변경
        window.draw(text);
        window.display();
    }
}

// 패배 화면
void showEnd2() {
    sf::RenderWindow window(sf::VideoMode(800, 600), L"게임 실패");

    sf::Font font;
    if (!font.loadFromFile("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\BagelFatOne-Regular.ttf")) {
        std::cerr << "폰트를 불러올 수 없습니다!" << std::endl;
        return;
    }

    sf::Text text(L"아쉽지만 목표를 달성하지 못했습니다.", font, 30);
    text.setFillColor(sf::Color::Black);
    text.setPosition(100, 250);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 241, 184)); // 배경 색 변경
        window.draw(text);
        window.display();
    }
}

// 메인 함수
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
