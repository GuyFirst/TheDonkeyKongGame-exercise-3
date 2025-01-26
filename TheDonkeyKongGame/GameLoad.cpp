#include "GameLoad.h"
#include "Steps.h"
#include "Result.h"
#include "gameConfig.h"

char GameLoad::handleUserInput(Steps& steps, int iteration)
{
	char keyPressed = (int)gameConfig::eKeys::NONE;
	if(steps.isNextStepOnIteration(iteration))
		return steps.popStep();
	return keyPressed;
}

void GameLoad::handleDieResult(Results& results, const int& iteration, std::string fileName, bool& isResultGood)
{
	if (results.popResult() != std::pair{ iteration, Results::DIED })
	{
		reportResultError("Mario is dead altough he was not suppose to be", fileName, iteration);
		isResultGood == false;
    }
	
}


void GameLoad::handlePaulineResult(Results& results, const int& iteration, std::string fileName, bool& isResultGood)
{
	if (results.popResult() != std::pair{ iteration, Results::REACH_PAULIN }) {
		reportResultError("Mario is near Pauline altough he was not suppose to be there", fileName, iteration);
		isResultGood = false;
	}
}







