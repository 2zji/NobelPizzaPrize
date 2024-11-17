#include "description.h"

// ���� ȭ���� �׸��� �Լ� ����
void drawDescriptionScreen(sf::RenderWindow& window, sf::Font& font, sf::RectangleShape& startButton, sf::Text& startButtonText) {
    sf::Text descriptionText;
    descriptionText.setFont(font);
    descriptionText.setString(
        L"1. �ֹ��� ���� ���۷δ�, �Ǵ� �������� ���ڸ� �����.\n"
        L"2. ���ڵ���->�丶�� �ҽ�->ġ��->���۷δ� or �������� ������ �ִ´�.\n"
        L"3. ���쿡 �ִ´�.(���쿡 ���� ��, �������� �ڵ� ����)\n\n"
        L"�ڼ����� Ʋ�� ��, -1000�� / ���۷δ� 1500��, �������� 2000����");
    descriptionText.setCharacterSize(25);
    descriptionText.setFillColor(sf::Color::Black);
    descriptionText.setPosition(50, 50);

    // ���� ȭ�鿡 �ʿ��� ��� �׸���
    window.draw(descriptionText);
    window.draw(startButton);
    window.draw(startButtonText);
}
