#pragma once
#include "Game.h"

class GameLoad : public Game
{
	bool isSilent = false;
public:
	GameLoad() {}
	void setIsSilent(bool isSilentMode) {isSilent = isSilentMode;}
	char handleUserInput(Steps& steps, int iteration);
	bool isReleventKeyPressed(const char& key) override { return false; }
	 void handleDieResult(Results& results, const int& iteration, std::string fileName);
	 void handlePaulineResult(Results& results, const int& iteration, std::string fileName);
};

