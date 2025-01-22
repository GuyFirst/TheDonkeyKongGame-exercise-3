#include "GameSave.h"
void GameSave::run()
{
    std::vector<std::string> vec_to_fill;
    getAllBoardFileNames(vec_to_fill);

    int flag = 0;
    Point screenStart(0, 0);
    while (true)                                        //
    {                                                   //
        gotoxy(screenStart.getX(), screenStart.getY()); // 
        Map menu;                                       // the flags indicates if the player wins, loses, or quiting the game.
        flag = menu.mainMenu(vec_to_fill);                         //  -1 for deciding to quit (before we entered the game)
        if (flag == -1)                                 //   1 if the player won
            return;
        if (vec_to_fill.size() == 0)
        {
            noScreensMessage();
            return;
        }
        flag = startGame(vec_to_fill, flag - '1');      //  -1 if the player lost
        //
        if (flag == 1)                                  //
            win();                                      //
        else                                            //
            lose();
    }
    return;
}