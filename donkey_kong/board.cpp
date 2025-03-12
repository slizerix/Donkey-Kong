
#include "Board.h"

void Board::load(board_type bt) {
	for (int i = 0; i < MAX_Y; i++) {
		if (bt == MENU)
			memcpy(currentBoard[i], menu[i], MAX_X + 1);
		else if (bt == INSTRUCTIONS)
			memcpy(currentBoard[i], instructions[i], MAX_X + 1);
		else if (bt == GAME)
			memcpy(currentBoard[i], game[i], MAX_X + 1);
		else if (bt == LOST) {
			memcpy(currentBoard[i], lost[i], MAX_X + 1);
		}
		else if (bt == WON) {
			memcpy(currentBoard[i], won[i], MAX_X + 1);
		}
		else if (bt == INVALID) {
			memcpy(currentBoard[i], invalid_screen[i], MAX_X + 1);
		}
		else if (bt == SELECTOR) {
			memcpy(currentBoard[i], screen_selector[i], MAX_X + 1);
		}
	}
}
//The func loads the wanted screen 

void Board::print() const {
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}

void Board::changeScreen(std::string textName) {

	std::ifstream file(textName);

	std::string line;
	int row = 0;

	while (std::getline(file, line) && row < MAX_Y) {
		
		for (size_t col = 0; col < line.size() && col < MAX_X; ++col) {
			game[row][col] = line[col];
		}
		
		game[row][MAX_X] = '\0';

		++row;
	}

}

bool Board::searchChar(char c, int& newX, int& newY) { // Search for a character in the board
	for (int y = 0; y < MAX_Y; y++) {
		for (int x = 0; x < MAX_X; x++) {
			if (currentBoard[y][x] == c) {
				newX = x;
				newY = y;

				// Special behavior for '&'
				if (c == '&' && x + 1 < MAX_X) {
					newX = x + 1;
				}

				return true; // Character found
			}
		}
	}
	return false; // Character not found
}

