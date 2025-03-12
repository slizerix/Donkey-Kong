#pragma once
#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdlib> // For system()
#include <windows.h>
#include <string>

enum board_type {MENU = '0', INSTRUCTIONS = '8', GAME = '1', LOST = '7', WON ='4',EXIT = '9', INVALID = '3', SELECTOR = '2' };
static constexpr int MAX_X = 80;
static constexpr int MAX_Y = 25;

class Board {
	
	//The screens the we use during the game 
	const char* menu[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                                                                              Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                                                                              Q", // 5
		  "Q                       ~~~ WELCOME TO THE GAME MENU ~~~                       Q", // 6
		  "Q                                                                              Q", // 7
		  "Q                       --------------------------------                       Q", // 8
		  "Q                            1. Start a New Game                               Q", // 9
		  "Q                            2. Screen Selector                                Q", // 10
		  "Q                            8. Instructions and Keys                          Q", // 11
		  "Q                            9. Exit                                           Q", // 12
		  "Q                                                                              Q", // 13
		  "Q                       --------------------------------                       Q", // 14
		  "Q                                                                              Q", // 15
		  "Q                                                                              Q", // 16
		  "Q                                                                              Q", // 17
		  "Q                        Thank you for playing our game!                       Q", // 18
		  "Q                                                                              Q", // 19
		  "Q                                                                              Q", // 20
		  "Q                                                                              Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                                                                              Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};




	const char* instructions[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                           ~~~ INSTRUCTIONS ~~~                               Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                          How to Play Donkey Kong:                            Q", // 5
		  "Q                                                                              Q", // 6
		  "Q - The objective is to navigate your character to the top of the screen,      Q", // 7
		  "Q   avoiding barrels and other obstacles, to rescue the princess.              Q", // 8
		  "Q - Use the keys below to control your character.                              Q", // 9
		  "Q                                                                              Q", // 10
		  "Q                                                                              Q", // 11
		  "Q                                 CONTROLS:                                    Q", // 12
		  "Q                               A - Move Left                                  Q", // 13
		  "Q                               D - Move Right                                 Q", // 14
		  "Q                               W - Jump / Move Up                             Q", // 15
		  "Q                               X - Move Down                                  Q", // 16
		  "Q                               S - Stay in Place                              Q", // 17
		  "Q                                                                              Q", // 18
		  "Q - Avoid barrels by jumping over them or moving out of their path.            Q", // 19
		  "Q - Climb ladders to progress to the next level.                               Q", // 20
		  "Q - Time your moves carefully to avoid falling or getting hit by obstacles.    Q", // 21
		  "Q                                                                              Q", // 22
		  "Q   Good luck and have fun! Press 0 for MENU or 1 for GAME                     Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};


	const char* won[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                        ~~~ YOU WON! ~~~                                      Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                        Congratulations!                                      Q", // 5
		  "Q                                                                              Q", // 6
		  "Q                        You have completed the game!                          Q", // 7
		  "Q                                                                              Q", // 8
		  "Q                        Thank you for playing!                                Q", // 9
		  "Q                                                                              Q", // 10
		  "Q                        Press any key to return to the menu!                  Q", // 11
		  "Q                                                                              Q", // 12
		  "Q                                                                              Q", // 13
		  "Q                                                                              Q", // 14
		  "Q                                                                              Q", // 15
		  "Q                                                                              Q", // 16
		  "Q                                                                              Q", // 17
		  "Q                                                                              Q", // 18
		  "Q                                                                              Q", // 19
		  "Q                                                                              Q", // 20
		  "Q                                                                              Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                        Good job and enjoy your victory!                      Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	const char* lost[MAX_Y] = {
	  // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		"Q                                                                              Q", // 1
		"Q                                                                              Q", // 2
		"Q                        ~~~ YOU LOST! ~~~                                     Q", // 3
		"Q                                                                              Q", // 4
		"Q                        Better luck next time!                                Q", // 5
		"Q                                                                              Q", // 6
		"Q                        You didn't complete the game.                         Q", // 7
		"Q                                                                              Q", // 8
		"Q                        Don't give up, try again!                             Q", // 9
		"Q                                                                              Q", // 10
		"Q                        Press any key to return to the menu!                  Q", // 11
		"Q                                                                              Q", // 12
		"Q                                                                              Q", // 13
		"Q                                                                              Q", // 14
		"Q                                                                              Q", // 15
		"Q                                                                              Q", // 16
		"Q                                                                              Q", // 17
		"Q                                                                              Q", // 18
		"Q                                                                              Q", // 19
		"Q                                                                              Q", // 20
		"Q                                                                              Q", // 21
		"Q                                                                              Q", // 22
		"Q                                                                              Q", // 23
		"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	const char* invalid_screen[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                                                                              Q", // 2
		  "Q                        *** INVALID GAME FILE ***                             Q", // 3
		  "Q                                                                              Q", // 4
		  "Q                 The current file of the game is invalid or missing.          Q", // 5
		  "Q                                                                              Q", // 6
		  "Q                        Please check your game files.                         Q", // 7
		  "Q                                                                              Q", // 8
		  "Q                     Press any key to proceed to the next screen.             Q", // 9
		  "Q                                                                              Q", // 10
		  "Q                                                                              Q", // 11
		  "Q                                                                              Q", // 12
		  "Q                                                                              Q", // 13
		  "Q                                                                              Q", // 14
		  "Q                                                                              Q", // 15
		  "Q                                                                              Q", // 16
		  "Q                                                                              Q", // 17
		  "Q                                                                              Q", // 18
		  "Q                                                                              Q", // 19
		  "Q                                                                              Q", // 20
		  "Q                                                                              Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                                                                              Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	const char* screen_selector[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q                           *** SCREEN SELECTOR ***                            Q", // 2
		  "Q                                                                              Q", // 3
		  "Q                  Please choose a screen to navigate to:                      Q", // 4
		  "Q                                                                              Q", // 5
		  "Q                  there are currently    screens.                             Q", // 6
		  "Q                                                                              Q", // 7
		  "Q                                                                              Q", // 8
		  "Q                                                                              Q", // 9
		  "Q                                                                              Q", // 10
		  "Q                                                                              Q", // 11
		  "Q                  screen number:                                              Q", // 12
		  "Q                                                                              Q", // 13
		  "Q                                                                              Q", // 14
		  "Q                                                                              Q", // 15
		  "Q                                                                              Q", // 16
		  "Q                                                                              Q", // 17
		  "Q                                                                              Q", // 18
		  "Q                                                                              Q", // 19
		  "Q                                                                              Q", // 20
		  "Q                                                                              Q", // 21
		  "Q                                                                              Q", // 22
		  "Q                                                                              Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};


	char game[MAX_Y][MAX_X + 1];

	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator

public:
	void load(board_type bt);		//The func loads the wanted screen 
	void print() const;
	char getChar(int x, int y) const { return currentBoard[y][x]; }
	void setChar(int x, int y, char c) { currentBoard[y][x] = c; }
	void clearScreen() { system("cls"); }
	void changeScreen(std::string textName);
	bool searchChar(char c, int& newX, int& newY);
};

