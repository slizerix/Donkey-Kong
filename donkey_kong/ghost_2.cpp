#include "ghost_2.h"


void ghost_2::cycle_ghost() {
	bool on_ladder = false;
	bool isDown = false;
	bool isUp = false;
	bool isFirst = false;

	if (pBoard->getChar(x, y) != 'H' && pBoard->getChar(x, y) != '&' && pBoard->getChar(x, y) != 'p' && pBoard->getChar(x, y) != '$') { pBoard->setChar(x, y, ' '); }

	

	if (pBoard->getChar(x, y) == 'H') {
		int randomValue = std::rand() % 3;
		if (randomValue == 0) {
			on_ladder = true;	
			dir = { 0,-1 };
		}
		if (((pBoard->getChar(x, y - 1) == '=') ||
			(pBoard->getChar(x, y - 1) == '>') ||
			(pBoard->getChar(x, y - 1) == '<')) && dir.y == -1)
		{
			dir = { 0,-2 };
			erase();
			move();
			enemy::draw('X');
			int randDirX = std::rand() % 2 == 0 ? 1 : -1;
			dir = { randDirX,0 };
			on_ladder = false; // Exit ladder mode
		}
		
		else if (((pBoard->getChar(x, y + 1) == '=') ||
			(pBoard->getChar(x, y + 1) == '>') ||
			(pBoard->getChar(x, y + 1) == '<')) && dir.y == 1)
		{
			int randDirX = std::rand() % 2 == 0 ? 1 : -1;
			dir = { randDirX,0 };
			isDown = false;
			on_ladder = false; // Exit ladder mode
		}
	}
	else if (pBoard->getChar(x, y + 2) == 'H' && dir.y != -1) {

		int randomValue = std::rand() % 3;
		if (randomValue == 0) {
			on_ladder = true;
			isDown = true;
			dir = { 0,2 };
			erase();
			move();
			enemy::draw('X');
			dir = { 0,1 };
		}
	}
	else
		where_to_move(on_ladder);

	erase();
	move();
	
	
	    

		if (pBoard->getChar(x, y) != 'H' && pBoard->getChar(x, y) != '&' && pBoard->getChar(x, y) != 'p' && pBoard->getChar(x, y) != '$') { pBoard->setChar(x, y, 'x'); }
		enemy::draw('X');
}

void ghost_2::where_to_move(bool on_ladder) {

		if (!on_ladder) {
			if (dir.x == 1 && pBoard->getChar(x + 2, y) == 'x' || dir.x == 1 && pBoard->getChar(x + 2, y) == 'X') {
				dir = { -1,0 };
			}
			else if ((dir.x == -1 && pBoard->getChar(x - 2, y) == 'x' || dir.x == -1 && pBoard->getChar(x - 2, y) == 'X')) {
				dir = { 1,0 };
			}
			else if ((pBoard->getChar(x + 1, y + 1) == ' ' || pBoard->getChar(x + 1, y) == 'Q' || pBoard->getChar(x + 1, y) == 'x')) {
				dir = { -1,0 };
			}
			else if ((pBoard->getChar(x - 1, y + 1) == ' ' || pBoard->getChar(x - 1, y) == 'Q' || pBoard->getChar(x - 1, y) == 'x')) {
				dir = { 1,0 };
			}
			else  {
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
	}





