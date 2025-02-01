#include <iostream>
#include "Game.h"
#include <conio.h> //for kbhit_ getch
#include <ctime>  // For time functions
#include <cstdlib>  // For rand() and srand()
#include <Windows.h>
#include "Barrel.h"
#include "Map.h"
#include "Mario.h"
#include "Point.h"
#include <chrono>
#include <vector>
#include <filesystem>
#include <algorithm>
#include "gameConfig.h"
#include "Ghost.h"
#include "UniqueGhost.h"
#include "Steps.h"
#include "Result.h"
#include "GameLoad.h"
#include "GameSave.h"
#include <typeinfo>
#include <memory>


void Game::run()
{
    std::vector<std::string> vec_to_fill;
    getAllBoardFileNames(vec_to_fill);
 
        int flag = 0;
        Point screenStart(0, 0);
        if (_isSilent) {
            std::cout << "running in silent mode, please wait";
            Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
        }
        while (true)                                        //
        {                                                   //
            gotoxy(screenStart.getX(), screenStart.getY()); // 
            Map menu;                                       // the flags indicates if the player wins, loses, or quiting the game.
            if (typeid(*this) == typeid(GameSave))
            {
                flag = menu.mainMenu(vec_to_fill);                         //  -1 for deciding to quit (before we entered the game)
                if (flag == -1)                                 //   1 if the player won
                    return;
                if (vec_to_fill.size() == 0)
                {
                    noScreensMessage();
                    return;
                }
                flag = startGame(vec_to_fill, flag - '1');      //  -1 if the player lost
                if (flag == 1)                                 
                    win();                                     
                else                                            
                    lose();                                                                
            }
            else
            {
                startGame(vec_to_fill, 0);
                clrsrc();
                return;
            }
       
        }
}

bool Game::getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
	bool areThereAnyScreen = false;
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        auto filename = entry.path().filename();
        auto filenameStr = filename.string();
        if (filenameStr.substr(0, 5) == "dkong" && filename.extension() == ".screen") {
			areThereAnyScreen = true;
            vec_to_fill.push_back(filenameStr);
        }
    }
    std::sort(vec_to_fill.begin(), vec_to_fill.end());
    return areThereAnyScreen;
}

void Game::handleErrors(int& flag)
{
    clrsrc();
    switch (flag) {
    case 1:
		printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "The provided file does not meet the game settings,\nas Mario does not appear in the file.\n");
        flag = 0;
        pressAnyKeyToMoveToNextStage();
        break;
    case 2:
        printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "The provided file does not meet the game settings,\nas Pauline dose not appear in the file and you can not win.\n");
        flag = 0;
        pressAnyKeyToMoveToNextStage();
        break;
    case 3:
        printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "The provided file does not meet the game settings,\nas Donkey does not appear in the file.\n");
        flag = 0;
        pressAnyKeyToMoveToNextStage();
        break;
    case 4:
        printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "The provided file does not meet the game settings,\nas the Legend must appear in the file.\n");
        flag = 0;
        pressAnyKeyToMoveToNextStage();
        break;
    case 5:
	case 6:
        printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "The provided file does not meet the game settings,\nas the file is not the appropriate size.\nPlease make sure the screen is 80X25 sized.\n");
        flag = 0;
        pressAnyKeyToMoveToNextStage();
        break;
    };
}

void Game::noScreensMessage() const
{
        clrsrc();
        gotoxy(0, 0);
        printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "No screens found in the current directory.\nPlease add screens to the directory and restart the game.\n");
		printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "Press any key to Exit.\n");
        while (true)
            if (_kbhit())
                return;
        return;
}

