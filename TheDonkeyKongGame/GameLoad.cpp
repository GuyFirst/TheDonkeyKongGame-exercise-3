#include "GameLoad.h"
#include "Steps.h"
#include "Result.h"

void GameLoad::run()
{
	
	std::vector<std::string> vec_to_fill;
	getAllBoardFileNames(vec_to_fill);

	int flag = startGame(vec_to_fill, flag - '1'); 

	return;
}

int GameLoad::startGame(std::vector<std::string> fileNames, int index)
{
    bool unmatching_result_found = false;

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

            // Loading file steps and results
            steps = Steps::loadSteps(stepsFilename);
            random_seed = steps.getRandomSeed();
            results = Results::loadResults(resultsFilename);
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
                size_t nextSignificantIteration = results.getNextSignificantIteration();
                

                if (results.isFinishedBy(iteration)) {
                    reportResultError("Results file reached finish while game hadn't!", filename, iteration);
                    unmatching_result_found = true;
                    break;
                }

                // Loading step from file
                char keyPressed = (int)gameConfig::eKeys::NONE;
                if (steps.isNextStepOnIteration(iteration)) {
                    keyPressed = steps.popStep(iteration);
                }
                 
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

                // That part is simillar to kirsh's if(!goodMove) part
                if (handleLifeLoss(currLives, mario, gameBoard, Barrel::barrelCurr, Barrel::barrelSpawnCounter, isMarioLocked, ghosts, barrels, score)) {
                    // check if the result is correct
                    auto result = results.popResult();
                    if (result != std::pair{ iteration, Results::DIED }) {
                        reportResultError("Results file doesn't match death event!", filename, iteration);
                        unmatching_result_found = true;
                    }

                    // May cause bugs, im not sure. 
                    // Because we already get the next significant iteration in the begining of the loop, 
                    // I just copied from kirsh's code 
                    nextSignificantIteration = results.getNextSignificantIteration();  
                    
                    
                    if (currLives == 0) return -1;
                }

                else {
                    // we didn't die, so we check if the result is correct
                    if (iteration == nextSignificantIteration) {
                        reportResultError("Results file has a hit bomb event that didn't happen!", filename, iteration);
                        unmatching_result_found = true;
                        break;
                    }
                }

                // Stopped working here (stopped copying from kirsh's code

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

