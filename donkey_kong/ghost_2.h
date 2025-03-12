#pragma once

#include "ghost.h"

class ghost_2 : public ghost
{
	const char ch = 'X';

public:

	ghost_2(int x_, int y_) : ghost(x_, y_) {
		dir = { 1 , 0 };
	}

	ghost_2& operator=(const ghost_2& other) {
		if (this != &other) { // Check for self-assignment
			// Copy base class members
			this->x = other.x;
			this->y = other.y;
			this->dir = other.dir;
			// Note: `ch` is `const` and cannot be reassigned
		}
		return *this;

	}

	void setDirY(int y) { dir.y = y; }
	void setDirX(int x) { dir.x = x; }
	void cycle_ghost();
	void where_to_move(bool on_ladder);

};

