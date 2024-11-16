#include "description.h"

// ���� ȭ���� �������ϴ� �Լ� ����
void drawDescriptionScreen(sf::RenderWindow& window, sf::Font& font) {
    sf::Text descriptionText;
    descriptionText.setFont(font);
    descriptionText.setString(
        L"���� ����\n\n"
        L"1. �ֹ��� ���ڸ� ���弼��.\n"
        L"2. ���� �ð��� 60���Դϴ�.\n"
        L"3. ���ڸ� �� ����� ������ ����ϴ�.\n\n"
        L"ESC�� ���� ���ư���");
    descriptionText.setCharacterSize(25);
    descriptionText.setFillColor(sf::Color::Black);
    descriptionText.setPosition(50, 50);

    window.draw(descriptionText);
}
