#include "game_config.h"

void game_config::start() { 
    bool proceed;
    proceed = new_game();
    while (proceed) {
        proceed = new_game();
    }
}

bool game_config::new_game() {
    Board b;
    char last_key = 's';                                                     //Makes sure Marios initial state will be still
    int lives = 3, num_of_screen = 0,score = 0;
    bool won = false, start = true, invalid_file = false;
    std::vector<std::string> fileNames;

    make_files_v(fileNames);                                                //create vector of screen names, also set the first screen
    
    start = display_menu(b, num_of_screen, fileNames.size());               //present the starting screen and decide if proceed or not 
	b.changeScreen(fileNames[num_of_screen]);							    //Change the screen to the selected screen

    if (start == false) { return false; }

    while (true) {
		start_game(b, last_key, lives, won, invalid_file, num_of_screen,score);  //Starts the game
        if (lives == 0) {
            set_screen(b, LOST);
            while (true) {                                                      //Mario lost
                if (_kbhit()) {                                                 //presents the losing screen 
                    _getch();                                                   //clears the buffer 
                    b.clearScreen();                                            //clears it and return to menu when a key is hit
                    return true;
                }
            }
        }
        if (invalid_file) {                                                     //Just invlid file not the last screen
            set_screen(b, INVALID);
            while (true) {
                if (_kbhit()) {
                    _getch();
                    b.clearScreen();
                    break;
                }
            }
        }
        if (num_of_screen == (fileNames.size() - 1)) {
            set_screen(b, WON);
			gotoxy(25, 15);
			cout << "Your score is: " << score << endl;
            while (true) {                                                  //presents the winning screen
                if (_kbhit()) {                                             //Clears it and return to menu when a key is hit
                    _getch();                                               //clears the buffer 
                    b.clearScreen();
                    return true;
                }
            }
        }
        if (won || invalid_file) {
            invalid_file = false;
            won = false;
            num_of_screen++;
            b.changeScreen(fileNames[num_of_screen]);
        }
        //Continues the game untill its WON or LOST(no more lifes )
    }
}
//The main loop of the game
void game_config::start_game(Board& b, char& last_key, int& lives, bool &won, bool &invalid_file, int num_of_screen,int &score) {  
    //Mario
    Mario m;
    int jumps = 0 ;
    bool fall = false, on_ladder = false, hammer_found=false;
    //enemy 
    barrels barrel[10];
    int barrel_timer = 0, barrel_index = 1;
    std::vector<ghost> ghosts;
	std::vector<ghost_2> ghosts2;
    //Game
    int Legend_x=2, Legend_y=2;
    char key_pressed = 's';
    
    b.load(GAME);                           
    if (!set_board(b, m, barrel, ghosts,ghosts2, Legend_x, Legend_y)) {
        invalid_file = true;
        return;
    }
    b.clearScreen();
    b.print();
    lives_counter(lives, Legend_x, Legend_y);
	screen_counter(num_of_screen);
	
	
    //Loads the game screen, sets the objects, if incorrect file terminates and return to main loop. also sets the lives counter and screen counter

    while (true) {   //loop of the game 
        if (!hammer_found) {
            hammer_found = m.hammerTime();
        }
        hammer_Legend(hammer_found, Legend_x, Legend_y);
		score_counter(score, Legend_x, Legend_y);
		handel_input(m, jumps, fall, on_ladder, key_pressed, hammer_found, barrel, ghosts,ghosts2,score); //Handels input from the user
        if (barrel_handling(b, barrel, barrel_timer, barrel_index, m) || fallDamage(m) || ghosts_handeling(b ,ghosts,ghosts2, m)) {
            lives--;
            won = false;                            //resets won to false
            break;
        }
        //Handeling barrel movement and reseting the screen if mario hit or in range of explosion
        //Checking if mario falled more than 5
        mario_redraw(m, jumps, fall, on_ladder, key_pressed);                                  //Cycle mario
        if (m.mario_won()) {                                                                  //Mario won
            won = true;
            break;
        }
       

        Sleep(80);
    }
}
//The actual game after the screen handeling


 
bool game_config::set_board(Board& b, Mario& m, barrels barr[], std::vector<ghost>& ghosts, std::vector<ghost_2>& ghosts2, int &Legend_x, int &Legend_y) {
    int new_mario_x, new_mario_y;
    int new_barrel_x, new_barrel_y;
    int mario_won_x, mario_won_y;
	
    bool cond1, cond2, cond3, cond4;

    cond1 = b.searchChar('@', new_mario_x, new_mario_y);
    cond2 = b.searchChar('&', new_barrel_x, new_barrel_y);
    cond3 = b.searchChar('$', mario_won_x, mario_won_y);
    cond4 = b.searchChar('L', Legend_x, Legend_y);
    //Searching for the cond in order to see that the files are valid 

    m.setXsetY(new_mario_x, new_mario_y);
    for (int i = 0; i <= 9; i++) { barr[i].set_default(new_barrel_x, new_barrel_y); }
    m.set_win(mario_won_x, mario_won_y);
    //Setting mario pauline and barrel initial location

    for (int y = 0; y < MAX_Y; y++) {          
        for (int x = 0; x < MAX_X; x++) {
            if (b.getChar(x, y) == 'x') {
                ghosts.push_back(ghost(x , y));
                b.setChar(x, y, ' ');
            }
        }
    }

    
    for (int y = 0; y < MAX_Y; y++) {          
        for (int x = 0; x < MAX_X; x++) {
            if (b.getChar(x, y) == 'X') {
                ghosts2.push_back(ghost_2(x , y));
                b.setChar(x, y, ' ');
            }
        }
    }

    //Resetting board
    for (int i = 0; i < ghosts.size(); i++) {
        ghosts[i].pBoard = &b;
    }
    for (int i = 0; i < ghosts2.size(); i++) {
        ghosts2[i].pBoard = &b;
    }

    m.pBoard = &b;
    m.draw();
    barr[0].pBoard = &b;
    barr[0].set_default_position();
    barr[0].draw();
    barr[0].set_active(true);
    //Present objects on the board 
    return (cond1 && cond2) && (cond3 && cond4);
    //returning true only if screen is valid 
}

