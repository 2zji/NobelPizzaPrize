#include <SFML/Graphics.hpp>

int main() {
    // SFML â ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML �ѱ� ����");

    // �ѱ� ��Ʈ �ε�
    sf::Font font;
    if (!font.loadFromFile("BagelFatOne-Regular.ttf")) {
        return -1;  // ��Ʈ �ε� ���� �� ����
    }

    // �ؽ�Ʈ ��ü ����
    sf::Text text(L"�ȳ��ϼ���, SFML!", font, 30);
    text.setFillColor(sf::Color::White);  // �ؽ�Ʈ ���� ����
    text.setPosition(200, 250);  // �ؽ�Ʈ ��ġ ����

    // ���� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ȭ���� �Ͼ������ ä���
        window.clear(sf::Color::Black);

        // �ؽ�Ʈ �׸���
        window.draw(text);

        // ȭ�鿡 �׸� ������ ǥ��
        window.display();
    }

    return 0;
}
