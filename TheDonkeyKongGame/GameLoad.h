#pragma once
#include "Game.h"
#include "gameConfig.h"

class GameLoad : public Game
{
	bool isSilent = false;
public:
	GameLoad(bool isLoad, bool isSave, bool isSilent) : Game(isLoad, isSave, isSilent) {}
	void setIsSilent(bool isSilentMode) {isSilent = isSilentMode;}
	char handleUserInput(Steps& steps, int iteration);
	bool isReleventKeyPressed(const char& key) override { return false; }
	void handleDieResult(std::pair<size_t, Results::ResultValue>& res, Results& results, const int& iteration, std::string fileName, bool& isResultGood);
	void handlePaulineResult(std::pair<size_t, Results::ResultValue>& res, Results& results, const int& iteration, std::string fileName, bool& isResultGood);
	void moveToNextStage(int stageIndex, bool isResultGood) override {
		clrsrc();
		if (isResultGood)
			reportResult("No issues where found on this screen, everything ran properly.");
	}
	void loseALife() const override {clrsrc();}
	virtual void setRandomSeed(long& random_seed, Steps& steps) override { random_seed = steps.getRandomSeed(); }
	virtual void handleEndOfGameLoop(Results & results, Steps & steps, std::string resultsFileName, std::string stepsFileName) override {}
	void handleStartOfGameLoop(Results& results, Steps& steps, std::string resultsFileName, std::string stepsFileName) override {
		results.loadResults(resultsFileName);
		steps.loadSteps(stepsFileName);
	}
	virtual void win() const override {};
	virtual void lose() const override {};
	virtual bool checkMissingFiles(const std::string& filename, const std::string& stepsFilename, const std::string& resultsFilename) override;


	
};

