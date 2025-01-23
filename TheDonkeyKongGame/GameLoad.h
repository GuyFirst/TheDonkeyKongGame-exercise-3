#pragma once
#include "Game.h"
class GameLoad : public Game
{
	bool isSilent = false;
public:
	virtual void run();
	void setIsSilent(bool isSilentMode) {isSilent = isSilentMode;}
	int startGame(std::vector<std::string> fileNames, int index);
};

