#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// ��� ����
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GAME_TIME = 60;

// ���� Ŭ����
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

    // ���õ� ��� �̹����� ������ ��������Ʈ
    sf::Texture selectedTexture;
    sf::Sprite selectedSprite;
    bool ingredientSelected; // ��ᰡ ���õǾ����� ����

    bool hasPepperoniOrPotato; // ���ڿ� ���۷δϳ� �������䰡 ������ Ȯ��

    // ���� ��ư
    sf::RectangleShape submitButton;
    sf::Text submitButtonText;

    // ���� ��ǥ ���� ����
    std::string targetPizza; // ��ǥ ���� (pepperoni �Ǵ� potato)
    sf::Text targetPizzaText;

public:
    PizzaGame() : ingredientSelected(false), hasPepperoniOrPotato(false) {
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

        // ���� ��ư ����
        submitButton.setSize(sf::Vector2f(200, 50));
        submitButton.setFillColor(sf::Color(234, 187, 101));
        submitButton.setPosition(50, 400);

        submitButtonText.setFont(font);
        submitButtonText.setString(L"����");
        submitButtonText.setCharacterSize(30);
        submitButtonText.setFillColor(sf::Color::Black);
        submitButtonText.setPosition(90, 410);

        // ���� �õ� ����
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // ��ǥ ���� �ؽ�Ʈ ����
        targetPizzaText.setFont(font);
        targetPizzaText.setCharacterSize(24);
        targetPizzaText.setFillColor(sf::Color::Black);
        targetPizzaText.setPosition(WINDOW_WIDTH / 2 - 100, 20);

        // ���� ��ǥ ���� ����
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
            targetPizzaText.setString(L"��ǥ: �������� ����");
        }
        else {
            targetPizza = "Pepperoni";
            targetPizzaText.setString(L"��ǥ: ���۷δ� ����");
        }
    }

    void updateGame() {
        if (gameEnded) return;

        elapsedTime = static_cast<int>(clock.getElapsedTime().asSeconds());
        int remainingTime = GAME_TIME - elapsedTime;

        if (remainingTime <= 0) {
            gameEnded = true;
            if (totalMoney >= 10000) {
                showEnd1(); // �¸� ȭ�� ǥ��
            }
            else {
                showEnd2(); // �й� ȭ�� ǥ��
            }
            return; // ������ �������Ƿ� ���� ���� ���� ����
        }

        // Ÿ�̸� �ؽ�Ʈ
        timerText.setString("Time: " + std::to_string(remainingTime));

        // �� �ؽ�Ʈ
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

        // ���õ� �̹����� ������ �׸���
        if (ingredientSelected) {
            window.draw(selectedSprite);
        }

        // ���� ��ư �׸���
        window.draw(submitButton);
        window.draw(submitButtonText);

        // �ؽ�Ʈ �׸���
        window.draw(moneyText);
        window.draw(timerText);

        // ��ǥ ���� �ؽ�Ʈ �׸���
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

                // ��� ��ư Ŭ�� ó��
                if (dough->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\dou_img.png");
                }
                else if (tomato->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\tomato_img.png");
                }
                else if (cheese->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\cheese_img.png");
                }
                else if (pepperoni->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\pepperoni_img.png");
                    hasPepperoniOrPotato = true;
                }
                else if (potato->sprite.getGlobalBounds().contains(mousePosF)) {
                    loadSelectedImage("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\potato_img.png");
                    hasPepperoniOrPotato = true;
                }

                // ���� ��ư Ŭ�� ó��
                if (submitButton.getGlobalBounds().contains(mousePosF)) {
                    submitPizza();
                }
            }
        }
    }

    // ���õ� �̹��� �ε� �� ǥ��
    void loadSelectedImage(const std::string& filePath) {
        if (selectedTexture.loadFromFile(filePath)) {
            selectedSprite.setTexture(selectedTexture);
            ingredientSelected = true;
        }
    }

    // ���� ��ư ó��
    void submitPizza() {
        if (ingredientSelected) {
            if ((targetPizza == "Potato" && hasPepperoniOrPotato) || (targetPizza == "Pepperoni" && hasPepperoniOrPotato)) {
                totalMoney += (targetPizza == "Potato" ? 1500 : 1200);
            }
            ingredientSelected = false; // ���� ���� �� ���õ� ��� �ʱ�ȭ
            hasPepperoniOrPotato = false;
            generateRandomPizza(); // �� ��ǥ ���� ����
        }
    }

    void showEnd1() {
        std::cout << "You Win!" << std::endl;
    }

    void showEnd2() {
        std::cout << "You Lose!" << std::endl;
    }
};

// ���� ���� �Լ�
void startGame() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pizza Making Game");

    PizzaGame game;

    while (window.isOpen()) {
        game.handleInput(window);
        game.updateGame();
        game.renderGame(window);
    }
}

// ���� ���� ȭ�� ǥ��
void showDescription(sf::RenderWindow& window) {
    sf::Text descriptionText;
    sf::Font font;
    if (!font.loadFromFile("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\BagelFatOne-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }
    descriptionText.setFont(font);
    descriptionText.setString(L"���� ����� ���ӿ� ���� ���� ȯ���մϴ�!\n1. �� ��Ḧ �����ϰ� ���ڸ� ����� �����ϼ���.\n2. �־��� �ð� ���� ��ǥ �ݾ��� �޼��ϼ���.");
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

    // ���� ������ ���� �����ֱ�
    showDescription(window);

    // �� �� ���� ����
    startGame();

    return 0;
}
