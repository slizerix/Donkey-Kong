#pragma once

#include <iostream>
#include "utils.h"
#include "Board.h"
#include <cstdlib>  
#include <ctime>    // For std::time()

class enemy{
	friend class barrels;			// So barrels will be able to accesss x,y and DIR 
	friend class ghost;			// So ghosts will be able to accesss x,y and draw()
	friend class ghost_2;			// So ghosts2 will be able to accesss x,y and draw()
	struct Direction { int x, y; }; // inner private struct
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int x, y;
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}
	// Draw func 
public:
	Board* pBoard = nullptr;

	void erase();
	void move();

	int getX()const { return x; };
	int getY()const { return y; };
};

