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

// Ingredient 클래스 (피자 재료를 표현하며, 각 재료의 텍스처, 스프라이트, 이름, 가격 관리)
class Ingredient {
public:
    sf::Texture texture;    // 재료 이미지 저장
    sf::Sprite sprite;      // 텍스처 기반 스프라이트
    std::string name;       // 재료 이름
    int price;              // 재료 가격

    // 재료 클래스 생성자: 텍스처 로드, 스프라이트 설정, 이름 및 가격 초기화
    Ingredient(const std::string& textureFile, const std::string& ingredientName, int ingredientPrice) {
            // textureFile: 텍스처 파일 경로, ingredientName: 재료 이름, ingredientPrice: 재료 가격
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Error loading texture: " << textureFile << std::endl;
        }
        sprite.setTexture(texture);
        name = ingredientName;
        price = ingredientPrice;
    }

    // 재료의 위치 설정
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    // 재료를 화면에 렌더링
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

// PizzaGame 클래스 (게임 로직, 화면 렌더링, 입력 처리 등 게임 전반적인 관리 담당)
class PizzaGame {
private:
    int totalMoney;     // 플레이어가 번 총 금액
    int elapsedTime;    // 경과 시간
    bool gameEnded;     // 게임 종료
    sf::Font font;      // 텍스트 표시 폰트
    sf::Text moneyText, timerText;  // 인게임 금액, 시간 텍스트
    sf::Clock clock;    // 시계

    // 피자 재료 객체
    Ingredient* dough;
    Ingredient* tomato;
    Ingredient* cheese;
    Ingredient* pepperoni;
    Ingredient* potato;

    sf::Texture selectedTexture;    // 선택 재료 텍스처
    sf::Sprite selectedSprite;      // 선택 재료 스프라이트
    bool ingredientSelected;        // 재료 선택 여부
    bool hasPepperoniOrPotato;      // 현재 피자에 페퍼로니 or 포테이토가 있는지 여부

    sf::RectangleShape submitButton;    // 제출 버튼
    sf::Text submitButtonText;          // 제출 버튼 텍스트

    // 랜덤 목표 피자 관련
    std::string targetPizza;    // 목표 피자 종류
    sf::Text targetPizzaText;   // 목표 피자 텍스트

    // 추가된 멤버 변수
    sf::Texture endTexture;   // 종료 화면 텍스처
    sf::Sprite endSprite;     // 종료 화면 스프라이트

public:
    //게임 생성자: 변수 초기화 및 폰트, 재료, 버튼 설정 
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

    // 목표 피자를 랜덤으로 생성
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

    // 게임 상태 업데이트: 시간 확인, 종료 상태 확인, 텍스트 갱신
    void updateGame() {
        if (gameEnded) return;

        elapsedTime = static_cast<int>(clock.getElapsedTime().asSeconds());
        int remainingTime = GAME_TIME - elapsedTime;

        if (remainingTime <= 0) {
            gameEnded = true;
            if (totalMoney >= 100000) {
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

    // 게임 렌더링: 재료, 버튼, 텍스트, 목표 피자 표시
    void renderGame(sf::RenderWindow& window) {
        window.clear(sf::Color(255, 241, 184)); // 배경 색 변경

        if (gameEnded) {
            window.draw(endSprite);  // 게임이 끝나면 엔딩 화면
        }
        else {
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
        }

        window.display();
    }

    // 입력 처리: 마우스 클릭으로 재료 선택 및 제출 처리
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

    // 선택된 이미지를 로드하여 화면에 표시
    void loadSelectedImage(const std::string& filePath) {
        if (selectedTexture.loadFromFile(filePath)) {
            selectedSprite.setTexture(selectedTexture);
            ingredientSelected = true;
        }
    }

    // 피자 제출 처리: 목표 피자와 일치하면 금액 추가, 새 목표 설정
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

    // 승리 화면 표시
    void showEnd1() {
        if (!endTexture.loadFromFile("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\end1.png")) {
            std::cerr << "Error!" << std::endl;
        }
        endSprite.setTexture(endTexture);

        // 화면 크기에 맞게 엔딩 이미지를 크기 조정
        float scaleX = static_cast<float>(WINDOW_WIDTH) / endSprite.getGlobalBounds().width;
        float scaleY = static_cast<float>(WINDOW_HEIGHT) / endSprite.getGlobalBounds().height;
        endSprite.setScale(scaleX, scaleY);

        gameEnded = true;  // 게임 종료 상태로 변경
    }

    // 패배 화면 표시
    void showEnd2() {
        if (!endTexture.loadFromFile("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\end2.png")) {
            std::cerr << "Error!" << std::endl;
        }
        endSprite.setTexture(endTexture);

        // 화면 크기에 맞게 엔딩 이미지를 크기 조정
        float scaleX = static_cast<float>(WINDOW_WIDTH) / endSprite.getGlobalBounds().width;
        float scaleY = static_cast<float>(WINDOW_HEIGHT) / endSprite.getGlobalBounds().height;
        endSprite.setScale(scaleX, scaleY);

        gameEnded = true;  // 게임 종료 상태로 변경
    }

};

// 게임 실행 함수: 입력 처리, 업데이트, 렌더링 반복
void startGame() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "NobelPizzaPrize");

    PizzaGame game;

    while (window.isOpen()) {
        game.handleInput(window);
        game.updateGame();
        game.renderGame(window);
    }
}

// 게임 설명 화면 표시 함수
void showDescription(sf::RenderWindow& window) {
    sf::Texture descriptionTexture;
    sf::Sprite descriptionSprite;

    // 이미지 로드
    if (!descriptionTexture.loadFromFile("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\game.png")) {
        std::cerr << "Error loading game.png!" << std::endl;
        return;
    }

    // 화면 크기에 맞게 조정
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

            // 키 입력 또는 마우스 클릭 시 설명 화면 종료
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                return;
            }
        }

        window.clear();
        window.draw(descriptionSprite); // 이미지 그리기
        window.display();
    }
}

// 메인 화면 표시 함수
void showMainScreen(sf::RenderWindow& window) {
    sf::Texture mainTexture;
    sf::Sprite mainSprite;

    // main.png
    if (!mainTexture.loadFromFile("C:\\연습\\노벨피자상\\NobelPizzaPrize\\assents\\main.png")) {
        std::cerr << "Error loading main.png!" << std::endl;
        return;
    }

    mainSprite.setTexture(mainTexture);

    // 화면 크기에 맞게 이미지 크기 조정
    float scaleX = static_cast<float>(WINDOW_WIDTH) / mainSprite.getGlobalBounds().width;
    float scaleY = static_cast<float>(WINDOW_HEIGHT) / mainSprite.getGlobalBounds().height;
    mainSprite.setScale(scaleX, scaleY);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // 키 입력 또는 마우스 클릭 시 메인 화면 종료
            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) {
                return;
            }
        }

        window.clear();
        window.draw(mainSprite); // 메인 이미지 그리기
        window.display();
    }
}

// main 함수: 메인 화면 -> 설명 화면 -> 게임 실행 순으로 진행
int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pizza Making Game");

    // 메인 화면 먼저 보여주기
    showMainScreen(window);

    // 게임 설명 화면 표시
    showDescription(window);

    // 게임 시작
    startGame();

    return 0;
}