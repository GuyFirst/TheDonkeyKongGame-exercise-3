#include "Game.h"
#include "GameLoad.h"
#include "GameSave.h"
#include <iostream>
#include "memory"

int main(int argc, char** argv) {
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	bool isSave = argc > 1 && std::string(argv[1]) == "-save";
    std::unique_ptr<Game> game;

    if (isLoad) {
        game = std::make_unique<GameLoad>(isLoad, isSave, isSilent);
    }
    else {
        game = std::make_unique<GameSave>(isLoad, isSave, isSilent);
    }

    game->run();

    return 0;
}


