#pragma once
#include <iostream>
#include "gameConfig.h"
#include <Windows.h>
#include "Point.h"
#include <string>
#include <vector>

struct ghostType {
    char me;
    Point startPos;
    ghostType(char ghostChar, Point start) : me(ghostChar), startPos(start) {}
};

class Map
{

private: 
    Point marioStartPos;
    Point barrelStartPoint;
    Point legendPosition;
    Point patishPosition;
    std::vector<ghostType> ghosts;
    bool isValid;
public:
	Map() : isValid(false) {}
    static constexpr int GAME_WIDTH = 82;
    static constexpr int GAME_HEIGHT = 25;
	Point getPatishPosition() const { return patishPosition; }
    Point getMarioStartPos() const { return marioStartPos; }
    Point getBarrelStartPoint() const { return barrelStartPoint; }
    Point getLegendPosition() const { return legendPosition; }
    const std::vector<ghostType>& getGhostType() const { return ghosts; }
	void m_playMarioTheme() const;
	void m_playDonkeyStartTheme() const;
	void m_playHowHighCanYouGetTheme() const;
	void setValidation(bool valid) { isValid = valid; }
    char originalMap[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {};

    const char loginScreen[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {

       "                                 ================                              ", 
       "                                    Welcome to                                 ", 
       "                                 ================                              ", 
       "       ________  ________  ________   ___  __    _______       ___    ___      ", 
       "      |\\   ___ \\|\\   __  \\|\\   ___  \\|\\  \\|\\  \\ |\\  ___ \\     |\\  \\  /  /|      ", 
       "      \\ \\  \\_|\\ \\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\/  /|\\ \\   __/|    \\ \\  \\/  / /", 
       "       \\ \\  \\ \\\\ \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\   ___  \\ \\  \\_|/__   \\ \\    / / ", 
       "        \\ \\  \\_\\\\ \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\   \\/  /  /", 
       "         \\ \\_______\\ \\_______\\ \\__\\\\ \\__\\ \\__\\\\ \\__\\ \\_______\\__/  / / ", 
       "          \\|_______|\\|_______|\\|__| \\|__|\\|__| \\|__|\\|_______|\\___/ /       ", 
       "                                                              \|___|/  ", 
       "                           by Guy First and Ori Perelman                       ",  
       "                      |\\  \\|\\  \\ |\\   __  \\|\\   ___  \\|\\   ____\\", 
       "                      \\ \\  \\/  /|\\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\___| ", 
       "                       \\ \\   ___  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\  ___ ", 
       "                        \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ ", 
       "                         \\ \\__\\\\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\  ", 
       "                          \\|__| \\|__|\\|_______|\\|__| \\|__|\\|_______|",
       "                      Please press the following keys to:                      ",
       "          1. start Game                                                        ", 
       "          2. Start Game From a Specific Screen            ", 
       "          8. Show Instructions                            ",
       "          9. Exit                                         ", 
       "          3. Play Mario Theme     4. Play 'Original Donkey Kong' Start Theme    ", 

    };

    const char instructionsScreen[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {
        "                                                                               ", // 1
        "                                                                               ", // 2
        "                                                                               ", // 3
        "                                                                               ", // 4
        "                                                                               ", // 5
        "                              ======================                           ", // 6
        "                                 Game Instructions                             ", // 7
        "                              ======================                           ", // 8
        "                                                                               ", // 9
        "                     1. Use A (left), W (up), D (right), X (down),             ", // 10
        "                            S (stand) keys to move Mario.                      ", // 11
        "                                                                               ", // 12
        "                                2. Avoid barrels.                              ", // 13
        "                                                                               ", // 14
        "                         3. Reach to the princess to win!                      ", // 15
        "                                                                               ", // 16
        "                                   4. Have fun!                                ", // 17
        "                                                                               ", // 18
        "                     Press the ESC key to return to the main menu...           ", // 19
        "                                                                               ", // 20
        "                                                                               ", // 21
        "                                                                               ", // 22
        "                                                                               ", // 23
        "                                                                               ", // 24
        "===============================================================================", // 25

    };
    char currentMap[Map::GAME_HEIGHT][Map::GAME_WIDTH] = {};
   
    void resetMap() {
        for (int i = 0; i < Map::GAME_HEIGHT; ++i)
            memcpy(currentMap[i], originalMap[i], Map::GAME_WIDTH);
    }

	bool isMapValid() const { return isValid; }
    void printcurrentMap() const;    
    char chooseScreens(std::vector<std::string> vec_to_fill) const;
    void printLegend(int remainingLives) const;
    int mainMenu(std::vector<std::string> vec_to_fill) const;
    void showMenu() const;
    void showInstructions() const;
    int exitGame() const{ std::cout << "Exiting the game. Goodbye!" << std::endl; return -1; }
    void win() const;
    void lose() const;
    int load(const std::string& filename);

   
};

