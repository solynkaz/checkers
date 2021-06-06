#include "Header.h"
class Check { // Класс шашки
private:
	bool white; // true - белая 
	bool eaten = false; // false - не съедена, true - съедена
	bool queen = false;
	sf::Sprite checkSprite;
public:
	void setSprite(sf::Sprite curSprite) {
		this->checkSprite = curSprite;
	}
	sf::Sprite getSprite() {
		return this->checkSprite;
	}

	void setColor(bool isWhite) {
		if (isWhite) this->white = true;
		else this->white = false;
	}
	bool getColor() { // true - белые, false - черные
		return this->white;
	
	}

	sf::Vector2i getPos() {
		sf::Vector2i vect;
		vect.x = this->checkSprite.getPosition().x;
		vect.y = this->checkSprite.getPosition().y;
		return vect;
	}
	void setPos(float x, float y) {
		this->checkSprite.setPosition(x, y);
	}

	void setEaten(bool yes) {
		if (yes) this->eaten = true;
		else this->eaten = false;
	}
	bool getEaten() {
		return this->eaten;
	}

	void setQueen(bool yes, sf::Texture* txt) {
		this->queen = yes;
		this->checkSprite.setTexture(*txt);
	}
	bool isQueen() {
		return this->queen;
	}
};
class Cell { // Класс клетки, геттеры сеттеры
private:
	sf::Vector2i cellStart;
	sf::Vector2i cellEnd;
	bool picked = false;
	Check* curCheck = nullptr;  // Шашка которая хранится на ячейке

public:
	void setPick(bool isPicked) {
		this->picked = isPicked;
	}
	bool getPick() {
		return this->picked;
	}

	void setCheck(Check* check) {
		this->curCheck = check;
	}
	Check* getCheck() {
		if (this->curCheck == nullptr) return nullptr;
		else return curCheck;
	}
	void setCellStart(short a, short b) {
		this->cellStart.x = a;
		this->cellStart.y = b;
	}
	sf::Vector2i getCellStart() {
		return this->cellStart;
	}

	void setCellEnd(short a, short b) {
		this->cellEnd.x = a;
		this->cellEnd.y = b;
	}
	sf::Vector2i getCellEnd() {
		return this->cellEnd;
	}

	
};

short canEatQueen(Cell* mas, short highlighted) {
	short bordersUp[4]    = { 1, 3, 5, 7 };
	short bordersDown[4]  = { 56, 58, 60, 62 };
	short bordersLeft[4]  = { 8, 24, 40, 56 };
	short bordersRight[4] = { 7, 23, 39, 55 };
	//LeftUp
	bool skip = false;
	short free = highlighted - 18;
	short busy = highlighted - 9;
	for (short i = 0; i < 8; i++) {
		for (short a : bordersUp) {
			if (busy == a || busy < 0 || free < 0) {
				skip = true;
				break;
			}
		}
		for (short a : bordersLeft) {
			if (busy == a || busy < 0 || free < 0) {
				skip = true;
				break;
			}
		}
		if (skip) break;
		else {
			if (mas[free].getCheck() == nullptr && mas[busy].getCheck() != nullptr) {
				if (mas[busy].getCheck()->getColor() != mas[highlighted].getCheck()->getColor()) {
					return 1;
				}
			}
			else if (mas[free].getCheck() != nullptr && mas[busy].getCheck() != nullptr) break;
			else {
				free -= 9;
				busy -= 9;
			}
		}
	}
	skip = false;
	//RightUp
	free = highlighted - 14;
	busy = highlighted - 7;
	for (short i = 0; i < 8; i++) {
		for (short a : bordersUp) {
			if (busy == a || busy < 0 || free < 0) {
				skip = true;
				break;
			}
		}
		for (short a : bordersRight) {
			if (busy == a || busy < 0 || free < 0) {
				skip = true;
				break;
			}
		}
		if (skip) break;
		else {
			if (mas[free].getCheck() == nullptr && mas[busy].getCheck() != nullptr) {
				if (mas[busy].getCheck()->getColor() != mas[highlighted].getCheck()->getColor()) {
					return 1;
				}
			}
			else if (mas[free].getCheck() != nullptr && mas[busy].getCheck() != nullptr) break;
			else {
				free -= 7;
				busy -= 7;
			}
		}
	}
	//LeftDown
	//19 26 33 40
	skip = false;
	free = highlighted + 14;
	busy = highlighted + 7;
	for (short i = 0; i < 8; i++) {
		for (short a : bordersDown) {
			if (busy == a || busy > 62 || free > 62) {
				skip = true;
				break;
			}
		}
		for (short a : bordersLeft) {
			if (busy == a || busy > 62 || free > 62) {
				skip = true;
				break;
			}
		}
		if (skip) break;
		else {
			if (mas[free].getCheck() == nullptr && mas[busy].getCheck() != nullptr) {
				if (mas[busy].getCheck()->getColor() != mas[highlighted].getCheck()->getColor()) {
					return 1;
				}
			}
			else if (mas[free].getCheck() != nullptr && mas[busy].getCheck() != nullptr) break;
			else {
				free += 7;
				busy += 7;
			}
		}
	}
	//RightDown
	skip = false;
	free = highlighted + 18;
	busy = highlighted + 9;
	for (short i = 0; i < 8; i++) {
		for (short a : bordersDown) {
			if (busy == a || busy > 62 || free > 62) {
				skip = true;
				break;
			}
		}
		for (short a : bordersRight) {
			if (busy == a || busy > 62 || free > 62) {
				skip = true;
				break;
			}
		}
		if (skip) break;
		else {
			if (mas[free].getCheck() == nullptr && mas[busy].getCheck() != nullptr) {
				if (mas[busy].getCheck()->getColor() != mas[highlighted].getCheck()->getColor()) {
					return 1;
				}
			}
			else if (mas[free].getCheck() != nullptr && mas[busy].getCheck() != nullptr) break;
			else {
				free += 9;
				busy += 9;
			}
		}
	}
	return 0;
}

