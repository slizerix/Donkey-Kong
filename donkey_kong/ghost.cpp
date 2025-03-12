#include "ghost.h"

void ghost::cycle_ghost() {
	if (pBoard->getChar(x, y) != 'H' && pBoard->getChar(x, y) != '&' && pBoard->getChar(x, y) != 'p' && pBoard->getChar(x, y) != '$') { pBoard->setChar(x, y, ' '); }
	where_to_move();
	erase();
	move();
	if (pBoard->getChar(x, y) != 'H' && pBoard->getChar(x, y) != '&' && pBoard->getChar(x, y) != 'p' && pBoard->getChar(x, y) != '$') { pBoard->setChar(x, y, 'x'); }
	draw();
}

void ghost::where_to_move() {
	if (dir.x == 1 && pBoard->getChar(x + 2, y) == 'x') {
		dir = { -1,0 };
	}
	else if (dir.x == -1 && pBoard->getChar(x - 2, y) == 'x') {
		dir = { 1,0 };
	}
	else if (pBoard->getChar(x + 1, y + 1) == ' ' || pBoard->getChar(x + 1, y) == 'Q' || pBoard->getChar(x + 1, y) == 'x') {
		dir = { -1,0 };
	}
	else if (pBoard->getChar(x - 1, y + 1) == ' ' || pBoard->getChar(x - 1, y) == 'Q' || pBoard->getChar(x - 1, y) == 'x') {
		dir = { 1,0 };
	}
	else {
		// Generate a random number between 0 and 99
		int randomValue = std::rand() % 100;
		// 5% chance change dir 
		if (randomValue > 95) {
			if (dir.x == 1) { dir.x = -1; }
			else { dir.x = 1; }
		}
		//changes the direction 
	}
	
}

