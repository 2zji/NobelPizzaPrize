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

// Ingredient Ŭ���� (���� ��Ḧ ǥ���ϸ�, �� ����� �ؽ�ó, ��������Ʈ, �̸�, ���� ����)
class Ingredient {
public:
    sf::Texture texture;    // ��� �̹��� ����
    sf::Sprite sprite;      // �ؽ�ó ��� ��������Ʈ
    std::string name;       // ��� �̸�
    int price;              // ��� ����

    // ��� Ŭ���� ������: �ؽ�ó �ε�, ��������Ʈ ����, �̸� �� ���� �ʱ�ȭ
    Ingredient(const std::string& textureFile, const std::string& ingredientName, int ingredientPrice) {
            // textureFile: �ؽ�ó ���� ���, ingredientName: ��� �̸�, ingredientPrice: ��� ����
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Error loading texture: " << textureFile << std::endl;
        }
        sprite.setTexture(texture);
        name = ingredientName;
        price = ingredientPrice;
    }

    // ����� ��ġ ����
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    // ��Ḧ ȭ�鿡 ������
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

// PizzaGame Ŭ���� (���� ����, ȭ�� ������, �Է� ó�� �� ���� �������� ���� ���)
class PizzaGame {
private:
    int totalMoney;     // �÷��̾ �� �� �ݾ�
    int elapsedTime;    // ��� �ð�
    bool gameEnded;     // ���� ����
    sf::Font font;      // �ؽ�Ʈ ǥ�� ��Ʈ
    sf::Text moneyText, timerText;  // �ΰ��� �ݾ�, �ð� �ؽ�Ʈ
    sf::Clock clock;    // �ð�

    // ���� ��� ��ü
    Ingredient* dough;
    Ingredient* tomato;
    Ingredient* cheese;
    Ingredient* pepperoni;
    Ingredient* potato;

    sf::Texture selectedTexture;    // ���� ��� �ؽ�ó
    sf::Sprite selectedSprite;      // ���� ��� ��������Ʈ
    bool ingredientSelected;        // ��� ���� ����
    bool hasPepperoniOrPotato;      // ���� ���ڿ� ���۷δ� or �������䰡 �ִ��� ����

    sf::RectangleShape submitButton;    // ���� ��ư
    sf::Text submitButtonText;          // ���� ��ư �ؽ�Ʈ

    // ���� ��ǥ ���� ����
    std::string targetPizza;    // ��ǥ ���� ����
    sf::Text targetPizzaText;   // ��ǥ ���� �ؽ�Ʈ

    // �߰��� ��� ����
    sf::Texture endTexture;   // ���� ȭ�� �ؽ�ó
    sf::Sprite endSprite;     // ���� ȭ�� ��������Ʈ

public:
    //���� ������: ���� �ʱ�ȭ �� ��Ʈ, ���, ��ư ���� 
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

    // ��ǥ ���ڸ� �������� ����
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