void Game::pressAnyKeyToMoveToNextStage() const
{
    printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "Press any key to move to the next stage.\n");
    Sleep((int)gameConfig::Sleep::SCREEN_SLEEP * 2);
    while (true)
        if (_kbhit())
            return;
}



         
int Game::startGame(std::vector<std::string> fileNames, int index) {
    bool endScreenResult = true;
    for (int i = index; i < fileNames.size(); i++) {
        ShowConsoleCursor(false);
        gotoxy(gameConfig::GAME_WIDTH / 3, gameConfig::GAME_HEIGHT / 2);
        // Initialize game board and objects
        Map gameBoard = initializeGameBoard(fileNames[i], this->_isSilent);
        if (!gameBoard.isMapValid()) continue;

        long random_seed;
        Steps steps;
        Results results;
        std::string filename = fileNames[i];
        
        // Making recording file names
        std::string filename_prefix = filename.substr(0, filename.find_last_of('.'));
        std::string stepsFilename = filename_prefix + ".steps";
        std::string resultsFilename = filename_prefix + ".result";
        
        if (checkMissingFiles(filename, stepsFilename, resultsFilename)) {
            continue;
       }

        Mario mario(&gameBoard, gameBoard.getMarioStartPos());
        std::vector<Barrel> barrels = initializeBarrels(gameBoard);
        std::vector<std::unique_ptr<Ghost>> ghosts = initializeGhosts(gameBoard);


        int score = (int)gameConfig::Score::STARTING_SCORE;
        int currLives = (int)gameConfig::Size::START_LIVES;
        if(!this->_isSilent)
             gameBoard.printLegend(currLives);
        bool isMarioLocked = false;
        bool patishPicked = false;
        bool isResultGood = true;
        auto lastToggleTime = std::chrono::steady_clock::now();
        std::vector<Point> togglePoints = defineFloorsToToggle(gameBoard);
        std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
        int elapsedSeconds = 0;
        clearBuffer();

        handleStartOfGameLoop(results, steps, resultsFilename, stepsFilename);

        // Setting random seed
        random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
        setRandomSeed(random_seed, steps);
        srand(random_seed);

        size_t iteration = 0;
        auto res = results.popResult();
        for (; true; iteration++) {


            char keyPressed = handleUserInput(steps, iteration);

            if (this->isReleventKeyPressed(keyPressed) && _isSave) {
                steps.addStep(iteration, keyPressed);  }

            if (keyPressed == (int)gameConfig::eKeys::ESC) {
                pauseGame(gameBoard, currLives);
                continue;
            }
            // Handle game logic
            if (handlePatishInteraction(mario, patishPicked, gameBoard)) continue;

            if (handleLifeLoss(currLives, mario, gameBoard, Barrel::barrelCurr, Barrel::barrelSpawnCounter, isMarioLocked, ghosts, barrels, score)) {
                if (_isLoad || _isSave)
                         handleDieResult(res, results,iteration, fileNames[i], isResultGood);   
                if (currLives == 0)
                    break;
            }


            if (mario.isNearPaulina())
            {
                if (_isLoad || _isSave)
                        handlePaulineResult(res, results, iteration, fileNames[i], isResultGood);
                break;
            }

            if (!isResultGood)
                break;

            if (res.second == Results::NO_RESULT) {
                reportResultError("Mario was suppose to win or lose but he was not.", fileNames[i], iteration);
                isResultGood = false;
                break;
            }

            


            if (res.first == iteration)
                res = results.popResult();

            // Handle barrel spawning
            handleBarrelSpawning(barrels, gameBoard);
            // handle patish
            patishDestroy(barrels, ghosts, mario, keyPressed, score, this->_isSilent);
            // Move barrels and ghosts
            moveBarrelsAndGhosts(barrels, ghosts, mario, this->_isLoad, this->_isSave, this->_isSilent);

            Sleep(this->_isSilent ? 0 : (this->_isLoad ? 10 : (int)gameConfig::Sleep::GAME_LOOP_SLEEP));
            

            // Toggle arrows every 4 seconds
            toggleArrowsEvery4Sec(gameBoard, togglePoints, lastToggleTime, this->_isSilent);

            //handle patish
            patishDestroy(barrels, ghosts, mario, keyPressed, score, this->_isSilent);

            // Handle Mario movement
            handleMarioMovement(mario, isMarioLocked, keyPressed, this->_isSilent);

            // Update the clock every second
            updateClock(startTime, elapsedSeconds, gameBoard, score);
            // Update score
            updateScore(gameBoard, score);
        }
        if(_isSave)
            handleEndOfGameLoop(results, steps, resultsFilename, stepsFilename);
        if (!currLives)
            return -1;
        if (i != fileNames.size() - 1) {
            moveToNextStage(i, isResultGood);
        }
        clearBuffer();
        endScreenResult = isResultGood;
        
    }
    clearBuffer();
    
    if (endScreenResult)
        reportResult("No issues where found on this screen, everything ran properly.");
    return 1;
}




