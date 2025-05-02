#include "Map.h"
#include "gameConfig.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "Point.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include "Note.h"


void Map::m_playMarioTheme() const
{
	playMarioTheme();
}

void Map::m_playDonkeyStartTheme() const
{
	playDonkeyStartTheme();
}

void Map::m_playHowHighCanYouGetTheme() const
{
	playHowHighCanYouGetTheme();
}

void Map::printcurrentMap() const
{
    gotoxy(0, 0);
    for (int i = 0; i < Map::GAME_HEIGHT; ++i) {
        std::cout << currentMap[i];
        if (i != Map::GAME_HEIGHT - 1)
            Sleep(20);
    }
}

char Map::chooseScreens(std::vector<std::string> vec_to_fill) const
{
    clrsrc();
    gotoxy(0, 0);
    std::cout << "choose screen to start with:\n";
	std::cout << "---------------------------\n";
	std::cout << "Please Select The number that display near the screen to start from it.\nAny other nubmer would not work.\n";
    int num = 1;
    for (auto& it : vec_to_fill)
    {
        std::cout << num << "." << it << "\n";
        num++;
    }
    char key;
    while (true)
        if (_kbhit()){
             key = _getch();
		 if ((key >= '1') && (key < '0' + num))
                    return key;
                 else
		    continue;
}
       
}

void Map::printLegend( int remainingLives) const
{
	Point  LegendPosition = getLegendPosition();
    gotoxy(LegendPosition.getX(), LegendPosition.getY());
    std::cout << "REMAINING LIVES: ";
   // gotoxy(LegendPosition.getX() + 4, LegendPosition.getY() + 1);
    for (int i = 0; i < remainingLives; i++)
        std::cout << "*";
    gotoxy(LegendPosition.getX(), LegendPosition.getY()+1);
    std::cout << "TIME PASSED: ";
    gotoxy(LegendPosition.getX(), LegendPosition.getY() + 2);
    std::cout << "SCORE: ";


}
void Map::showMenu() const{
    for (int i = 0; i < Map::GAME_HEIGHT; ++i) {
        std::cout << this->loginScreen[i];
        if (i != Map::GAME_HEIGHT - 1)
            std::cout << "\n";
        Sleep(20);
    }
}
void Map::showInstructions() const
{
    gotoxy(0, 0);
    for (int i = 0; i < Map::GAME_HEIGHT; ++i) {
        std::cout << this->instructionsScreen[i];
        if (i != Map::GAME_HEIGHT - 1)
            std::cout << "\n";
        Sleep(20);
    }
    char key = 0;
    while (true)
    {
        if (_kbhit())
            key = _getch();

        if (key != (char)gameConfig::eKeys::ESC)
            continue;

        break;
    }
    return;
}
int Map::mainMenu(std::vector<std::string> vec_to_fill) const
{
    int flag = 0;
    showMenu();
    while (true)
    {
        
        char keyPressed = '*';
        if (_kbhit())
            keyPressed = _getch();

        if (keyPressed == '9')
            return flag = exitGame();

        if (keyPressed == '8')
        {
            clrsrc();
            showInstructions();
            clrsrc();
            showMenu();
            Sleep(500);
        }
        if (keyPressed == '2')
        {
			if (vec_to_fill.size() == 0)
                return '1';
            char key = chooseScreens(vec_to_fill);
            clrsrc();
            return key;
        }
		if (keyPressed == '1')
			return keyPressed;

        if (keyPressed == '3') {
            playMarioTheme();
            showMenu();
        }
        if (keyPressed == '4') {
			playDonkeyStartTheme();
            showMenu();
        }
    }
}




