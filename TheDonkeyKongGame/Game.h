#pragma once
#include <vector>
#include "Ghost.h"
#include "Mario.h"
#include "Map.h"
#include "Barrel.h"
#include <iomanip>      
#include <thread> 
#include <string>

class Game
{
public:
	virtual void run();
	virtual char handleUserInput();
	int startGame(std::vector<std::string>, int index);
	void pause();
	void loseALife() const;
	void win() const;
	void lose() const;
	void drawMario(Mario& mario);
	bool handleLifeLoss(int& currLives, Mario& mario, Map& gameBoard, static int& barrelCurr, static int& barrelCounter, bool& isMarioLocked, std::vector<Ghost*>& ghosts, std::vector<Barrel>& barrels, int& score);
	void spawnBarrel(std::vector<Barrel>& barrels, int& barrelCurr, Map& gameBoard);
	void moveBarrels(std::vector<Barrel>& barrels, Mario& mario);
	void handleMarioLocked(char keyPressed, Mario& mario, bool& isMarioLocked);
	bool isMarioInLongAction(Mario& mario) const;
	bool isMarioInShortAction(Mario& mario) const;
	void toggleArrow(Map& gameBoard, const Point& point);
	void moveGhosts(std::vector<Ghost*>& ghosts);
	void resetGhosts(std::vector<Ghost*>& ghosts);
	std::vector<Point> defineFloorsToToggle(Map& map);
	void updateClock(std::chrono::steady_clock::time_point& startTime, int& elapsedSeconds, Map& gameBoard, int& score);
	void patishDestroy(std::vector<Barrel>& barrels, std::vector<Ghost*>& ghosts, Mario& mario, char key, int& score);
	void updateClock(const std::chrono::seconds& elapsedTime);
	bool getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	void handleErrors(int& flag);
	void noScreensMessage() const;
	void pressAnyKeyToMoveToNextStage() const;
	void hack() const;
	Map initializeGameBoard(const std::string& fileName);
	std::vector<Barrel> initializeBarrels(Map& gameBoard);
	std::vector<Ghost*>  initializeGhosts(Map& gameBoard);
	void pauseGame(Map& gameBoard,const int currLives);
	bool handlePatishInteraction(Mario& mario, bool& patishPicked, Map& gameBoard);
	void handleBarrelSpawning(std::vector<Barrel>& barrels, Map& gameBoard);
	void moveBarrelsAndGhosts(std::vector<Barrel>& barrels, std::vector<Ghost*>& ghosts, Mario& mario);
	void toggleArrowsEvery4Sec(Map& gameBoard, std::vector<Point>& togglePoints, std::chrono::steady_clock::time_point& lastToggleTime);
	void handleMarioMovement(Mario& mario, bool& isMarioLocked, char keyPressed);
	void updateScore(Map& gameBoard, int score);
	void moveToNextStage(int stageIndex);
	void reportResultError(const std::string& message, const std::string& filename, size_t iteration);
};

