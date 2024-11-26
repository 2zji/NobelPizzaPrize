#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

// End ȭ�� �̵� �Լ�
void showEnd1(); // ���� ȭ��
void showEnd2(); // ���� ȭ��

class Pizza {
public:
    enum Ingredient { Dough, Cheese, Pepperoni, Potato, None };

    Pizza() : currentStep(Dough), isComplete(false), isCorrect(true) {}

    // ��� �߰� �޼���
    void addIngredient(Ingredient ingredient) {
        if (isComplete) return; // �̹� �ϼ��� ���
        if (ingredient == None) return; // ��ȿ���� ���� ���

        // �ùٸ� �������� Ȯ��
        if ((currentStep == Dough && ingredient == Cheese) ||
            (currentStep == Cheese && (ingredient == Pepperoni || ingredient == Potato))) {
            currentStep = ingredient;
            if (currentStep == Pepperoni || currentStep == Potato) {
                isComplete = true;
                type = (currentStep == Pepperoni) ? "Pepperoni" : "Potato";
            }
        }
        else {
            isCorrect = false; // �߸��� ����
        }
    }

    // ���� ���
    int getScore() const {
        if (!isComplete || !isCorrect) return -1000; // Ʋ���� ����
        return (type == "Pepperoni") ? 1500 : 2000; // �ùٸ� ������ ���� ��ȯ
    }

private:
    Ingredient currentStep; // ���� ��� �ܰ�
    bool isComplete;        // ���ڰ� �ϼ��Ǿ����� ����
    bool isCorrect;         // �ùٸ��� ����������� ����
    std::string type;       // ���� ����
};

class Game {
public:
    Game() : remainingTime(60), totalScore(0), pizzaCount(0) {
        clock.restart();
    }

    void run() {
        sf::RenderWindow gameWindow(sf::VideoMode(800, 600), L"���� ����� ����");

        // ��Ʈ �ε�
        sf::Font font;
        if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
            std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
            return;
        }

        // UI ����
        sf::Text timerText, scoreText, instructionText;
        setupText(timerText, font, 30, sf::Color::Black, { 50, 20 });
        setupText(scoreText, font, 30, sf::Color::Black, { 50, 60 });
        setupText(instructionText, font, 20, sf::Color::Black, { 50, 500 });
        instructionText.setString(L"Ŭ������ ��Ḧ �߰��ϼ���: 1) ����, 2) ġ��, 3) ���۷δ�, 4) ��������");

        while (gameWindow.isOpen()) {
            handleEvents(gameWindow);
            update();
            render(gameWindow, timerText, scoreText, instructionText);
        }
    }

private:
    sf::Clock clock;       // �ð� ����
    int remainingTime;     // ���� �ð�
    int totalScore;        // �� ����
    int pizzaCount;        // �ϼ��� ���� ��
    Pizza currentPizza;    // ���� ����

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
        std::wstring timerStr = L"���� �ð�: " + std::to_wstring(remainingTime) + L"��";
        std::wstring scoreStr = L"����: " + std::to_wstring(totalScore) + L"��, ����: " + std::to_wstring(pizzaCount) + L"��";

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
        currentPizza = Pizza(); // ���ο� ���� �غ�
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