#pragma once
#include "Game.h"

class GameLoad : public Game
{
	bool isSilent = false;
public:
	GameLoad(bool isLoad, bool isSave, bool isSilent) : Game(isLoad, isSave, isSilent) {}
	void setIsSilent(bool isSilentMode) {isSilent = isSilentMode;}
	char handleUserInput(Steps& steps, int iteration);
	bool isReleventKeyPressed(const char& key) override { return false; }
	void handleDieResult(Results& results, const int& iteration, std::string fileName);
	void handlePaulineResult(Results& results, const int& iteration, std::string fileName);
	void moveToNextStage(int stageIndex) override { clrsrc();}
	void loseALife() const override {clrsrc();}
	virtual void setRandomSeed(long& random_seed, Steps& steps) override { random_seed = steps.getRandomSeed(); }
	virtual void handleEndOfGameLoop(Results & results, Steps & steps, std::string resultsFileName, std::string stepsFileName) override {}
	void handleStartOfGameLoop(Results& results, Steps& steps, std::string resultsFileName, std::string stepsFileName) override {
		results.loadResults(resultsFileName);
		steps.loadSteps(stepsFileName);
	}
	void finish() const override{
		clrsrc();
		gotoxy(0, 0);
		std::cout << "no issues where found, the game ran as it should have been.";
	}
	virtual void win() const override {};
	virtual void lose() const override {};

	
};