    // ���� ���� ������Ʈ: �ð� Ȯ��, ���� ���� Ȯ��, �ؽ�Ʈ ����
    void updateGame() {
        if (gameEnded) return;

        elapsedTime = static_cast<int>(clock.getElapsedTime().asSeconds());
        int remainingTime = GAME_TIME - elapsedTime;

        if (remainingTime <= 0) {
            gameEnded = true;
            if (totalMoney >= 100000) {
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

    // ���� ������: ���, ��ư, �ؽ�Ʈ, ��ǥ ���� ǥ��
    void renderGame(sf::RenderWindow& window) {
        window.clear(sf::Color(255, 241, 184)); // ��� �� ����

        if (gameEnded) {
            window.draw(endSprite);  // ������ ������ ���� ȭ��
        }
        else {
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
        }

        window.display();
    }

    // �Է� ó��: ���콺 Ŭ������ ��� ���� �� ���� ó��
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

    // ���õ� �̹����� �ε��Ͽ� ȭ�鿡 ǥ��
    void loadSelectedImage(const std::string& filePath) {
        if (selectedTexture.loadFromFile(filePath)) {
            selectedSprite.setTexture(selectedTexture);
            ingredientSelected = true;
        }
    }

    // ���� ���� ó��: ��ǥ ���ڿ� ��ġ�ϸ� �ݾ� �߰�, �� ��ǥ ����
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

    // �¸� ȭ�� ǥ��
    void showEnd1() {
        if (!endTexture.loadFromFile("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\end1.png")) {
            std::cerr << "Error!" << std::endl;
        }
        endSprite.setTexture(endTexture);

        // ȭ�� ũ�⿡ �°� ���� �̹����� ũ�� ����
        float scaleX = static_cast<float>(WINDOW_WIDTH) / endSprite.getGlobalBounds().width;
        float scaleY = static_cast<float>(WINDOW_HEIGHT) / endSprite.getGlobalBounds().height;
        endSprite.setScale(scaleX, scaleY);

        gameEnded = true;  // ���� ���� ���·� ����
    }

    // �й� ȭ�� ǥ��
    void showEnd2() {
        if (!endTexture.loadFromFile("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\end2.png")) {
            std::cerr << "Error!" << std::endl;
        }
        endSprite.setTexture(endTexture);

        // ȭ�� ũ�⿡ �°� ���� �̹����� ũ�� ����
        float scaleX = static_cast<float>(WINDOW_WIDTH) / endSprite.getGlobalBounds().width;
        float scaleY = static_cast<float>(WINDOW_HEIGHT) / endSprite.getGlobalBounds().height;
        endSprite.setScale(scaleX, scaleY);

        gameEnded = true;  // ���� ���� ���·� ����
    }

};

// ���� ���� �Լ�: �Է� ó��, ������Ʈ, ������ �ݺ�
void startGame() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NobelPizzaPrize");

    PizzaGame game;

    while (window.isOpen()) {
        game.handleInput(window);
        game.updateGame();
        game.renderGame(window);
    }
}

// ���� ���� ȭ�� ǥ�� �Լ�
void showDescription(sf::RenderWindow& window) {
    sf::Texture descriptionTexture;
    sf::Sprite descriptionSprite;

    // �̹��� �ε�
    if (!descriptionTexture.loadFromFile("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\game.png")) {
        std::cerr << "Error loading game.png!" << std::endl;
        return;
    }

    // ȭ�� ũ�⿡ �°� ����
    descriptionSprite.setTexture(descriptionTexture);
    sf::Vector2u textureSize = descriptionTexture.getSize();
    float scaleX = static_cast<float>(WINDOW_WIDTH) / textureSize.x;
    float scaleY = static_cast<float>(WINDOW_HEIGHT) / textureSize.y;
    descriptionSprite.setScale(scaleX, scaleY);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Ű �Է� �Ǵ� ���콺 Ŭ�� �� ���� ȭ�� ����
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                return;
            }
        }

        window.clear();
        window.draw(descriptionSprite); // �̹��� �׸���
        window.display();
    }
}

// ���� ȭ�� ǥ�� �Լ�
void showMainScreen(sf::RenderWindow& window) {
    sf::Texture mainTexture;
    sf::Sprite mainSprite;

    // main.png
    if (!mainTexture.loadFromFile("C:\\����\\�뺧���ڻ�\\NobelPizzaPrize\\assents\\main.png")) {
        std::cerr << "Error loading main.png!" << std::endl;
        return;
    }

    mainSprite.setTexture(mainTexture);

    // ȭ�� ũ�⿡ �°� �̹��� ũ�� ����
    float scaleX = static_cast<float>(WINDOW_WIDTH) / mainSprite.getGlobalBounds().width;
    float scaleY = static_cast<float>(WINDOW_HEIGHT) / mainSprite.getGlobalBounds().height;
    mainSprite.setScale(scaleX, scaleY);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Ű �Է� �Ǵ� ���콺 Ŭ�� �� ���� ȭ�� ����
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                return;
            }
        }

        window.clear();
        window.draw(mainSprite); // ���� �̹��� �׸���
        window.display();
    }
}

// main �Լ�: ���� ȭ�� -> ���� ȭ�� -> ���� ���� ������ ����
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pizza Making Game");

    // ���� ȭ�� ���� �����ֱ�
    showMainScreen(window);

    // ���� ���� ȭ�� ǥ��
    showDescription(window);

    // ���� ����
    startGame();

    return 0;
}