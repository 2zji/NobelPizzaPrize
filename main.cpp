#include <SFML/Graphics.hpp>
#include <iostream>
#include "font_data.cpp"  // font_data.cpp 파일
#include "description.h"

// 폰트 데이터 써서 sf::Font 객체로 변환하는 함수 (메모리에 직접 불러옴)
sf::Font loadFontFromData() {
    sf::Font font;
    if (font.loadFromMemory(font_data, font_data_len)) {
        return font;
    }
    else {
        // 폰트 로드 실패 시 기본 폰트를 반환 or 오류
        sf::Font defaultFont;
        defaultFont.loadFromFile("BagelFatOne-Regular.ttf");    //BagelFatOne-Regular(외부 다운)사용
        return defaultFont;
    }
}

// 버튼을 클릭했는지 확인하는 함수 (사용자가 클릭한 위치가 버튼 영역 안에 있는지 확인)
bool isButtonClicked(sf::RectangleShape& button, sf::Vector2i mousePos) {
    return button.getGlobalBounds().contains(sf::Vector2f(mousePos));
}

int main() {
    // 창 만들기
    sf::RenderWindow window(sf::VideoMode(800, 600), L"노벨피자상");

    // 폰트 로드
    sf::Font font = loadFontFromData();

    // 텍스트 설정
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString(L"노벨피자상");  //""앞에 L 붙이면 한글 출력 잘 됨ㅇㅇ
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(300, 100);

    // 시작 버튼 설정
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color(234, 187, 101));
    startButton.setPosition(300, 200);

    //시작 버튼 텍스트 설정
    sf::Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString(L"게임 시작");
    startButtonText.setCharacterSize(30);
    startButtonText.setFillColor(sf::Color::Black);
    startButtonText.setPosition(330, 210);

    // 게임 설명 버튼 설정
    sf::RectangleShape instructionsButton(sf::Vector2f(200, 50));
    instructionsButton.setFillColor(sf::Color(234, 187, 101));
    instructionsButton.setPosition(300, 300);

    //게임 설명 버튼 텍스트 설정
    sf::Text instructionsButtonText;
    instructionsButtonText.setFont(font);
    instructionsButtonText.setString(L"게임 설명");
    instructionsButtonText.setCharacterSize(30);
    instructionsButtonText.setFillColor(sf::Color::Black);
    instructionsButtonText.setPosition(320, 310);

    // 게임 루프 (창이 열려 있는 동안 게임 루프)
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // 마우스 클릭 이벤트 처리 (클릭된 위치를 확인)
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // 시작 버튼 클릭
                if (isButtonClicked(startButton, mousePos)) {
                    // 게임 시작 코드로 이동
                    titleText.setString(L"게임 시작");
                }

                // 게임 설명 버튼 클릭
                if (isButtonClicked(instructionsButton, mousePos)) {
                    // 게임 설명 코드로 이동
                    titleText.setString(L"게임 설명: 피자로 노벨상 받기!");
                }
            }
        }

        // 창 그리기
        window.clear(sf::Color(255, 241, 184));  // 배경 색상 설정
        window.draw(titleText);          // 제목 텍스트
        window.draw(startButton);        // 시작 버튼
        window.draw(startButtonText);    // 시작 버튼 텍스트
        window.draw(instructionsButton); // 게임 설명 버튼
        window.draw(instructionsButtonText);  // 게임 설명 버튼 텍스트
        window.display();
    }

    return 0;
}