void Game::updateClock(std::chrono::steady_clock::time_point& startTime, int& elapsedSeconds, Map& gameBoard, int& score) {
    // Get the current time
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

    // If a second has passed, update the clock
    if (duration > elapsedSeconds) {
        elapsedSeconds = duration;

        // Format the clock (example: "Time: 01:23")
        int minutes = elapsedSeconds / 60;
        int seconds = elapsedSeconds % 60;

		if (seconds % 5 == 0)
            score -= static_cast<int>(gameConfig::Score::SECONDS_PASSED);
        // Position where the clock will be printed (customize as needed)
        if (!this->_isSilent)
        {
            Point clockPosition = gameBoard.getLegendPosition();
            gotoxy(clockPosition.getX() + strlen("TIME PASSED:"), clockPosition.getY() + 1); // Adjust position for clock

            std::cout << (minutes < 10 ? "0" : "") << minutes << ":"
                << (seconds < 10 ? "0" : "") << seconds;
        }
    }
}

// Initialize game board
Map Game::initializeGameBoard(const std::string& fileName, bool isSilent) {
    Map gameBoard;
    int flag = gameBoard.load(fileName);
    handleErrors(flag);
    if (flag) {
        gameBoard.resetMap();
        if(!isSilent)
           gameBoard.printcurrentMap();
    }
	gameBoard.setValidation(flag);
    return gameBoard;
}

// Initialize barrels
std::vector<Barrel> Game::initializeBarrels(Map& gameBoard) {
    std::vector<Barrel> barrels;
    barrels.emplace_back(&gameBoard, gameBoard.getBarrelStartPoint());
    return barrels;
}





std::vector<std::unique_ptr<Ghost>> Game::initializeGhosts(Map& gameBoard) {
    std::vector<std::unique_ptr<Ghost>> ghosts;
    for (const ghostType& ghost : gameBoard.getGhostType()) {
        // Create Ghost or UniqueGhost based on 'me' value
        if (ghost.me == 'x') {
            ghosts.push_back(std::make_unique<Ghost>(&gameBoard, std::rand(), ghost.startPos, ghost.me));
        }
        else {
            ghosts.push_back(std::make_unique<UniqueGhost>(&gameBoard, std::rand(), ghost.startPos, ghost.me));
        }
    }

    return ghosts;
}

/*std::vector<Ghost*> Game::initializeGhosts(Map& gameBoard) {

    std::vector<Ghost*> ghosts;
    for (const ghostType& ghost : gameBoard.getGhostType()) {
        // Create Ghost or UniqueGhost based on 'me' value
        if (ghost.me == 'x') {
           
            ghosts.push_back(new Ghost(&gameBoard, std::rand(), ghost.startPos, ghost.me));
        }
        else {
          
            ghosts.push_back(new UniqueGhost(&gameBoard, std::rand(), ghost.startPos, ghost.me));
        }
    }

    return ghosts;
}*/

// Handle user input


// Pause the game
void Game::pauseGame(Map& gameBoard, const int currLives) {
    pause();
    gameBoard.printcurrentMap();
    gameBoard.printLegend(currLives);
}

// Handle Patish interaction
bool Game::handlePatishInteraction(Mario& mario, bool& patishPicked, Map& gameBoard) {
    if (mario.isNearPatish() && !patishPicked) {
        mario.isWithPatish = true;
        patishPicked = true;
        Point hammerPos = gameBoard.getPatishPosition();
        gameBoard.currentMap[hammerPos.getY()][hammerPos.getX()] = ' ';
        gameBoard.originalMap[hammerPos.getY()][hammerPos.getX()] = ' ';
        return true;
    }
    return false;
}

// Handle barrel spawning
void Game::handleBarrelSpawning(std::vector<Barrel>& barrels, Map& gameBoard) {
    Barrel::barrelSpawnCounter++;
    if (Barrel::barrelSpawnCounter == (int)gameConfig::Size::BARRREL_COUNTER && Barrel::barrelCurr < (int)gameConfig::Size::BARREL_MAX) {
        barrels.emplace_back(&gameBoard, gameBoard.getBarrelStartPoint());
        Barrel::resetBarrelSpawnCounter();
        Barrel::incrementBarrelCurr();
    }
}

// Move barrels and ghosts
void Game::moveBarrelsAndGhosts(std::vector<Barrel>& barrels, std::vector<std::unique_ptr<Ghost>>& ghosts, Mario& mario, bool isLoad, bool isSave, bool isSilent) {
    moveBarrels(barrels, mario, isLoad, isSave, isSilent);
    moveGhosts(ghosts, isLoad, isSave, isSilent);
}

