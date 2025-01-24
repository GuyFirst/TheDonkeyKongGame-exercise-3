#include "GameSave.h"
#include "Steps.h"
#include "Result.h"
#include <conio.h> //for kbhit_ getch



char GameSave::handleUserInput(Steps& steps, int iteration) {
    char keyPressed = (int)gameConfig::eKeys::NONE;
    if (_kbhit()) {
        keyPressed = std::tolower(_getch());
    }
    return keyPressed;
}

void GameSave::handleDieResult(Results& results, const int& iteration, std::string fileName)
{
    results.addResult(iteration, Results::DIED);
}

void GameSave::handlePaulineResult(Results& results, const int& iteration, std::string fileName)
{
    results.addResult(iteration, Results::REACH_PAULIN);
}


