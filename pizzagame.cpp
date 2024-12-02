#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// 상수 정의
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GAME_TIME = 60;

// 게임 클래스
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

    // 선택된 재료 이미지를 저장할 스프라이트
    sf::Texture selectedTexture;
    sf::Sprite selectedSprite;
    bool ingredientSelected; // 재료가 선택되었는지 여부

    bool hasPepperoniOrPotato; // 피자에 페퍼로니나 포테이토가 들어갔는지 확인

    // 제출 버튼
    sf::RectangleShape submitButton;
    sf::Text submitButtonText;

    // 랜덤 목표 피자 관련
    std::string targetPizza; // 목표 피자 (pepperoni 또는 potato)
    sf::Text targetPizzaText;

public:
    PizzaGame() : ingredientSelected(false), hasPepperoniOrPotato(false) {
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

        // 제출 버튼 설정
        submitButton.setSize(sf::Vector2f(200, 50));
        submitButton.setFillColor(sf::Color(234, 187, 101));
        submitButton.setPosition(50, 400);

        submitButtonText.setFont(font);
        submitButtonText.setString(L"제출");
        submitButtonText.setCharacterSize(30);
        submitButtonText.setFillColor(sf::Color::Black);
        submitButtonText.setPosition(90, 410);

        // 랜덤 시드 설정
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // 목표 피자 텍스트 설정
        targetPizzaText.setFont(font);
        targetPizzaText.setCharacterSize(24);
        targetPizzaText.setFillColor(sf::Color::Black);
        targetPizzaText.setPosition(WINDOW_WIDTH / 2 - 100, 20);

        // 랜덤 목표 피자 생성
        generateRandomPizza();
    }

    ~PizzaGame() {
        delete dough;
        delete tomato;
        delete cheese;
        delete pepperoni;
        delete potato;
    }

    void generateRandomPizza() {
        if (std::rand() % 2 == 0) {
            targetPizza = "Potato";
            targetPizzaText.setString(L"목표: 포테이토 피자");
        }
        else {
            targetPizza = "Pepperoni";
            targetPizzaText.setString(L"목표: 페퍼로니 피자");
        }
    }

    void updateGame() {
        if (gameEnded) return;

        elapsedTime = static_cast<int>(clock.getElapsedTime().asSeconds());
        int remainingTime = GAME_TIME - elapsedTime;

        if (remainingTime <= 0) {
            gameEnded = true;
            if (totalMoney >= 10000) {
                showEnd1(); // 승리 화면 표시
            }
            else {
                showEnd2(); // 패배 화면 표시
            }
            return; // 게임이 끝났으므로 이후 로직 실행 중지
        }

        // 타이머 텍스트
        timerText.setString("Time: " + std::to_string(remainingTime));

        // 돈 텍스트
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

        // 선택된 이미지가 있으면 그리기
        if (ingredientSelected) {
            window.draw(selectedSprite);
        }

        // 제출 버튼 그리기
        window.draw(submitButton);
        window.draw(submitButtonText);

        // 텍스트 그리기
        window.draw(moneyText);
        window.draw(timerText);

        // 목표 피자 텍스트 그리기
        window.draw(targetPizzaText);

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
                if (dough->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\dou_img.png");
                }
                else if (tomato->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\tomato_img.png");
                }
                else if (cheese->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\cheese_img.png");
                }
                else if (pepperoni->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\pepperoni_img.png");
                    hasPepperoniOrPotato = true;
                }
                else if (potato->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\potato_img.png");
                    hasPepperoniOrPotato = true;
                }

                // 제출 버튼 클릭 처리
                if (submitButton.getGlobalBounds().contains(mousePosF)) {
                    submitPizza();
                }
            }
        }
    }

    // 선택된 이미지 로드 및 표시
    void loadSelectedImage(const std::string& filePath) {
        if (selectedTexture.loadFromFile(filePath)) {
            selectedSprite.setTexture(selectedTexture);
            ingredientSelected = true;
        }
    }

    // 제출 버튼 처리
    void submitPizza() {
        if (ingredientSelected) {
            if ((targetPizza == "Potato" && hasPepperoniOrPotato) || (targetPizza == "Pepperoni" && hasPepperoniOrPotato)) {
                totalMoney += (targetPizza == "Potato" ? 1500 : 1200);
            }
            ingredientSelected = false; // 피자 제출 후 선택된 재료 초기화
            hasPepperoniOrPotato = false;
            generateRandomPizza(); // 새 목표 피자 설정
        }
    }

    void showEnd1() {
        std::cout << "You Win!" << std::endl;
    }

    void showEnd2() {
        std::cout << "You Lose!" << std::endl;
    }
};

// 게임 실행 함수
void startGame() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pizza Making Game");

    PizzaGame game;

    while (window.isOpen()) {
        game.handleInput(window);
        game.updateGame();
        game.renderGame(window);
    }
}

// 게임 설명 화면 표시
void showDescription(sf::RenderWindow& window) {
    sf::Text descriptionText;
    sf::Font font;
    if (!font.loadFromFile("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\BagelFatOne-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
    descriptionText.setFont(font);
    descriptionText.setString(L"피자 만들기 게임에 오신 것을 환영합니다!\n1. 각 재료를 선택하고 피자를 만들어 제출하세요.\n2. 주어진 시간 내에 목표 금액을 달성하세요.");
    descriptionText.setCharacterSize(24);
    descriptionText.setFillColor(sf::Color::Black);
    descriptionText.setPosition(100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(255, 241, 184));
        window.draw(descriptionText);
        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pizza Making Game");

    // 게임 설명을 먼저 보여주기
    showDescription(window);

    // 그 후 게임 시작
    startGame();

    return 0;
}
