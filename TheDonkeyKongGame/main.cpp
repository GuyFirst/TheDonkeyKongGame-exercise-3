#include "Game.h"

int main(int argc, char** argv) {
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	bool isSave = argc > 1 && std::string(argv[1]) == "-save";
	if (isLoad)
		GameLoad game;
	else if (isSave)
		GameSave game;
	else
		Game game;
	game.run();
	return 0;
}




