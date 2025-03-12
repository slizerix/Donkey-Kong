#include "enemy.h"

void enemy::move() {
	int newX = x + dir.x;
	int newY = y + dir.y;
	x = newX;
	y = newY;
}

void enemy::erase() {
	if (pBoard->getChar(x, y) == 'H')
		draw('H');
	else if (pBoard->getChar(x, y) == '&')
		draw('&');
	else if (pBoard->getChar(x, y) == '$')
		draw('$');
	else if (pBoard->getChar(x, y) == 'p')
		draw('p');
	else
		draw(' ');
}

