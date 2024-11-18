#include <SFML/Graphics.hpp>
#include "description.h"
#include "common.h" // isButtonClicked 함수 포함

// 메인 함수
int main() {
    // 창 설정
    sf::RenderWindow window(sf::VideoMode(800, 600), L"노벨피자상");

    // 폰트 로드
    sf::Font font = loadFontFromData();

    // 제목 텍스트 설정
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString(L"노벨피자상");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(300, 100);

    // 시작 버튼 설정
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color(234, 187, 101));
    startButton.setPosition(300, 200);

    sf::Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString(L"게임 시작");
    startButtonText.setCharacterSize(30);
    startButtonText.setFillColor(sf::Color::Black);
    centerText(startButtonText, startButton);

    // 게임 설명 버튼 설정
    sf::RectangleShape instructionsButton(sf::Vector2f(200, 50));
    instructionsButton.setFillColor(sf::Color(234, 187, 101));
    instructionsButton.setPosition(300, 300);

    sf::Text instructionsButtonText;
    instructionsButtonText.setFont(font);
    instructionsButtonText.setString(L"게임 설명");
    instructionsButtonText.setCharacterSize(30);
    instructionsButtonText.setFillColor(sf::Color::Black);
    centerText(instructionsButtonText, instructionsButton);

    // 뒤로 가기 버튼 설정 (설명 화면용)
    Button backButton(
        sf::Vector2f(200, 50), sf::Vector2f(300, 500), sf::Color(200, 100, 100),
        L"뒤로 가기", font, 30, sf::Color::White
    );

    bool showDescription = false;

    // 게임 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (!showDescription) {
                    // 시작 버튼 클릭
                    if (isButtonClicked(startButton, mousePos)) {
                        titleText.setString(L"게임이 시작됩니다!");
                    }

                    // 게임 설명 버튼 클릭
                    if (isButtonClicked(instructionsButton, mousePos)) {
                        showDescription = true; // 설명 화면으로 전환
                    }
                }
                else {
                    // 뒤로 가기 버튼 클릭
                    if (backButton.isClicked(mousePos)) {
                        showDescription = false; // 메인 화면으로 돌아가기
                    }
                }
            }
        }

        // 화면 그리기
        window.clear(sf::Color(255, 241, 184));

        if (!showDescription) {
            // 메인 화면
            window.draw(titleText);
            window.draw(startButton);
            window.draw(startButtonText);
            window.draw(instructionsButton);
            window.draw(instructionsButtonText);
        }
        else {
            // 설명 화면
            drawDescriptionScreen(window, font, backButton);
        }

        window.display();
    }

    return 0;
}
