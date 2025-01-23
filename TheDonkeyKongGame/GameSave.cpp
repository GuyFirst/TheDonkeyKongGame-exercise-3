#include "GameSave.h"
#include "Steps.h"
#include "Result.h"


void GameSave::run()
{
	std::vector<std::string> vec_to_fill;
	getAllBoardFileNames(vec_to_fill);

	int flag = startGame(vec_to_fill, flag - '1');

	return;
}

int Game::startGame(std::vector<std::string> fileNames, int index) {
    for (int i = index; i < fileNames.size(); i++) {
        ShowConsoleCursor(false);
        gotoxy(gameConfig::GAME_WIDTH / 3, gameConfig::GAME_HEIGHT / 2);

        // Initialize game board and objects
        Map gameBoard = initializeGameBoard(fileNames[i]);
        if (!gameBoard.isMapValid()) continue;

        long random_seed;
        Steps steps;
        Results results;
        std::string filename = fileNames[i];

        // Making recording file names
        std::string filename_prefix = filename.substr(0, filename.find_last_of('.'));
        std::string stepsFilename = filename_prefix + ".steps";
        std::string resultsFilename = filename_prefix + ".result";

        // Setting random seed
        random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
        steps.setRandomSeed(random_seed);
        srand(random_seed);

        Mario mario(&gameBoard, gameBoard.getMarioStartPos());
        std::vector<Barrel> barrels = initializeBarrels(gameBoard);
        std::vector<Ghost*> ghosts = initializeGhosts(gameBoard);


        int score = (int)gameConfig::Score::STARTING_SCORE;
        int currLives = (int)gameConfig::Size::START_LIVES;
        gameBoard.printLegend(currLives);
        bool isMarioLocked = false;
        bool patishPicked = false;
        auto lastToggleTime = std::chrono::steady_clock::now();
        std::vector<Point> togglePoints = defineFloorsToToggle(gameBoard);
        std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
        int elapsedSeconds = 0;
        clearBuffer();

        size_t iteration = 0;
        for (;true; iteration++) {
            size_t nextSignificantIteration = results.getNextSignificantIteration(); 0; // May result in bugs, be aware
           
            char keyPressed = handleUserInput();
            if (keyPressed == (int)gameConfig::eKeys::ESC) {
                pauseGame(gameBoard, currLives);
                continue;
            }

            if (keyPressed == '`') {
                barrels.clear();
                hack();
                break;
            }

            // Handle game logic
            if (handlePatishInteraction(mario, patishPicked, gameBoard)) continue;
            if (handleLifeLoss(currLives, mario, gameBoard, Barrel::barrelCurr, Barrel::barrelSpawnCounter, isMarioLocked, ghosts, barrels, score)) {
                return -1;
            }

            if (mario.isNearPaulina()) break;

            // Handle barrel spawning
            handleBarrelSpawning(barrels, gameBoard);
            // handle patish
            patishDestroy(barrels, ghosts, mario, keyPressed, score);
            // Move barrels and ghosts
            moveBarrelsAndGhosts(barrels, ghosts, mario);

            Sleep((int)gameConfig::Sleep::GAME_LOOP_SLEEP);

            // Toggle arrows every 4 seconds
            toggleArrowsEvery4Sec(gameBoard, togglePoints, lastToggleTime);

            //handle patish
            patishDestroy(barrels, ghosts, mario, keyPressed, score);

            // Handle Mario movement
            handleMarioMovement(mario, isMarioLocked, keyPressed);

            // Update the clock every second
            updateClock(startTime, elapsedSeconds, gameBoard, score);
            // Update score
            updateScore(gameBoard, score);
        }

        if (i != fileNames.size() - 1) {
            moveToNextStage(i);
        }
        clearBuffer();
    }
    clearBuffer();
    return 1;
}