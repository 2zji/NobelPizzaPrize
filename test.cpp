#include <SFML/Graphics.hpp>

int main() {
    // SFML 창 생성
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML 한글 지원");

    // 한글 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        return -1;  // 폰트 로드 실패 시 종료
    }

    // 텍스트 객체 생성
    sf::Text text(L"안녕하세요, SFML!", font, 30);
    text.setFillColor(sf::Color::White);  // 텍스트 색상 설정
    text.setPosition(200, 250);  // 텍스트 위치 설정

    // 게임 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 화면을 하얀색으로 채우기
        window.clear(sf::Color::Black);

        // 텍스트 그리기
        window.draw(text);

        // 화면에 그린 내용을 표시
        window.display();
    }

    return 0;
}
