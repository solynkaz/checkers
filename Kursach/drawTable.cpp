#include "Header.h"
using namespace std;

void drawEmptyTable(sf::RenderWindow* window) {
	sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.f)); // Создание прямоугольника (квадрата) 100/100
	rectangle.setFillColor(sf::Color(255, 255, 255)); // rgb цвет прямоугольника
	float y = 0, x = 0;
	for (y = 0; y <= 700; y += 100) {
		for (int i = 0; i < 4; x += 200, i++) {
			rectangle.setPosition(x, y);
			window->draw(rectangle);
		}
		if (x == 800) x = 100;
		else x = 0;
	}// Конец вывода игрового поля
}