#pragma once

#include <iostream>

#include "utils.h"
#include "Board.h"

//

class Mario {
	static constexpr char keys[] = { 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);

	struct Direction { int x, y; }; // inner private struct
	// the directions array order is exactly the same as the keys array - must keep it that way
	static constexpr Direction directions[] = { {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int x, y;
	int x_won, y_won;

	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	const char ch = '@';
	int fallCounter = 0;

	void draw(char c) const {
		gotoxy(x, y);
		std::cout << c;
	}

public:
	Board* pBoard = nullptr;

	void draw() const { draw(ch); }
	void erase()const;
	void keyPressed(char key);
	void move();
	void setXsetY(int x_, int y_) { x = x_; y = y_; }
	//Gneral mario functions

	//canges locally 

	bool is_on_platform()const;
	void up(int& jumps);
	bool isMarioFalling();
	int getDirx() { return dir.x; }
	void setDirY(int y) { dir.y = y; }
	void setDirX(int x) { dir.x = x; }
	void AdvanceFallCounter() { fallCounter++; }
	void NullifyFallCounter() { fallCounter = 0; }
	//Handels jump and fall

	char retun_char()const { return pBoard->getChar(x, y); }
	char return_char_upper()const { return pBoard->getChar(x, y - 1); }
	char return_char_lower()const { return pBoard->getChar(x, y + 1); }
	char return_char_2lower()const { return pBoard->getChar(x, y + 2); }
	int return_fallCounter()const { return fallCounter; }
	//Get chars around mario for ladder handeling

	int getX()const { return x; }
	int getY()const { return y; }
	//Checking collisiong with barrels

	bool hammerTime() const;
	void set_win(int x_, int y_) { x_won = x_; y_won = y_; }
	bool mario_won()const { return (x == x_won && y == y_won); }		
	//Checks if mario got to pauline
	
};