void game_config::make_files_v(std::vector<std::string>& fileNames) {
    std::ifstream file1("dkong_1.screen.txt");
    if (file1) {
        int i = 1;
        std::string fileName = "dkong_" + std::to_string(i) + ".screen.txt";

        while (file1) {
            fileNames.push_back(fileName);
            i++;
            file1.close();
            fileName = "dkong_" + std::to_string(i) + ".screen.txt";
            file1.open(fileName); // Reopen the file here
        }
        file1.close(); // Close the file after the loop

    }
}
 
bool game_config::display_menu(Board& b,int& num_of_screen,int size_of_files) {
    char key_pressed;
    b.load(MENU);
    b.print();
    ShowConsoleCursor(false);
    while (true) {
        if (_kbhit()) {
            key_pressed = _getch();
            if (key_pressed == GAME) {
                return true;
                break;
            }
            else if (key_pressed == INSTRUCTIONS) {
                set_screen(b, INSTRUCTIONS);
            }
            else if (key_pressed == MENU) {
                set_screen(b, MENU);
            }
            else if (key_pressed == EXIT) {
                return false;                                                // Exit the program
            }
            else if (key_pressed == SELECTOR) {
                int numFile;
				set_screen(b, SELECTOR);
                gotoxy(39, 6);
                cout << size_of_files;
                // Call the function to get the user's selection
                num_of_screen = get_screen_selection(size_of_files);
				return true;
            }
        }
    }
}
//Display the start screen
 
