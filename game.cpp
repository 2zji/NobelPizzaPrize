#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

// End 화면 이동 함수
void showEnd1(); // 성공 화면
void showEnd2(); // 실패 화면

class Pizza {
public:
    enum Ingredient { Dough, Cheese, Pepperoni, Potato, None };

    Pizza() : currentStep(Dough), isComplete(false), isCorrect(true) {}

    // 재료 추가 메서드
    void addIngredient(Ingredient ingredient) {
        if (isComplete) return; // 이미 완성된 경우
        if (ingredient == None) return; // 유효하지 않은 재료

        // 올바른 순서인지 확인
        if ((currentStep == Dough && ingredient == Cheese) ||
            (currentStep == Cheese && (ingredient == Pepperoni || ingredient == Potato))) {
            currentStep = ingredient;
            if (currentStep == Pepperoni || currentStep == Potato) {
                isComplete = true;
                type = (currentStep == Pepperoni) ? "Pepperoni" : "Potato";
            }
        }
        else {
            isCorrect = false; // 잘못된 순서
        }
    }

    // 점수 계산
    int getScore() const {
        if (!isComplete || !isCorrect) return -1000; // 틀리면 감점
        return (type == "Pepperoni") ? 1500 : 2000; // 올바른 피자의 가격 반환
    }

private:
    Ingredient currentStep; // 현재 재료 단계
    bool isComplete;        // 피자가 완성되었는지 여부
    bool isCorrect;         // 올바르게 만들어졌는지 여부
    std::string type;       // 피자 종류
};

class Game {
public:
    Game() : remainingTime(60), totalScore(0), pizzaCount(0) {
        clock.restart();
    }

    void run() {
        sf::RenderWindow gameWindow(sf::VideoMode(800, 600), L"피자 만들기 게임");

        // 폰트 로드
        sf::Font font;
        if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
            std::cerr << "폰트를 불러올 수 없습니다!" << std::endl;
            return;
        }

        // UI 설정
        sf::Text timerText, scoreText, instructionText;
        setupText(timerText, font, 30, sf::Color::Black, { 50, 20 });
        setupText(scoreText, font, 30, sf::Color::Black, { 50, 60 });
        setupText(instructionText, font, 20, sf::Color::Black, { 50, 500 });
        instructionText.setString(L"클릭으로 재료를 추가하세요: 1) 도우, 2) 치즈, 3) 페퍼로니, 4) 포테이토");

        while (gameWindow.isOpen()) {
            handleEvents(gameWindow);
            update();
            render(gameWindow, timerText, scoreText, instructionText);
        }
    }

private:
    sf::Clock clock;       // 시간 관리
    int remainingTime;     // 남은 시간
    int totalScore;        // 총 점수
    int pizzaCount;        // 완성된 피자 수
    Pizza currentPizza;    // 현재 피자

    void handleEvents(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    currentPizza.addIngredient(Pizza::Dough);
                }
                else if (event.key.code == sf::Keyboard::Num2) {
                    currentPizza.addIngredient(Pizza::Cheese);
                }
                else if (event.key.code == sf::Keyboard::Num3) {
                    currentPizza.addIngredient(Pizza::Pepperoni);
                    finalizePizza();
                }
                else if (event.key.code == sf::Keyboard::Num4) {
                    currentPizza.addIngredient(Pizza::Potato);
                    finalizePizza();
                }
            }
        }
    }

    void update() {
        int elapsedSeconds = static_cast<int>(clock.getElapsedTime().asSeconds());
        remainingTime = 60 - elapsedSeconds;

        if (remainingTime <= 0) {
            endGame();
        }
    }

    void render(sf::RenderWindow& window, sf::Text& timerText, sf::Text& scoreText, sf::Text& instructionText) {
        std::wstring timerStr = L"남은 시간: " + std::to_wstring(remainingTime) + L"초";
        std::wstring scoreStr = L"점수: " + std::to_wstring(totalScore) + L"원, 피자: " + std::to_wstring(pizzaCount) + L"개";

        timerText.setString(timerStr);
        scoreText.setString(scoreStr);


        window.clear(sf::Color::White);
        window.draw(timerText);
        window.draw(scoreText);
        window.draw(instructionText);
        window.display();
    }

    void setupText(sf::Text& text, sf::Font& font, int size, sf::Color color, sf::Vector2f position) {
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(color);
        text.setPosition(position);
    }

    void finalizePizza() {
        totalScore += currentPizza.getScore();
        if (currentPizza.getScore() > 0) {
            pizzaCount++;
        }
        currentPizza = Pizza(); // 새로운 피자 준비
    }

    void endGame() {
        if (totalScore >= 10000) {
            showEnd1();
        }
        else {
            showEnd2();
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}