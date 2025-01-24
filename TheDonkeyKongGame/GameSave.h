#pragma once
#include "Game.h"


class GameSave : public Game
{
public:
	GameSave() {}
	bool isReleventKeyPressed(const char& key) override {
		return (key == 'a' || key == 's' || key == 'd' || key == 'w' || key == 's' || key == 'x' || key == 'p');
	}
	char handleUserInput(Steps& steps, int iteration) override;
	bool  isReallyDied(const Results& results, const int& iteration) const { return true; }
	bool  isReallyReachedPauline(const Results& results, const int& iteration) const { return true; }
	 void handleDieResult(Results& results, const int& iteration, std::string fileName);
	 void handlePaulineResult(Results& results, const int& iteration, std::string fileName);
	 virtual void setRandomSeed(long& random_seed, Steps& steps) override { steps.setRandomSeed(random_seed); }
	 virtual void handleEndOfGameLoop(Results& results, Steps& steps, std::string resultsFileName, std::string stepsFileName) override {
		 results.saveResults(resultsFileName);
		 steps.saveSteps(stepsFileName);
	 }
	 void handleStartOfGameLoop(Results& results, Steps& steps, std::string resultsFileName, std::string stepsFileName) override {}
};