int game_config::get_screen_selection(int size_of_files) {
    std::string input = ""; // To store the user's input

    while (true) {
        gotoxy(33, 12);         // Position for entering input
        std::cout << std::string(20, ' '); // Clear the input area
        gotoxy(33, 12);         // Reset cursor to the input area

        input.clear(); // Reset the input string
        while (true) {
            if (_kbhit()) {
                char key_pressed = _getch();

                // Handle ENTER key to confirm input
                if (key_pressed == ENTER) {
                    if (!input.empty()) { // Ensure input is not empty
                        int numFile = std::stoi(input); // Convert input to integer
                        if (numFile > 0 && numFile <= size_of_files) {
                            return numFile - 1; // Return the valid screen number
                        }
                        else {
                            gotoxy(33, 14); // Error message location
                            std::cout << "Invalid selection. Try again.     ";
                            break; // Exit the inner loop to retry input
                        }
                    }
                    else {
                        gotoxy(33, 14);
                        std::cout << "Please enter a valid number.       ";
                        break; // Exit the inner loop to retry input
                    }
                }
                // Handle BACKSPACE for input correction
                else if (key_pressed == '\b' && !input.empty()) { // Backspace key
                    input.pop_back(); // Remove last character
                    gotoxy(33, 12);   // Reset cursor position
                    std::cout << std::string(20, ' '); // Clear line
                    gotoxy(33, 12);
                    std::cout << input; // Redisplay corrected input
                }
                // Append valid digits to the input
                else if (isdigit(key_pressed)) {
                    input += key_pressed; // Append character to input
                    std::cout << key_pressed; // Display the character
                }
            }
        }
    }
}
//Get the screen selection from the user
void game_config::screen_counter(int& num_of_screen) {
	gotoxy(75, 2);
	std::cout << "# " << num_of_screen +1 << std::endl;
}
 
void game_config::score_counter(int const score, int const Legend_x, int const Legend_y) {
    gotoxy(Legend_x, Legend_y+1);
    cout << "Score: " << score;
}
//Display the score of the player on the screen

void game_config::hammer_Legend(bool hammer_found, int const Legend_x, int const Legend_y) {
    gotoxy(Legend_x, Legend_y + 2);
	if (hammer_found) {
		std::cout << "Hammer: Found     ";
	}
	else
		std::cout << "Hammer: Not Found";
} 
//Display the hammer status

void game_config::lives_counter(int& lives, int const Legend_x, int const Legend_y) {
    gotoxy(Legend_x, Legend_y);
    std::cout << "num of lives: ";
    for (int i = 0; i < lives; ++i) {
        std::cout << '*' << " ";
    }
    std::cout << std::endl;
}
//Display num of lifes 

void game_config::set_screen(Board& b, board_type t) {
    b.clearScreen();
    b.load(t);
    b.print();
}
//Sets the screen of the game

void game_config::handel_input(Mario& m, int& jumps, bool& fall, bool& on_ladder, char& Key_pressed,bool hammer_found, barrels barr[], std::vector<ghost>& ghosts, std::vector<ghost_2>& ghosts2, int& score) {
    if (_kbhit() && (jumps == 0) && fall == false) {
        Key_pressed = _getch();  // Use the parameter directly
        game_pause(Key_pressed); // Check for pause 

        if (m.retun_char() == 'H') { // Check to enter ladder mode
            if (Key_pressed == 'w' || Key_pressed == 'W') {
                on_ladder = true;
                m.setDirX(0);
            }
        }
        else {
            on_ladder = false; // Exit ladder mode
        }

        if (on_ladder) { // Handle movement on ladder
            if (Key_pressed == 'w' || Key_pressed == 'W')
                m.setDirY(-1);
            if (Key_pressed == 'x' || Key_pressed == 'X')
                m.setDirY(1);
        }
        else {
            m.keyPressed(Key_pressed); // Handle Mario's regular movement
        }

        if ((Key_pressed == 'w' || Key_pressed == 'W') && !m.isMarioFalling() && !on_ladder) {
            m.up(jumps); // Handle jump
        }
		handleHammerAction(hammer_found, Key_pressed, m, barr, ghosts,ghosts2,score); //Handels the hammer action   
    }
}
//Handels input from the user