void Map::win() const
{
    const char WinScreen[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH] = {
        "                                                                               ", // 1
        "                                                                               ", // 2
        "                                                                               ", // 3
        "                                                                               ", // 4
        "                                                                               ", // 5
        "                                                                               ", // 6
        "                            ~ ~ ~ YOU ~ ~ ~ WON ~ ~ ~                          ", // 7
        "                                                                               ", // 8
        "                                                                               ", // 9
        "                                                                               ", // 10
        "                                                                               ", // 11
        "                                                                               ", // 12
        "                                                                               ", // 13
        "                                                                               ", // 14
        "                                                                               ", // 15
        "                                       :)                                      ", // 16
        "                                                                               ", // 17
        "                                                                               ", // 18
        "                                                                               ", // 19
        "                                                                               ", // 20
        "                                                                               ", // 21
        "                                                                               ", // 22
        "                                                                               ", // 23
        "                                                                               ", // 24
        "                                                                               ", // 25
    };
    const char message[] = "Returning to the main menu";
    gotoxy(0, 0);

    for (int col = 0; col < 25; col++)
    {
        std::cout << WinScreen[col] << '\n';
    }
    int i = 0;
    Sleep(1000);
    gotoxy(28, 22);
    while (message[i] != '\0')
    {
        std::cout << message[i];
        Sleep((int)gameConfig::Sleep::TEXT_PRINTING_SLEEP);
        i++;
    }
    Sleep(2000);
    return;
}

void Map::lose() const
{
    const char LoseScreen[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH] = {
       "                                                                               ", // 1
       "                                                                               ", // 2
       "                                                                               ", // 3
       "                                                                               ", // 4
       "                                                                               ", // 5
       "                                                                               ", // 6
       "                            ~ ~ ~ YOU ~ ~ ~ LOST ~ ~ ~                         ", // 7
       "                                                                               ", // 8
       "                                                                               ", // 9
       "                                                                               ", // 10
       "                                                                               ", // 11
       "                                                                               ", // 12
       "                                      OH NO                                    ", // 13
       "                                      LOSER                                    ", // 14
       "                                                                               ", // 15
       "                                       :(                                      ", // 16
       "                                                                               ", // 17
       "                                                                               ", // 18
       "                                                                               ", // 19
       "                                                                               ", // 20
       "                                                                               ", // 21
       "                                                                               ", // 22
       "                                                                               ", // 23
       "                                                                               ", // 24
       "                                                                               ", // 25
    };
    const char message[] = "Returning to the main menu...";
    gotoxy(0, 0);

    for (int col = 0; col < 25; col++)
    {
        std::cout << LoseScreen[col] << '\n';
    }
    int i = 0;
    Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
    gotoxy(28, 22);
    while (message[i] != '\0')
    {
        std::cout << message[i];
        Sleep(100);
        i++;
    }
    for (int i = 0; i < 3; i++) {
        gotoxy(28 + strlen(message) - 3, 22);
        std::cout << "   ";
        gotoxy(28 + strlen(message) - 3, 22);
        for (int i = 0; i < 3; i++) {
            std::cout << '.';
            Sleep((int)gameConfig::Sleep::WAITING_FOR_MENU_SLEEP);
        }
        Sleep((int)gameConfig::Sleep::WAITING_FOR_MENU_SLEEP);
    }
    return;
}





