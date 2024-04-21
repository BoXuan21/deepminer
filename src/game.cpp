#include "Game.h"
#include <iostream>
#include <thread>

Game::Game() : world(), currentRobot(0), level(1), scoreThreshold(50) {
    robots.push_back(new Robot(world));
    robots[currentRobot]->resetPosition(world);  // Initialize position
}

Game::~Game() {
    for (auto robot : robots) {
        delete robot;
    } // löschen um speicher leaks zu vermeiden
    robots.clear();

     // Erstelle Threads für jeden Roboter
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(std::thread(&Robot::robotAction, std::ref(*robots[i]), std::ref(world)));
    }
}

void Game::run() {
    char command;
    bool gameRunning = true;
    while (gameRunning) {
        world.displayWorld(*robots[currentRobot]);
        robots[currentRobot]->displayScore();

        if (robots[currentRobot]->isAtLastLayer()) {
            std::cout << "Robot has reached the last layer. Game over!" << std::endl;
            break;  // End game if robot is at the last layer
        }

        checkLevelProgress();  // Check if the level needs to be advanced

        std::cout << "Enter command ('x' to mine): ";
        std::cin >> command;
        switch (command) {
            case 'x':
                robots[currentRobot]->mine(world);
                break;
            case 'q':
                gameRunning = false;
                break;
            default:
                std::cout << "Invalid command." << std::endl;
                break;
        }
    }
}


void Game::checkLevelProgress() {
    if (robots[currentRobot]->getScore() >= scoreThreshold) {
        advanceLevel();
    }
}

void Game::advanceLevel() {
    level++;
    std::cout << "Advancing to level " << level << "." << std::endl;

    switch (level) {
        case 2:
            scoreThreshold = 100;  // Set the new score threshold for level 2
            std::cout << "Welcome to Level 2! Reach 100 points to advance." << std::endl;
            break;
        case 3:
            scoreThreshold = 150;  // Set the new score threshold for level 3
            std::cout << "Welcome to Level 3! Reach 150 points to advance." << std::endl;
            break;
        default:
            std::cout << "You have reached the highest level. Congratulations!" << std::endl;
            gameRunning = false;  // Optionally end the game if it's the highest level
            return;
    }

    /*world = World();  // Reinitialize the world, refreshing all game fields
    for (auto& robot : robots) {
        robot->resetScore();  // Reset score for each robot
        robot->resetPosition(world);  // Reset position (sets z to top layer and randomizes x, y)
    } */
}
