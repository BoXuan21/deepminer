#ifndef GAME_H
#define GAME_H

#include "World.h"
#include "Robot.h"
#include <vector>

class Game {
private:
    World world;
    std::vector<Robot*> robots;
    int currentRobot;
    int level;                // Track the current level
    int scoreThreshold;       // Score required to move to the next level
    bool gameRunning;         // Control the running of the game loop

public:
    Game();
    ~Game();
    void run();
    void checkLevelProgress();
    void advanceLevel();
    void displayFinalScore();

};

#endif
