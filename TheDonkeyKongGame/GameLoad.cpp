#include "GameLoad.h"

void GameLoad::run()
{
	std::vector<std::string> vec_to_fill;
	getAllBoardFileNames(vec_to_fill);

	int flag = startGame(vec_to_fill, flag - '1'); 

	return;
}
