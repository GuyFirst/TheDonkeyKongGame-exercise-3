#include "Game.h"
#include "GameLoad.h"
#include "GameSave.h"

int main(int argc, char** argv) {
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	bool isSave = argc > 1 && std::string(argv[1]) == "-save";
	
	Game* game;
	if (isLoad)
	{
		game = new GameLoad();  
		game->run(isLoad,isSave,isSilent);
	}
	if (isSave)
	{
		game = new GameSave();  
		game->run(isLoad, isSave, isSilent);
	}
	

	

	return 0;
}




