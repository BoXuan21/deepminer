#ifndef GAME_H
#define GAME_H

#include "Robot.h"
#include "World.h"

class Game {
private:
    World world;
    std::vector<Robot*> robots;
    int currentRobot;
    int level;
    int scoreThreshold;

public:
    Game();

    ~Game();

    void run();

    void checkLevelProgress();

    void advanceLevel();
};

#endif // GAME_H
