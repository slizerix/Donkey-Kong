
#include "utils.h"

void gotoxy(int x, int y) {
    std::cout.flush(); // Ensure the output buffer is flushed.
    COORD coord;       // Create a COORD structure.
    coord.X = x;       // Set the X coordinate.
    coord.Y = y;       // Set the Y coordinate.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor.
}
//This func sets the cursor on certain point on the screen

void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // Set the cursor visibility.
    SetConsoleCursorInfo(out, &cursorInfo);
}
//This func removes the cursor visability