short canEat(Cell* mas, short highlighted) {
	short between = 0;
	short free = 0;
	for (short i = 0; i < 64; i++) {
		//Проверка на соседов слева вверх
		if (mas[highlighted].getCellStart().x - 100 == mas[i].getCellStart().x && mas[highlighted].getCellStart().y - 100 == mas[i].getCellStart().y) {
			between = i;
			for (short j = 0; j < 64; j++) {
				if (mas[between].getCellStart().x - 100 == mas[j].getCellStart().x && mas[between].getCellStart().y - 100 == mas[j].getCellStart().y) {
					free = j;
					if (mas[free].getCheck() == nullptr && mas[between].getCheck() != nullptr && mas[between].getCheck()->getColor() != mas[highlighted].getCheck()->getColor()) {
						return 1;
					}
				}
			}
		}
		// Проверка на соседов справа вверх
		else if (mas[highlighted].getCellStart().x + 100 == mas[i].getCellStart().x && mas[highlighted].getCellStart().y - 100 == mas[i].getCellStart().y) {
			between = i;
			for (short j = 0; j < 64; j++) {
				if (mas[between].getCellStart().x + 100 == mas[j].getCellStart().x && mas[between].getCellStart().y - 100 == mas[j].getCellStart().y) {
					free = j;
					if (mas[free].getCheck() == nullptr && mas[between].getCheck() != nullptr && mas[between].getCheck()->getColor() != mas[highlighted].getCheck()->getColor()) {
						return 1;
					}
				}
			}
		}
		// Проверка на соседов слева вниз
		else if (mas[highlighted].getCellStart().x - 100 == mas[i].getCellStart().x && mas[highlighted].getCellStart().y + 100 == mas[i].getCellStart().y) {
			between = i;
			for (short j = 0; j < 64; j++) {
				if (mas[between].getCellStart().x - 100 == mas[j].getCellStart().x && mas[between].getCellStart().y + 100 == mas[j].getCellStart().y) {
					free = j;
					if (mas[free].getCheck() == nullptr && mas[between].getCheck() != nullptr && mas[between].getCheck()->getColor() != mas[highlighted].getCheck()->getColor()) {
						return 1;
					}
				}
			}
		}
		// Проверка на соседов справа вниз
		else if (mas[highlighted].getCellStart().x + 100 == mas[i].getCellStart().x && mas[highlighted].getCellStart().y + 100 == mas[i].getCellStart().y) {
			between = i;
			for (short j = 0; j < 64; j++) {
				if (mas[between].getCellStart().x + 100 == mas[j].getCellStart().x && mas[between].getCellStart().y + 100 == mas[j].getCellStart().y) {
					free = j;
					if (mas[free].getCheck() == nullptr && mas[between].getCheck() != nullptr && mas[between].getCheck()->getColor() != mas[highlighted].getCheck()->getColor()) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

bool canMoveWhite(Cell* mas, short highlighted) {
	short between = 0;
	short free = 0;
	bool sleva = false;
	bool sprava = false;
	for (short i = 0; i < 64; i++) {
		//Проверка на соседов слева вверх
		if (mas[highlighted].getCellStart().x - 100 == mas[i].getCellStart().x && mas[highlighted].getCellStart().y - 100 == mas[i].getCellStart().y) {
			between = i;
			for (short j = 0; j < 64; j++) {
				if (mas[between].getCellStart().x - 100 == mas[j].getCellStart().x && mas[between].getCellStart().y - 100 == mas[j].getCellStart().y) {
					free = j;
					if (mas[between].getCheck() == nullptr) {
						sleva = true;
					}
				}
			}
		}
		// Проверка на соседов справа вверх
		else if (mas[highlighted].getCellStart().x + 100 == mas[i].getCellStart().x && mas[highlighted].getCellStart().y - 100 == mas[i].getCellStart().y) {
			between = i;
			for (short j = 0; j < 64; j++) {
				if (mas[between].getCellStart().x + 100 == mas[j].getCellStart().x && mas[between].getCellStart().y - 100 == mas[j].getCellStart().y) {
					free = j;
					if (mas[between].getCheck() == nullptr) {
						sprava = true;
					}
				}
			}
		}
	}
	if (sleva || sprava) return true;
	else return false;
}
bool canMoveBlack(Cell* mas, short highlighted) {
	short between = 0;
	short free = 0;
	bool sleva = false;
	bool sprava = false;
	for (short i = 0; i < 64; i++) {
		// Проверка на соседов слева вниз
		if (mas[highlighted].getCellStart().x - 100 == mas[i].getCellStart().x && mas[highlighted].getCellStart().y + 100 == mas[i].getCellStart().y) {
		between = i;
		for (short j = 0; j < 64; j++) {
			if (mas[between].getCellStart().x - 100 == mas[j].getCellStart().x && mas[between].getCellStart().y + 100 == mas[j].getCellStart().y) {
				free = j;
				if (mas[between].getCheck() == nullptr) {
					sleva = true;
				}
			}
		}
		}
		// Проверка на соседов справа вниз
		else if (mas[highlighted].getCellStart().x + 100 == mas[i].getCellStart().x && mas[highlighted].getCellStart().y + 100 == mas[i].getCellStart().y) {
		between = i;
		for (short j = 0; j < 64; j++) {
			if (mas[between].getCellStart().x + 100 == mas[j].getCellStart().x && mas[between].getCellStart().y + 100 == mas[j].getCellStart().y) {
				free = j;
				if (mas[between].getCheck() == nullptr) {
					sprava = true;
				}
			}
		}
		}
	}
	if (sleva || sprava) return true;
	else return false;
}

bool endGame(Cell* mas, Check* masWhite, Check* masBlack) {
	short countOfWhites = 0;
	short countOfBlacks = 0;
	short bordersUp[4] = { 1, 3, 5, 7 };
	short bordersDown[4] = { 56, 58, 60, 62 };
	short bordersLeft[4] = { 8, 24, 40, 56 };
	short bordersRight[4] = { 7, 23, 39, 55 };
	bool WhiteEnd = true;
	bool BlackEnd = true;
	for (short i = 0; i < 12; i++) {
		if (countOfBlacks > 0 && countOfWhites > 0) break;
		if (countOfWhites == 0) {
			if (masWhite[i].getEaten() == false) countOfWhites++;
		}
		if (countOfBlacks == 0) {
			if (masBlack[i].getEaten() == false) countOfBlacks++;
		}
	}
	if (countOfBlacks > 0 && countOfWhites > 0) {
		for (int i = 0; i < 64; i++) {
			if (mas[i].getCheck() != nullptr) {
				if (mas[i].getCheck()->getColor()) {
					if (WhiteEnd) {
						if (canEat(mas, i) == 0) {
							if (canMoveWhite(mas, i) == true) {
								WhiteEnd = false;
							}
						}
						else {
							WhiteEnd = false;
						}
					}
				}
				else {
					if (BlackEnd) {
						if (canEat(mas, i) == 0) {
							if (canMoveBlack(mas, i) == true) {
								BlackEnd = false;
							}
						}
						else {
							BlackEnd = false;
						}
					}
				}
			}
		}
	}
	else return true;
	if (WhiteEnd || BlackEnd) return true;
	else return false;
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Checkers", sf::Style::Close | sf::Style::Titlebar); // Окно / Указатель на окно
	sf::RenderWindow* window1 = &window;

	sf::Texture*whiteQueenPtr = new sf::Texture;
	sf::Texture*blackQueenPtr = new sf::Texture;
	blackQueenPtr->loadFromFile("SrcFiles/blackQueen.png");
	whiteQueenPtr->loadFromFile("SrcFiles/whiteQueen.png");

	sf::Event event; // Обработка событий
	sf::Mouse mouse; // Экземпляр мыши

#pragma region
	//Создание массива спрайтов черной шашки
	sf::Texture* blackCheckTxt = new sf::Texture;//создаем объект Texture (текстура)
	blackCheckTxt->loadFromFile("SrcFiles/blackShashka.png");//загружаем картинку
	sf::Sprite masBlackSprites[12];//создаем объект Sprite(спрайт)
	for (short i = 0; i < 12; i++) {
		masBlackSprites[i].setTexture(*blackCheckTxt);
		masBlackSprites[i].setOrigin(40, 40);
	}

	//Создание массива спрайтов белой шашки
	sf::Texture* whiteCheckTxt = new sf::Texture;
	whiteCheckTxt->loadFromFile("SrcFiles/whiteShashka.png");
	sf::Sprite masWhiteSprites[12];
	for (short i = 0; i < 12; i++) {
		masWhiteSprites[i].setTexture(*whiteCheckTxt);
		masWhiteSprites[i].setOrigin(40, 40);
	}

	//Создание массива черных шашОк + массива указателей на них
	Check masBlackChecks[12];
	Check* masBlackPtr[12];
	short counter = 0;
	short blackX = 150, blackY = 50;
	for (short i = 1; i <= 3; i++) {
		if (counter == 4) blackX = 50;
		else blackX = 150;
		for (short j = 1; j <= 4; j++) {
			masBlackChecks[counter].setColor(false);
			masBlackChecks[counter].setSprite(masBlackSprites[counter]);
			masBlackChecks[counter].setPos(blackX, blackY);
			blackX += 200;
			counter++;
		}
		blackY += 100;
	}
	for (short i = 0; i < 12; i++) masBlackPtr[i] = &masBlackChecks[i];

	//Создание массива белых шашОк
	Check masWhiteChecks[12];
	Check* masWhitePtr[12];
	counter = 0;
	float whiteX = 50, whiteY = 550;
	for (short i = 1; i <= 3; i++) {
		for (short j = 1; j <= 4; j++) {
			masWhiteChecks[counter].setColor(true);
			masWhiteChecks[counter].setSprite(masWhiteSprites[counter]);
			masWhiteChecks[counter].setPos(whiteX, whiteY);
			counter++;
			if (whiteX == 750) {
				whiteX = 50;
				break;
			}
			else if (whiteX == 650) {
				whiteX = 150;
				break;
			}
			whiteX += 200;
		}
		whiteY += 100;
	}
	for (short i = 0; i < 12; i++) masWhitePtr[i] = &masWhiteChecks[i];

	Check* masWhitePointer = masWhiteChecks;
	Check* masBlackPointer = masBlackChecks;

#pragma endregion Massiv spritov i samih shashek

#pragma region
	//Разбитие поля на клетки
	Cell masCells[64];
	Cell* masCellsPtr = masCells;
	short i = 0;
	for (short y = 0; y < 800; y += 100) {
		for (short x = 0; x < 800; x += 100) {
			masCells[i].setCellStart(x, y);
			masCells[i].setCellEnd(x + 100, y + 100);
			i++;
		}
	}

	//Засовывание шашек в поля на клетке
	for (short i = 0; i < 64; i++) {
		for (short j = 0; j < 12; j++) {
			if
				(masCells[i].getCellStart().x < masBlackPtr[j]->getPos().x // Проверка на вхождение в ячейку одной из черных шашек
					&& masCells[i].getCellStart().y < masBlackPtr[j]->getPos().y
					&& masCells[i].getCellEnd().x > masBlackPtr[j]->getPos().x
					&& masCells[i].getCellEnd().y > masBlackPtr[j]->getPos().y) {
				masCells[i].setCheck(masBlackPtr[j]);
				break;
			}
			else if
				(masCells[i].getCellStart().x < masWhitePtr[j]->getPos().x // Проверка на вхождение в ячейку одной из черных шашек
					&& masCells[i].getCellStart().y < masWhitePtr[j]->getPos().y
					&& masCells[i].getCellEnd().x > masWhitePtr[j]->getPos().x
					&& masCells[i].getCellEnd().y > masWhitePtr[j]->getPos().y) {
				masCells[i].setCheck(masWhitePtr[j]);
				break;
			}
		}
	}
#pragma endregion Razbitie polya i prisvaivanie shashek v yacheiku

	short highlighted = NULL;
	bool highlight = false;
	bool turnWhite = true;
	sf::Vector2i pixelPos;
	while (window.isOpen())
	{
		if (endGame(masCellsPtr, *masWhitePtr, *masBlackPtr)) return 0;
		while (window.pollEvent(event)) //Список ивентов бесконечная отслеживает ивенты в окне
		{
			//if (endGame(masCellsPtr, masWhitePointer, masBlackPointer) == true) return 1;
			switch (event.type) {
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::C) {
					system("cls");
					turnWhite = !turnWhite;
				}
				else if (event.key.code == sf::Keyboard::V) {
					std::cout << "Endgame: " << endGame(masCellsPtr, masWhiteChecks, masBlackChecks) << std::endl;
				}
				break;
			case sf::Event::Closed: // Нажатие на кнопку закрытия
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				short current = 0;
				sf::Vector2i pixelPos = mouse.getPosition(window);
				short bordersUp[4] = { 1, 3, 5, 7 };
				short bordersDown[4] = { 56, 58, 60, 62 };
				for (short i = 0; i <= 56; i += 8) { // Поиск по совпадению y координаты тыка и координат первого столбца, далее проверка строки в совпавшем столбе 
					if (pixelPos.y > masCells[i].getCellStart().y && pixelPos.y < masCells[i].getCellEnd().y) {
						for (short j = 0; j < 8; j++) {
							if (pixelPos.x > masCells[i + j].getCellStart().x && pixelPos.x < masCells[i + j].getCellEnd().x) {
								current = i + j; // 
								std::cout << "Current: " << current << std::endl;
								//                  Если ячейка не выбрана		   Если ячейка имеет шашку в себе			Сравнение цвета хода с цветом шашки
								if (masCells[current].getPick() == false && masCells[current].getCheck() != nullptr) {
									if (turnWhite == masCells[current].getCheck()->getColor()) {
#pragma region
										highlight = true;
										masCells[current].setPick(true);
										highlighted = current; // highlighted - хайлайтнутая в дальнейшем ходе программы
										break;
									}
								}
#pragma endregion Первый тычок, подсветка шашки которая ходит
								else if (masCells[highlighted].getPick() && masCells[current].getCheck() == nullptr) {
									// Проверка на ход не далее одной клетки влево право + не вниз а вверх от своей стороны
#pragma region
									if (!masCells[highlighted].getCheck()->isQueen() && canEat(masCellsPtr, highlighted) == 0) { // Если не дамка и не может есть, происходит обычная проверка на ход
										if ((masCells[current].getCellStart().x > masCells[highlighted].getCellStart().x && masCells[current].getCellStart().x - masCells[highlighted].getCellStart().x == 100) // Проверка на обычный ход по x
											|| (masCells[current].getCellStart().x < masCells[highlighted].getCellStart().x && masCells[highlighted].getCellStart().x - masCells[current].getCellStart().x == 100))
										{
											if ((masCells[highlighted].getCheck()->getColor() && masCells[highlighted].getCellStart().y - masCells[current].getCellStart().y == 100) // Проверка на обычный ход по y
												|| (!masCells[highlighted].getCheck()->getColor() && masCells[current].getCellStart().y - masCells[highlighted].getCellStart().y == 100))
											{
												// Конец проверки на ход
												masCells[current].setCheck(masCells[highlighted].getCheck());
												masCells[current].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
												masCells[highlighted].setCheck(nullptr);
												masCells[highlighted].setPick(false);
												for (short g = 0; g < 64; g++) {
													masCells[g].setPick(false);
												}
												highlight = false;
												highlighted = NULL;
												if (turnWhite) turnWhite = false; else turnWhite = true; // Меняет череду хода
												break;
											}
										}
									}
#pragma endregion Второй тычок, обычный ход
									else if (!masCells[highlighted].getCheck()->isQueen() && canEat(masCellsPtr, highlighted) == 1) {
#pragma region
										bool wasEaten = false;
										for (short g = 0; g < 64; g++) {
											//Влево вверх, плюсы потому что проверяем от кьюрента назад
											if ((masCells[current].getCellStart().x + 100 == masCells[g].getCellStart().x && masCells[current].getCellStart().y + 100 == masCells[g].getCellStart().y) &&
												(masCells[current].getCellStart().x + 200 == masCells[highlighted].getCellStart().x && masCells[current].getCellStart().y + 200 == masCells[highlighted].getCellStart().y)) {
												if (masCells[g].getCheck() != nullptr && masCells[current].getCheck() == nullptr) {
													if (masCells[g].getCheck()->getColor() != masCells[highlighted].getCheck()->getColor()) {
														masCells[current].setCheck(masCells[highlighted].getCheck());
														masCells[highlighted].setCheck(nullptr);
														masCells[g].getCheck()->setEaten(true);
														masCells[g].setCheck(nullptr);
														masCells[current].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
														wasEaten = true;
														break;
													}
												}
											}
										}
										if (!wasEaten) {
											for (short g = 0; g < 64; g++) {
												//Вправо вверх, плюсы потому что проверяем от кьюрента назад
												if ((masCells[current].getCellStart().x - 100 == masCells[g].getCellStart().x && masCells[current].getCellStart().y + 100 == masCells[g].getCellStart().y) &&
													(masCells[current].getCellStart().x - 200 == masCells[highlighted].getCellStart().x && masCells[current].getCellStart().y + 200 == masCells[highlighted].getCellStart().y)) {
													if (masCells[g].getCheck() != nullptr && masCells[current].getCheck() == nullptr) {
														if (masCells[g].getCheck()->getColor() != masCells[highlighted].getCheck()->getColor()) {
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[g].getCheck()->setEaten(true);
															masCells[g].getCheck();
															masCells[g].setCheck(nullptr);
															masCells[current].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															wasEaten = true;

															break;
														}
													}
												}
											}
										}
										if (!wasEaten) {
											for (short g = 0; g < 64; g++) {
												//Влево вниз, плюсы потому что проверяем от кьюрента назад
												if ((masCells[current].getCellStart().x + 100 == masCells[g].getCellStart().x && masCells[current].getCellStart().y - 100 == masCells[g].getCellStart().y) &&
													(masCells[current].getCellStart().x + 200 == masCells[highlighted].getCellStart().x && masCells[current].getCellStart().y - 200 == masCells[highlighted].getCellStart().y)) {
													if (masCells[g].getCheck() != nullptr && masCells[current].getCheck() == nullptr) {
														if (masCells[g].getCheck()->getColor() != masCells[highlighted].getCheck()->getColor()) {
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[g].getCheck()->setEaten(true);
															masCells[g].setCheck(nullptr);
															masCells[current].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															wasEaten = true;
															break;
														}
													}
												}
											}
										}
										if (!wasEaten) {
											for (short g = 0; g < 64; g++) {
												//Вправо вниз, плюсы потому что проверяем от кьюрента назад
												if ((masCells[current].getCellStart().x - 100 == masCells[g].getCellStart().x && masCells[current].getCellStart().y - 100 == masCells[g].getCellStart().y) &&
													(masCells[current].getCellStart().x - 200 == masCells[highlighted].getCellStart().x && masCells[current].getCellStart().y - 200 == masCells[highlighted].getCellStart().y)) {
													if (masCells[g].getCheck() != nullptr && masCells[current].getCheck() == nullptr) {
														if (masCells[g].getCheck()->getColor() != masCells[highlighted].getCheck()->getColor()) {
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[g].getCheck()->setEaten(true);
															masCells[g].setCheck(nullptr);
															masCells[current].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															wasEaten = true;
															break;
														}
													}
												}
											}
										}
										if (wasEaten) {
											if (canEat(masCellsPtr, current) == 0) {
												if (turnWhite) {
													turnWhite = false;
													masCells[highlighted].setPick(false);
													masCells[current].setPick(false);
												}
												else {
													turnWhite = true;
													masCells[highlighted].setPick(false);
													masCells[current].setPick(false);
												}
											}
											else if (canEat(masCellsPtr, current) == 1) {
												masCells[highlighted].setPick(false);
												masCells[current].setPick(false);
											}
										}
									}
#pragma endregion Проверка на съедение и съедение
									else if (masCells[highlighted].getCheck()->isQueen() && canEatQueen(masCellsPtr, highlighted) == 1) { // Проверка на возможность съедания дамкой

										short bordersLeft[4] = { 8, 24, 40, 56 };
										short bordersRight[4] = { 7, 23, 39, 55 };
										bool wasEaten = false;
										/*
										LeftUp -1 / -1
										RightUp +1 / -1
										LeftDown -1 / +1
										LeftRight +1 / +
									   moving upLeft - (-9)
									   moving upRight - (-7)
									   moving downLeft - (+7)
									   moving downRight - (+9)
									   */
										short first = ((masCells[current].getCellStart().x / 100) - (masCells[highlighted].getCellStart().x / 100));
										short second = ((masCells[current].getCellStart().y / 100) - (masCells[highlighted].getCellStart().y / 100));
										if (abs(first) != abs(second)) break;
										if (first < 0 && second < 0) {
											//LeftUp
											short free = highlighted - 18;
											short busy = highlighted - 9;
											for (short i = 0; i < 8; i++) {
												if (masCells[free].getCheck() == nullptr && masCells[busy].getCheck() != nullptr) {
													if (masCells[busy].getCheck()->getColor() != masCells[highlighted].getCheck()->getColor()) {
														if (free == current) {
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[busy].getCheck()->setEaten(true);
															masCells[busy].setCheck(nullptr);
															masCells[current].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															masCells[highlighted].setPick(false);
															wasEaten = true;
															break;
														}
														else free -= 9;
													}
												}
												else if (masCells[free].getCheck() != nullptr && masCells[busy].getCheck() != nullptr) break;
												else {
													free -= 9;
													busy -= 9;
												}
											}
										}
										else if (first > 0 && second < 0) {
											//RightUp
											short free = highlighted - 14;
											short busy = highlighted - 7;
											for (short i = 0; i < 8; i++) {
												if (masCells[free].getCheck() == nullptr && masCells[busy].getCheck() != nullptr) {
													if (masCells[busy].getCheck()->getColor() != masCells[highlighted].getCheck()->getColor()) {
														if (free == current) {
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[busy].getCheck()->setEaten(true);
															masCells[busy].setCheck(nullptr);
															masCells[current].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															masCells[highlighted].setPick(false);
															wasEaten = true;
															break;
														}
														else {
															free -= 7;
														}
													}
												}
												else if (masCells[free].getCheck() != nullptr && masCells[busy].getCheck() != nullptr) break;
												else {
													free -= 7;
													busy -= 7;
												}
											}
										}
										else if (first < 0 && second > 0) {
											//LeftDown
											short free = highlighted + 14;
											short busy = highlighted + 7;
											for (short i = 0; i < 8; i++) {
												if (masCells[free].getCheck() == nullptr && masCells[busy].getCheck() != nullptr) {
													if (masCells[busy].getCheck()->getColor() != masCells[highlighted].getCheck()->getColor()) {
														if (free == current) {
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[busy].getCheck()->setEaten(true);
															masCells[busy].setCheck(nullptr);
															masCells[current].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															masCells[highlighted].setPick(false);
															wasEaten = true;
															break;
														}
														else free += 7;
													}
												}
												else if (masCells[free].getCheck() != nullptr && masCells[busy].getCheck() != nullptr) break;
												else {
													free += 7;
													busy += 7;
												}
											}
										}
										else if (first > 0 && second > 0) {
											//RightDown
											short free = highlighted + 18;
											short busy = highlighted + 9;
											for (short i = 0; i < 8; i++) {
												if (masCells[free].getCheck() == nullptr && masCells[busy].getCheck() != nullptr) {
													if (masCells[busy].getCheck()->getColor() != masCells[highlighted].getCheck()->getColor()) {
														if (free == current) {
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[busy].getCheck()->setEaten(true);
															masCells[busy].setCheck(nullptr);
															masCells[current].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															masCells[highlighted].setPick(false);
															wasEaten = true;
															break;
														}
														else free += 9;
													}
												}
												else if (masCells[free].getCheck() != nullptr && masCells[busy].getCheck() != nullptr) break;
												else {
													free += 9;
													busy += 9;
												}
											}
										}
										if (wasEaten) {
											if (canEatQueen(masCellsPtr, current) == 0) {
												if (turnWhite) turnWhite = false;
												else turnWhite = true;
											}
										}
									}
									else if (masCells[highlighted].getCheck()->isQueen() && canEatQueen(masCellsPtr, highlighted) == 0) {
										short bordersLeft[4] = { 8, 24, 40, 56 };
										short bordersRight[4] = { 7, 23, 39, 55 };
										short first = ((masCells[current].getCellStart().x / 100) - (masCells[highlighted].getCellStart().x / 100));
										short second = ((masCells[current].getCellStart().y / 100) - (masCells[highlighted].getCellStart().y / 100));
										bool wasMove = false;
										/*
										LeftUp -1 / -1
										RightUp +1 / -1
										LeftDown -1 / +1
										LeftRight +1 / +1
									   moving upLeft - (-9)
									   moving upRight - (-7)
									   moving downLeft - (+7)
									   moving downRight - (+9)
									   */
									   //LeftUP
										if (first < 0 && second < 0) {
											short next = highlighted - 9;
											for (short g = 0; g < 8; g++) {
												if (next < 0) break;
												if (masCells[next].getCheck() != nullptr) break;
												if (next == current) {
													if (abs(((masCells[current].getCellStart().x / 100) - masCells[highlighted].getCellStart().x / 100)) == abs((masCells[current].getCellStart().y / 100) - (masCells[highlighted].getCellStart().y / 100))) {
														if (masCells[current].getCheck() == nullptr) {
															masCells[highlighted].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[highlighted].setPick(false);
															wasMove = true;
															break;
														}
													}
												}
												else {
													next -= 9;
												}
											}
										}
										//RightUP
										else if (first > 0 && second < 0) {
											short next = highlighted - 7;
											for (short g = 0; g < 8; g++) {
												if (next < 0) break;
												if (masCells[next].getCheck() != nullptr) break;
												if (next == current) {
													if (abs(((masCells[current].getCellStart().x / 100) - masCells[highlighted].getCellStart().x / 100)) == abs((masCells[current].getCellStart().y / 100) - (masCells[highlighted].getCellStart().y / 100))) {
														if (masCells[current].getCheck() == nullptr) {
															masCells[highlighted].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[highlighted].setPick(false);
															wasMove = true;
															break;
														}
													}
												}
												else {
													next -= 7;
												}
											}
										}
										//LeftDown
										else if (first < 0 && second > 0) {
											short next = highlighted + 7;
											for (short g = 0; g < 8; g++) {
												if (next > 63) break;
												if (masCells[next].getCheck() != nullptr) break;
												if (next == current) {
													if (abs(((masCells[current].getCellStart().x / 100) - masCells[highlighted].getCellStart().x / 100)) == abs((masCells[current].getCellStart().y / 100) - (masCells[highlighted].getCellStart().y / 100))) {
														if (masCells[current].getCheck() == nullptr) {
															masCells[highlighted].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[highlighted].setPick(false);
															wasMove = true;
															break;
														}
													}
												}
												else {
													next += 7;
												}
											}
										}
										//RightDown
										else if (first > 0 && second > 0) {
											short next = highlighted + 9;
											for (short g = 0; g < 8; g++) {
												if (next > 63) break;
												if (masCells[next].getCheck() != nullptr) break;
												if (next == current) {
													if (abs(((masCells[current].getCellStart().x / 100) - masCells[highlighted].getCellStart().x / 100)) == abs((masCells[current].getCellStart().y / 100) - (masCells[highlighted].getCellStart().y / 100))) {
														if (masCells[current].getCheck() == nullptr) {
															masCells[highlighted].getCheck()->setPos(masCells[current].getCellStart().x + 50, masCells[current].getCellStart().y + 50);
															masCells[current].setCheck(masCells[highlighted].getCheck());
															masCells[highlighted].setCheck(nullptr);
															masCells[highlighted].setPick(false);
															wasMove = true;
															break;
														}
													}
												}
												else {
													next += 9;
												}
											}
										}
										else break;
										if (wasMove) {
											turnWhite = !turnWhite;
										}
									}

								}
								else {
									masCells[highlighted].setPick(false);
									masCells[current].setPick(false);
								}
							}
							if (masCells[current].getCheck() != nullptr) {
								for (short o = 0; o < 4; o++) {
									if (masCells[current].getCheck()->getColor()) {
										if (current == bordersUp[o]) {
											masCells[current].getCheck()->setQueen(true, whiteQueenPtr);
											break;
										}
									}
									else if (!masCells[current].getCheck()->getColor()) {
										if (current == bordersDown[o]) {
											masCells[current].getCheck()->setQueen(true, blackQueenPtr);
										}
									}
								}
							}
						}
						break;
					}
				}
				break;
			}
			window1->clear();
			drawEmptyTable(window1);
			for (short i = 0; i < 12; i++) {
				if (masBlackChecks[i].getEaten() == false) window1->draw(masBlackChecks[i].getSprite());
				if (masWhiteChecks[i].getEaten() == false) window1->draw(masWhiteChecks[i].getSprite());
				if (highlight == true && masCells[highlighted].getPick() == true) { // Если подсветка = тру и у клетки переменная выбора тру, то отрисовка подсветки выбранной клетки
					sf::RectangleShape rectangle(sf::Vector2f(100, 100)); // Создание прямоугольника (квадрата) 100/100
					rectangle.move(masCells[highlighted].getCellStart().x, masCells[highlighted].getCellStart().y);
					rectangle.setFillColor(sf::Color(255, 215, 0, 10)); // rgb цвет прямоугольника
					window1->draw(rectangle);
				}
			}
			window1->display(); // В самом конце отрисовать что должно быть на экране
		}

	}
	return 0;
}


/*
При ходе, дамка перемещается на x, y клеток, но при этом x = y, потому что ходит квадратом
*/