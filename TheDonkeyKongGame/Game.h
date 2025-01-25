#pragma once
#include <vector>
#include "Ghost.h"
#include "Mario.h"
#include "Map.h"
#include "Barrel.h"
#include <iomanip>      
#include <thread> 
#include <string>
#include "Steps.h"
#include "Result.h"

class Game
{
	bool _isLoad;
	bool _isSave;
	bool _isSilent;

public:
	Game(bool isLoad, bool isSave, bool isSilent) : _isLoad(isLoad), _isSave(isSave), _isSilent(isSilent) {}

	virtual void handleDieResult( Results& results, const int& iteration, std::string fileName) = 0;
	virtual void handlePaulineResult(Results& results, const int& iteration, std::string fileName) = 0;
    void run();
	virtual char handleUserInput(Steps& steps, int iteration) = 0;
	virtual void handleStartOfGameLoop(Results& results, Steps& steps, std::string resultsFileName, std::string stepsFileName) = 0;
	virtual void handleEndOfGameLoop(Results& results, Steps& steps, std::string resultsFileName, std::string stepsFileName) = 0;
    int startGame(std::vector<std::string>, int index);
	virtual bool isReleventKeyPressed(const char& key) = 0;
	void pause();
	virtual void loseALife() const;
	virtual void setRandomSeed(long& random_seed, Steps& steps) = 0;
	virtual void win() const = 0;
	virtual void lose() const = 0;
	void drawMario(Mario& mario);
	bool handleLifeLoss(int& currLives, Mario& mario, Map& gameBoard, static int& barrelCurr, static int& barrelCounter, bool& isMarioLocked, std::vector<Ghost*>& ghosts, std::vector<Barrel>& barrels, int& score);
	void spawnBarrel(std::vector<Barrel>& barrels, int& barrelCurr, Map& gameBoard);
	void moveBarrels(std::vector<Barrel>& barrels, Mario& mario, bool isLoad, bool isSave, bool isSilent);
	void handleMarioLocked(char keyPressed, Mario& mario, bool& isMarioLocked);
	bool isMarioInLongAction(Mario& mario) const;
	bool isMarioInShortAction(Mario& mario) const;
	void toggleArrow(Map& gameBoard, const Point& point);
	void moveGhosts(std::vector<Ghost*>& ghosts, bool isLoad, bool isSave, bool isSilent);
	void resetGhosts(std::vector<Ghost*>& ghosts);
	std::vector<Point> defineFloorsToToggle(Map& map);
	void updateClock(std::chrono::steady_clock::time_point& startTime, int& elapsedSeconds, Map& gameBoard, int& score);
	void patishDestroy(std::vector<Barrel>& barrels, std::vector<Ghost*>& ghosts, Mario& mario, char key, int& score, bool isSilent);
	void updateClock(const std::chrono::seconds& elapsedTime);
	bool getAllBoardFileNames(std::vector<std::string>& vec_to_fill);
	void handleErrors(int& flag);
	void noScreensMessage() const;
	void pressAnyKeyToMoveToNextStage() const;
	Map initializeGameBoard(const std::string& fileName, bool isSilent);
	std::vector<Barrel> initializeBarrels(Map& gameBoard);
	std::vector<Ghost*>  initializeGhosts(Map& gameBoard);
	void pauseGame(Map& gameBoard,const int currLives);
	bool handlePatishInteraction(Mario& mario, bool& patishPicked, Map& gameBoard);
	void handleBarrelSpawning(std::vector<Barrel>& barrels, Map& gameBoard);
	void moveBarrelsAndGhosts(std::vector<Barrel>& barrels, std::vector<Ghost*>& ghosts, Mario& mario, bool isLoad, bool isSave, bool isSilent);
	void toggleArrowsEvery4Sec(Map& gameBoard, std::vector<Point>& togglePoints, std::chrono::steady_clock::time_point& lastToggleTime, bool isSilent);
	void handleMarioMovement(Mario& mario, bool& isMarioLocked, char keyPressed, bool isSilent);
	void updateScore(Map& gameBoard, int score);
	virtual void moveToNextStage(int stageIndex);
	virtual void finish() const = 0;
};