// Toggle arrows on map
void Game::toggleArrowsEvery4Sec(Map& gameBoard, std::vector<Point>& togglePoints, std::chrono::steady_clock::time_point& lastToggleTime, bool isSilent) {
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - lastToggleTime).count() >= 4) {
        for (const Point& p : togglePoints) {
            toggleArrow(gameBoard, p);
        }
        lastToggleTime = now;
    }
}

// Handle Mario movement
void Game::handleMarioMovement(Mario& mario, bool& isMarioLocked, char keyPressed, bool isSilent) {
    if (isMarioLocked) {
        handleMarioLocked(keyPressed, mario, isMarioLocked);
    }
    else {
        mario.move((gameConfig::eKeys)keyPressed, isSilent);
        isMarioLocked = isMarioInLongAction(mario);
    }

    if (isMarioInShortAction(mario)) {
        isMarioLocked = false;
    }
}

// Update score display
void Game::updateScore(Map& gameBoard, int score) {
    Point LegendPosition = gameBoard.getLegendPosition();
    gotoxy(LegendPosition.getX() + 7, LegendPosition.getY() + 2);
    if(!(this->_isSilent))
      std::cout << score;
}

// Move to the next stage
void Game::moveToNextStage(int stageIndex, bool isResultGood) {
    clrsrc();
    gotoxy(gameConfig::GAME_WIDTH / 3, gameConfig::GAME_HEIGHT / 2);
    printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "Stage ");
    std::cout << stageIndex + 1;
    printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), " completed!\n");
    Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
    gotoxy(gameConfig::GAME_WIDTH / 3, (gameConfig::GAME_HEIGHT / 2) + 1);
    printSlow(static_cast<int>(gameConfig::Sleep::TEXT_PRINTING_SLEEP), "Moving on to the next stage...\n");
    Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
}






//    OUR impement for the function CHAT-GPT suggested
void Game::toggleArrow(Map& gameBoard, const Point& point) {
    
    char currentChar = gameBoard.currentMap[point.getY()][point.getX()];
    if (currentChar == '>') {
        gameBoard.currentMap[point.getY()][point.getX()] = '<';
        gotoxy(point.getX(), point.getY());
        if(!_isSilent)
           std::cout << '<';
    }
    else  if (currentChar == '<') {
        gameBoard.currentMap[point.getY()][point.getX()] = '>';
        gotoxy(point.getX(), point.getY());
        if (!_isSilent)
           std::cout << '>';
    }
}


void Game::drawMario(Mario& mario) {
    char curr = mario.getMapChar();
    if(!_isSilent)
    mario.draw(curr == 'H' ? '#' : '@');
}


bool Game::handleLifeLoss(int& currLives, Mario& mario, Map& gameBoard, int& barrelCurr, int& barrelSpawnCounter, bool& isMarioLocked, std::vector<std::unique_ptr<Ghost>>& ghosts, std::vector<Barrel>& barrels, int& score) {
    if (currLives == mario.lives)
        return false;
    currLives--;
    if (currLives == 0)
        return true;
    score -= (int)gameConfig::Score::LIFE_LOSS;
    loseALife();
    gameBoard.resetMap();
    if(!_isSilent)
        gameBoard.printcurrentMap();
    
    if (!_isSilent)
        gameBoard.printLegend(currLives);
    mario.resetMario();
    resetGhosts(ghosts);
    barrelCurr = 0;
    barrelSpawnCounter = 0;
    isMarioLocked = false;
    barrels.clear();
    clearBuffer();

    return true;
}

void Game::spawnBarrel(std::vector<Barrel>& barrels, int& barrelCurr, Map& gameBoard) {
    barrels.push_back(Barrel(&gameBoard, gameBoard.getBarrelStartPoint()));  // Add to vector instead of using array index
    barrelCurr++;
}

void Game::moveBarrels(std::vector<Barrel>& barrels, Mario& mario, bool isLoad, bool isSave, bool isSilent) {
    for (int i = 0; i < Barrel::barrelCurr; i++) {
        if (i < barrels.size()) {
            char curr = barrels[i].getMapChar();
            barrels[i].draw('O', isLoad, isSave, isSilent);
            barrels[i].move(barrels, &mario, isLoad, isSave, isSilent);
        }
    }
}

