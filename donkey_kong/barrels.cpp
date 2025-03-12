#include "barrels.h"

void barrels::b_where_to_move() {		//Implement limitations in barrel movement 
	if (!b_is_on_platform()) {
		dir = { 0,1 };
		fall_counter++;
		if (fall_counter == 8) { explode = true; }
	}
	if (pBoard->getChar(x + 1, y) == 'Q') {
		erase();
		active = false;
		fall_counter = 0;
	}
	else if (pBoard->getChar(x - 1, y) == 'Q') {
		erase();
		active = false;
		fall_counter = 0;
	}
	if (pBoard->getChar(x, y + 1) == '>') {
		dir = last_dir = { 1,0 };
		fall_counter = 0;
		if (explode == true) { barrel_explode(); }
	}
	else if (pBoard->getChar(x, y + 1) == '<') {
		dir = last_dir = { -1,0 };
		fall_counter = 0;
		if (explode == true) { barrel_explode(); }
	}
	else if (pBoard->getChar(x, y + 1) == '=') {
		dir = last_dir;
		fall_counter = 0;
		if (explode == true) { barrel_explode(); }
	}
}

void barrels::barrel_explode() {
	erase();

	// Draw explosion in the 2x2 radius above (x, y)
	for (int i = -2; i <= 2; ++i) {  // Horizontal range
		for (int j = -2; j <= 0; ++j) {  // Vertical range: only above and center
			if (i * i + j * j <= 4) { // Ensures circular effect (radius 2)
				gotoxy(x + i, y + j);
				std::cout << '*';
			}
		}
	}

	Sleep(40); // Pause to show explosion effect

	// Erase explosion
	for (int i = -2; i <= 2; ++i) {  // Horizontal range
		for (int j = -2; j <= 0; ++j) {  // Vertical range: only above and center
			if (i * i + j * j <= 4) {
				gotoxy(x + i, y + j);
				std::cout << ' '; // Clear the explosion
			}
		}
	}

	active = false;

}

bool barrels::b_is_on_platform() const {		//Checks if on platform			
	if (pBoard->getChar(x, y + 1) == ' ')
		return false;
	else
		return true;
}

bool barrels::cycle_barrel() {		//One cycle of barrel
	if (active) {
		erase();
		b_where_to_move();
		if (active == false) { return true; }		//returns true then a barrel exploded
		//if it is inactive after where to move it means that the barrel exploded
		move();
		draw();
	}
	return false;
}
//the func return true when barrel exploded

