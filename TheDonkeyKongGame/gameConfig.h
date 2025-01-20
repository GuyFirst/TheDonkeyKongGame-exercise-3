#pragma once
#include <string>
class gameConfig
{
public:
	static constexpr int GAME_WIDTH = 81;
	static constexpr int GAME_HEIGHT = 25;
	enum class eKeys { LEFT = 'a', UP = 'w', RIGHT = 'd', DOWN = 'x', STAY = 's', PATISH = 'p', ESC = 27, NONE };
	enum class Direction { POSITIVE = 1, NEGATIVE = -1, STAY = 0 };
	enum class Size { BARREL_MAX = 5, ZERO_SIZE = 0, START_LIVES = 3, BARRREL_COUNTER = 10 };
	enum class Sleep { GAME_LOOP_SLEEP = 110, SCREEN_SLEEP = 900, EXPLOSION_SLEEP = 16, TEXT_PRINTING_SLEEP = 30, WAITING_FOR_MENU_SLEEP = 150 };
	enum class Score { STARTING_SCORE = 10000, LIFE_LOSS = 500, SECONDS_PASSED = 100, GHOST_KILL = 500, BARREL_KILL = 500 };
	

	
};
void gotoxy(int, int);
void clrsrc();
void ShowConsoleCursor(bool showFlag);
void clearBuffer();
void printSlow(int delay, const std::string& text);