int Map::load(const std::string& filename) {
    std::ifstream screen_file(filename);
    if (!screen_file.is_open()) {
        throw std::runtime_error("Failed to open the file: " + filename);
    }

    int curr_row = 0;
    int curr_col = 0;
    char c;

    bool foundMario = false;
    bool foundPauline = false;
    bool foundDonkey = false;
    bool foundLegend = false;
	bool isQCurrRow = false;
    std::vector<ghostType> ghosts;
    Point position;
   
    while (!screen_file.get(c).eof()) {
        if (c == '\n') {
            if (curr_col < Map::GAME_WIDTH && !isQCurrRow) 
                   for (; curr_col < Map::GAME_WIDTH-2; ++curr_col) 
                       originalMap[curr_row][curr_col] = ' ';   // Fill the remaining space with ' ' (spaces)
            
            else if (curr_col > Map::GAME_WIDTH) {
				//not good return with a proper message and ignore the screen
            }
            //originalMap[curr_row][++curr_col] = '\0';
          
            ++curr_row;
            curr_col = 0;
            continue;
        }
       
        if (curr_col < Map::GAME_WIDTH && curr_row < Map::GAME_HEIGHT) {
            switch (c) {
            case '@':  // Mario
                if (foundMario) { originalMap[curr_row][curr_col++] = ' '; break; } //from the second mario (if there is), ignore him

                foundMario = true;
                marioStartPos = { curr_col, curr_row };
                originalMap[curr_row][curr_col++] = ' ';  // Replace with space
                break;

            case '$':  // Pauline
                if (foundPauline) { originalMap[curr_row][curr_col++] = ' '; break; }//from the second Pauline (if there is), ignore her
               
                foundPauline = true;
                originalMap[curr_row][curr_col++] = '$';
                break;

            case '&':  // Donkey Kong
				if (foundDonkey) { originalMap[curr_row][curr_col++] = ' '; break; }//from the second Donkey Kong (if there is), ignore him
                foundDonkey = true;
                barrelStartPoint = { curr_col, curr_row + 1 };
                originalMap[curr_row][curr_col++] = '&';
                break;

            case 'x':  // Ghost
                position.setX(curr_col);
                position.setY(curr_row);
                ghosts.emplace_back('x', position);
                originalMap[curr_row][curr_col++] = ' ';  // Replace with space
                break;
            case 'X':  // Ghost
                position.setX(curr_col);
                position.setY(curr_row);
                ghosts.emplace_back('X', position);
                originalMap[curr_row][curr_col++] = ' ';  // Replace with space
                break;

            case 'L':  // Legend
                if (foundLegend) {
                    originalMap[curr_row][curr_col++] = ' '; break;  }//from the second Legend (if there is), ignore it 
                foundLegend = true;
                legendPosition = { curr_col, curr_row };
                originalMap[curr_row][curr_col++] = ' ';  // Replace with space
                break;

            case 'p':  // Patish
                patishPosition = { curr_col, curr_row };
                originalMap[curr_row][curr_col++] = 'p';  
                break;

            case 'Q':  // border
                originalMap[curr_row][curr_col++] = 'Q';
				isQCurrRow = true;
                break;

            default:
                originalMap[curr_row][curr_col++] = c;  // Regular character
                break;
            }
        }
	    if (curr_col >= Map::GAME_WIDTH) {return 5;}
    }
	if (curr_row < Map::GAME_HEIGHT-1) { return 6; }
    for (; curr_col < Map::GAME_WIDTH - 2; ++curr_col)
        originalMap[curr_row][curr_col] = ' ';   // Fill the remaining space with ' ' (spaces)
	originalMap[curr_row][curr_col] = '\0';  // Null-terminate the last row

	for (int i = 0; i < ghosts.size(); i++) // delete ghosts that are not on the floor
    {
        if (originalMap[ghosts[i].startPos.getY() + 1][ghosts[i].startPos.getX()] != '=' && 
            originalMap[ghosts[i].startPos.getY() + 1][ghosts[i].startPos.getX()] != '<' && 
            originalMap[ghosts[i].startPos.getY() + 1][ghosts[i].startPos.getX()] != '>')
             ghosts.erase(ghosts.begin() + i--);
    }
    if (!foundMario) { return 1; } // not good, return int, a proper message, and ignore the screen 
    if (!foundPauline) { return 2; } //not good, return int, a proper message, and ignore the screen 
    if (!foundDonkey) { return 3; } // not good, return int, a proper message, and ignore the screen 
    if (!foundLegend) { return 4; } // not good, return int, a proper message, and ignore the screen 

    
    this->ghosts = ghosts;  // Update ghost positions in the class
    return -1;
}