void game_config::handleHammerAction(bool hammer_found, char Key_pressed,Mario& m, barrels barr[], std::vector<ghost>& ghosts, std::vector<ghost_2>& ghosts2, int& score) {
    if (hammer_found) {
        if (std::tolower(Key_pressed) == 'p') {
            if (m.getDirx() == 1) {
                for (int i = 0; i < 10; i++) {
                    if (((barr[i].getX() == m.getX() + 2) || (barr[i].getX() == m.getX() + 1)) && barr[i].getY() == m.getY()) {
                        if (barr[i].get_active()) {
                            barr[i].set_active(false);
                            barr[i].erase();
                            score++;
                        }
                    }
                }
                for (int i = 0; i < ghosts.size(); i++) {
                    if (((ghosts[i].getX() == m.getX() + 2) || (ghosts[i].getX() == m.getX() + 1)) && ghosts[i].getY() == m.getY()) {
                        ghosts[i].erase();
                        ghosts.erase(ghosts.begin() + i);
                        score++;
                    }
                }
                for (int i = 0; i < ghosts2.size(); i++) {
                    if (((ghosts2[i].getX() == m.getX() + 2) || (ghosts2[i].getX() == m.getX() + 1)) && ghosts2[i].getY() == m.getY()) {
                        ghosts2[i].erase();
                        ghosts2.erase(ghosts2.begin() + i);
                        score++;
                    }
                }
            }
            else if (m.getDirx() == -1) {
                for (int i = 0; i < 10; i++) {
                    if (((barr[i].getX() == m.getX() - 2) || (barr[i].getX() == m.getX() - 1)) && barr[i].getY() == m.getY()) {
                        if (barr[i].get_active()) {
                            barr[i].set_active(false);
                            barr[i].erase();
                            score++;
                        }
                    }
                }
                for (int i = 0; i < ghosts.size(); i++) {
                    if (((ghosts[i].getX() == m.getX() - 2) || (ghosts[i].getX() == m.getX() - 1)) && ghosts[i].getY() == m.getY()) {
                        ghosts[i].erase();
                        ghosts.erase(ghosts.begin() + i);
                        score++;
                    }
                }
                for (int i = 0; i < ghosts2.size(); i++) {
                    if (((ghosts2[i].getX() == m.getX() - 2) || (ghosts2[i].getX() == m.getX() - 1)) && ghosts2[i].getY() == m.getY()) {
                        ghosts2[i].erase();
                        ghosts2.erase(ghosts2.begin() + i);
                        score++;
                    }
                }
            }
            else if (m.getDirx() == 0) {
                for (int i = 0; i < 10; i++) {
                        if ((((barr[i].getX() == m.getX() - 2) || (barr[i].getX() == m.getX() - 1)) || ((barr[i].getX() == m.getX() + 2) || (barr[i].getX() == m.getX() + 1))) && barr[i].getY() == m.getY()) {
                            if (barr[i].get_active()) {
                            barr[i].set_active(false);
                            barr[i].erase();
                            score++;
                            }
                        }
                }
                for (int i = 0; i < ghosts.size(); i++) {
                    if ((((ghosts[i].getX() == m.getX() - 2) || (ghosts[i].getX() == m.getX() - 1)) || ((ghosts[i].getX() == m.getX() + 2) || (ghosts[i].getX() == m.getX() + 1))) && ghosts[i].getY() == m.getY()) {
                        ghosts[i].erase();
                        ghosts.erase(ghosts.begin() + i);
                        score++;
                    }
                }
                for (int i = 0; i < ghosts2.size(); i++) {
                    if ((((ghosts2[i].getX() == m.getX() - 2) || (ghosts2[i].getX() == m.getX() - 1)) || ((ghosts2[i].getX() == m.getX() + 2) || (ghosts2[i].getX() == m.getX() + 1))) && ghosts2[i].getY() == m.getY()) {
                        ghosts2[i].erase();
                        ghosts2.erase(ghosts2.begin() + i);
                        score++;
                    }
                }
            }
        }
    }
} //Handels the hammer action

void game_config::mario_redraw(Mario& m, int& jumps, bool& fall, bool& on_ladder, char& Key_pressed) {
    if (on_ladder) {  // Mario on ladder, 2 irregular occasions
        if ((m.return_char_upper() == '=' || m.return_char_upper() == '>' || m.return_char_upper() == '<') &&
            (Key_pressed == 'w' || Key_pressed == 'W')) {
            m.setDirY(-2);
            redraw(m);
            on_ladder = false;
            m.keyPressed('s');
        }
        else if ((m.return_char_lower() == '=' || m.return_char_lower() == '>' || m.return_char_lower() == '<') &&
            (Key_pressed == 'x' || Key_pressed == 'X')) {
            on_ladder = false;
        }
        else {
            redraw(m);
        }
    }
    else {
        if (m.return_char_2lower() == 'H' && (Key_pressed == 'x' || Key_pressed == 'X')) {
            m.setDirY(2);
            redraw(m);
            on_ladder = true;
            m.keyPressed('x');
        }
        else {
            checkFalls(m, jumps, fall);  // Important to check jump status before redrawing
            redraw(m);
            checkJumps(m, jumps);
        }
    }
}
//Handels marios redraw with all irregular positions

