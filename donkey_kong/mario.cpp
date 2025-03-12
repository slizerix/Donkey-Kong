#include "mario.h"

void Mario::keyPressed(char key) {
	for (size_t i = 0; i < numKeys; i++) {
		if (std::tolower(key) == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

void Mario::move() {
	int newX = x + dir.x;
	int newY = y + dir.y;
	// Better use a function in Board to check if the new position is valid
	// + Better use a constant for the wall character
	if (pBoard->getChar(newX, newY) == 'Q' || pBoard->getChar(newX, newY) == '=' ||
		pBoard->getChar(newX, newY) == '<' || pBoard->getChar(newX, newY) == '>') {
		dir = { 0, 0 };
	}
	else {
		x = newX;
		y = newY;
	}
}

bool Mario::is_on_platform()const {
	if (pBoard->getChar(x, y + 1) == ' ')
		return false;
	else
		return true;
}

void Mario::up(int& jumps) {
		if (jumps == 0) {
			dir.y = -1;
		}
		jumps++;
}

bool Mario::isMarioFalling() {
	if (pBoard->getChar(x,y + 1) != '>' &&
		pBoard->getChar(x, y + 1) != '<' &&
		pBoard->getChar(x,y + 1) != '=') {
		return  true;
	}
	return false;
}

void Mario::erase()const {
	if ((pBoard->getChar(x, y) == 'H'))
		draw('H');
	else if ((pBoard->getChar(x, y) == '&'))
		draw('&');
	else
		draw(' ');
}
//make sure dowst erease ladders

bool Mario::hammerTime() const {
	if ((pBoard->getChar(x, y) == 'p')) {
		pBoard->setChar(x, y, ' ');
		return true;
	}
	return false;
}