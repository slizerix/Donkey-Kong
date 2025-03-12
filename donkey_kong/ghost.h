#pragma once
#include "enemy.h"

class ghost: public enemy
{
	const char ch = 'x';

public: 
	ghost(int x_, int y_){
		x = x_; 
		y = y_; 
		dir = { 1 , 0 };
	}

	virtual void cycle_ghost();
	void where_to_move();
	void draw() const {
		enemy::draw(ch);
	}
	ghost& operator=(const ghost& other) {
		if (this != &other) { // Check for self-assignment
			// Copy base class members
			this->x = other.x;
			this->y = other.y;
			this->dir = other.dir;
			// Note: `ch` is `const` and cannot be reassigned
		}
		return *this;

	}
};

