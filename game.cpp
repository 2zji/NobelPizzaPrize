#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <locale>
#include <codecvt>

// wstring�� UTF-8�� ��ȯ�ϴ� �Լ�
std::string wstringToString(const std::wstring& wstr) {
    // std::wstring_convert�� C++11���� �߰��� �Լ���, wstring�� string���� ��ȯ�� �� �ֽ��ϴ�.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr); // UTF-8�� ��ȯ
}

void startGame() {
    sf::RenderWindow gameWindow(sf::VideoMode(800, 600), L"�뺧���ڻ�");

    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        std::cerr << "��Ʈ�� �ҷ��� �� �����ϴ�!" << std::endl;
        return;
    }

    // Ÿ�̸� ����
    sf::Clock clock;
    sf::Time elapsedTime;
    int remainingTime = 60; // 60��

    // Ÿ�̸� �ؽ�Ʈ
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

        // �ð� ���
        elapsedTime = clock.getElapsedTime();
        int elapsedSeconds = static_cast<int>(elapsedTime.asSeconds());
        remainingTime = 60 - elapsedSeconds;

        // �ð��� ������ ������ ����
        if (remainingTime <= 0) {
            remainingTime = 0;
            // ���� ���� ���� (���� ���� ȭ��)
            gameWindow.close();
        }

        // Ÿ�̸� �ؽ�Ʈ ������Ʈ
        std::wstring wstr = std::to_wstring(remainingTime);
        std::string str = wstringToString(wstr);  // wstring�� UTF-8�� ��ȯ

        // �ؽ�Ʈ ������Ʈ
        timerText.setString(str);

        gameWindow.clear(sf::Color(255, 241, 184)); // ����
        gameWindow.draw(timerText); // Ÿ�̸� �ؽ�Ʈ
        gameWindow.display();
    }
}