void game_config::redraw(Mario& m) {
    m.erase();
    m.move();
    m.draw();
}       
//Cycles marios location on the scrren with the direction on his movement

bool game_config::barrel_handling(Board& b, barrels barrel[], int& barrel_timer, int& barrel_index, Mario& m) {

    if (barrel_timer == 50) {
        barrel_timer = 0;
        barrel[barrel_index].set_default_position();
        barrel[barrel_index].set_active(true);
        barrel[barrel_index].pBoard = &b;
        barrel[barrel_index].draw();
        barrel_index++;
        if (barrel_index == 10) { barrel_index = 0; }
        //Reset barrel default settings
    }
    barrel_timer++;

    for (int i = 0; i < 10; i++) {
        if (barrel[i].get_active()) {
            if (m.getX() == barrel[i].getX() && m.getY() == barrel[i].getY()) {         //Checks if mario hit by barrel
                return true;  
            }
            if (barrel[i].cycle_barrel()) {
                if (mario_explosion(barrel[i], m))
                    return true;
            }
            //cycles the barrel
            //checks if mario hit by explosion
            if (m.getX() == barrel[i].getX() && m.getY() == barrel[i].getY()) {         //Check if mario hit by barrel
                return true;
            }
        }
    }
    return false;
}
//Handeling barrel movement
//return true if mario hit by barrel/explosion or false if not

bool game_config::ghosts_handeling(Board& b, std::vector<ghost>& ghosts, std::vector<ghost_2>& ghosts2, Mario& m) {
    for (int i = 0; i < ghosts.size(); i++) {
        if (m.getX() == ghosts[i].getX() && m.getY() == ghosts[i].getY()) {         //Checks if mario hit by ghost
            return true;
        }
        ghosts[i].cycle_ghost();
        if (m.getX() == ghosts[i].getX() && m.getY() == ghosts[i].getY()) {         //Checks if mario hit by ghost
            return true;
        }
    }
    for (int i = 0; i < ghosts2.size(); i++) {
        if (m.getX() == ghosts2[i].getX() && m.getY() == ghosts2[i].getY()) {         //Checks if mario hit by ghost
            return true;
        }
        ghosts2[i].cycle_ghost();
        if (m.getX() == ghosts2[i].getX() && m.getY() == ghosts2[i].getY()) {         //Checks if mario hit by ghost
            return true;
        }
    }
    
    return false;
}

bool game_config::mario_explosion(barrels& b, Mario& m) {
    int barrel_x, barrel_y;
    int mario_x, mario_y;

    barrel_x = b.getX();
    barrel_y = b.getY();
    mario_x = m.getX();
    mario_y = m.getY();

    if (mario_x >= barrel_x - 2 && mario_x <= barrel_x + 3 && mario_y >= barrel_y - 2 && mario_y <= barrel_y + 2)
        return true;

    return false;
}
//The func checks if mario hit by explosion

void game_config::game_pause(char key_pressed) {
    if (key_pressed == ESC) {
        //Game paused 
        while (true) {
            key_pressed = _getch();
            if (key_pressed == ESC)
                break;
        }
    }
}
//This func pauses the game if needed

void game_config::checkJumps(Mario&m ,int& jumps) {
    if (jumps == 2) {
        jumps = 0;
        m.setDirY(0);
    }
    if (jumps == 1) {
        jumps++;
    }
}
void game_config::checkFalls(Mario& m, int& jumps, bool& fall){
    if (m.isMarioFalling() && jumps == 0) {
        fall = true;
        m.setDirY(1);
        m.AdvanceFallCounter();              //Advance fall counter
    }
    if (!m.isMarioFalling() && fall == true) {
        m.setDirY(0);
        fall = false;
    }
}
//Handels jumping

bool game_config::fallDamage(Mario& m) {
    if (m.return_char_lower() == '=' ||
        m.return_char_lower() == '<' ||
        m.return_char_lower() == '>') {
        if (m.return_fallCounter() >= 5) {
            return true;
        }
        m.NullifyFallCounter();                 //Nulify the falling counter
    }
    return false;
}
//The func checks wether mario fell more than 5 and nulifies the falling counter

