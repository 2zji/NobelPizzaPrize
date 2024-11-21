#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <locale>
#include <codecvt>

// wstring을 UTF-8로 변환하는 함수
std::string wstringToString(const std::wstring& wstr) {
    // std::wstring_convert는 C++11에서 추가된 함수로, wstring을 string으로 변환할 수 있습니다.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr); // UTF-8로 변환
}

void startGame() {
    sf::RenderWindow gameWindow(sf::VideoMode(800, 600), L"노벨피자상");

    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "폰트를 불러올 수 없습니다!" << std::endl;
        return;
    }

    // 타이머 변수
    sf::Clock clock;
    sf::Time elapsedTime;
    int remainingTime = 60; // 60초

    // 타이머 텍스트
    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(350, 20);

    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }

        // 시간 계산
        elapsedTime = clock.getElapsedTime();
        int elapsedSeconds = static_cast<int>(elapsedTime.asSeconds());
        remainingTime = 60 - elapsedSeconds;

        // 시간이 끝나면 게임을 종료
        if (remainingTime <= 0) {
            remainingTime = 0;
            // 게임 종료 로직 (게임 오버 화면)
            gameWindow.close();
        }

        // 타이머 텍스트 업데이트
        std::wstring wstr = std::to_wstring(remainingTime);
        std::string str = wstringToString(wstr);  // wstring을 UTF-8로 변환

        // 텍스트 업데이트
        timerText.setString(str);

        gameWindow.clear(sf::Color(255, 241, 184)); // 배경색
        gameWindow.draw(timerText); // 타이머 텍스트
        gameWindow.display();
    }
}