void Game::handleMarioLocked(char keyPressed, Mario& mario, bool& isMarioLocked) {
    if (keyPressed == (char)gameConfig::eKeys::STAY &&
        (mario.state == Mario::State::CLIMBING_UP || mario.state == Mario::State::CLIMBING_DOWN)) {
        mario.state = Mario::State::STANDING;
        isMarioLocked = false;
    }
    else {
        mario.move(gameConfig::eKeys::NONE, this->_isSilent);
    }
}

bool Game::isMarioInLongAction(Mario& mario) const {
    return mario.state == Mario::State::JUMPING ||
        mario.state == Mario::State::CLIMBING_UP ||
        mario.state == Mario::State::CLIMBING_DOWN;
}

bool Game::isMarioInShortAction(Mario& mario) const {
    return mario.state == Mario::State::STANDING ||
        mario.state == Mario::State::WALKING;
}


void Game::pause()
{
    clrsrc();
    gotoxy(20, 10);
    std::cout << "Game paused, press ESC again to continue.";
    gotoxy(20, 12);
    std::cout << "But it is not mandatory to present such a message.";


    char keyPressed = 0;
    while (true) {
        if (_kbhit()) {
            keyPressed = _getch();
            if (keyPressed == (char)gameConfig::eKeys::ESC) {
                // When ESC is pressed, unpause the game
                clrsrc();
                gotoxy(0, 0);
                return;
            }
        }
    }
}





void Game::loseALife() const
{

    clrsrc();
    gotoxy(40, 10);
    std::cout << "oh no u lose a life oh no";
    Sleep((int)gameConfig::Sleep::SCREEN_SLEEP);
}




void Game::moveGhosts(std::vector<std::unique_ptr<Ghost>>& ghosts, bool isLoad, bool isSave, bool isSilent) {
    for (auto& ghost : ghosts) {
        
        (*ghost).move(ghosts, isLoad,  isSave, isSilent);
    }
}

void Game::resetGhosts(std::vector<std::unique_ptr<Ghost>>& ghosts) {
    for (auto& ghost : ghosts) {
        (*ghost).reset();
    }
}

std::vector<Point> Game::defineFloorsToToggle(Map& map)
{
    std::vector<Point> res;
    for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
        for (int j = 0; j < gameConfig::GAME_WIDTH; j++)
        {
            if ((map.originalMap[i][j] == '<' && map.originalMap[i][j - 1] == '=' && map.originalMap[i][j + 1] == '=') ||
                (map.originalMap[i][j] == '>' && map.originalMap[i][j - 1] == '=' && map.originalMap[i][j + 1] == '='))
            {
                Point p(j, i);
                res.push_back(p);
            }

        }
    return res;
}



void Game::patishDestroy(std::vector<Barrel>& barrels, std::vector<std::unique_ptr<Ghost>>& ghosts, Mario& mario, char key, int& score, bool isSilent) {
    if (key == (char)gameConfig::eKeys::PATISH && mario.isWithPatish) {
        Point marioPos1 = mario.getPoint();
        Point marioPos2 = mario.getPoint();
        marioPos1.setX(marioPos1.getX() + 1);
        marioPos2.setX(marioPos2.getX() - 1);

        // Handle ghosts
        for (auto it = ghosts.begin(); it != ghosts.end(); ) {
            if ((*it)->getPoint() == mario.getPoint() || (*it)->getPoint() == marioPos1 || (*it)->getPoint() == marioPos2) {
                (*it)->draw(' ', isSilent, isSilent, isSilent);
                it = ghosts.erase(it);
                score += (int)gameConfig::Score::GHOST_KILL;
            }
            else {
                ++it;
            }
        }

        // Handle barrels
        for (auto it = barrels.begin(); it != barrels.end(); ) {
            Barrel& barrel = *it;

            if (barrel.getPoint() == mario.getPoint() || barrel.getPoint() == marioPos1 || barrel.getPoint() == marioPos2) {
                barrel.draw(' ', isSilent, isSilent, isSilent);
                it = barrels.erase(it);
                Barrel::decrementBarrelCurr();
                Barrel::resetBarrelSpawnCounter();
                score += (int)gameConfig::Score::BARREL_KILL;
            }
            else {
                ++it;
            }
        }
    }
}



void Game::updateClock(const std::chrono::seconds& elapsedTime)
{
    // Calculate minutes and seconds from total elapsed seconds
    int secondsElapsed = elapsedTime.count();
    int minutes = secondsElapsed / 60;
    int seconds = secondsElapsed % 60;

    // Print the clock with zero padding (e.g., 01:05 for 1 minute and 5 seconds)
    std::cout << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
}


