#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono> // Chrono library for time measurement
#include "RobotController.h"

// Constructor: Initialize the game
Game::Game() : currentRobot(0), level(1), scoreThreshold(50) {
    // Create and initialize 5 robots
    for (int i = 0; i < 5; ++i) {
        robots.push_back(new Robot(world));
        robots[i]->resetPosition(world);
    }
}

// Destructor: Clean up memory used by robots
Game::~Game() {
    for (auto robot : robots) {
        delete robot; // Delete each robot
    }
    robots.clear(); // Clear the vector of robots
}

// Main game loop
void Game::run() {
    std::cout << "Game starting" << "\n";
    char command;
    bool gameRunning = true;

    // Record start time for the entire program
    auto programStartTime = std::chrono::high_resolution_clock::now();

    while (gameRunning) {
        // Display current state of the world and robots
        world.displayWorld(*robots[currentRobot]);
        robots[currentRobot]->displayScore();
        system("cls"); // Clear the console screen

        std::cout << "Cores loading....." << "\n";

        // Create threads for robot actions
        std::vector<std::thread> threads;
        for (int i = 0; i < 5; ++i) {
            // Each thread controls a single robot's action
            threads.emplace_back(&RobotController::mineWithRobot, robots[i], &world);
        }

        // Record start time for thread execution
        auto threadStartTime = std::chrono::high_resolution_clock::now();

        // Join all threads to wait for them to finish
        for (auto& thread : threads) {
            thread.join();
        }

        // Record end time for thread execution
        auto threadEndTime = std::chrono::high_resolution_clock::now();

        // Calculate duration for thread execution
        auto threadDuration = std::chrono::duration_cast<std::chrono::milliseconds>(threadEndTime - threadStartTime);

        std::cout << "Time taken for all threads: " << threadDuration.count() << " milliseconds" << std::endl;

        // Display final scores for all robots
        for (int i = 0; i < 5; ++i) {
            std::cout << "Robot " << i + 1 << " Final Score: " << robots[i]->getScore() << std::endl;
        }

        /*if (robots[currentRobot]->isAtLastLayer()) {
            std::cout << "Robot has reached the last layer. Game over!" << std::endl;
            break;  // End game if robot is at the last layer
        } */

        /* checkLevelProgress();   Check if the level needs to be advanced */

        // User input for command
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

    // Record end time for the entire program
    auto programEndTime = std::chrono::high_resolution_clock::now();

    // Calculate duration for the entire program
    auto programDuration = std::chrono::duration_cast<std::chrono::milliseconds>(programEndTime - programStartTime);

    std::cout << "Total time taken for the program: " << programDuration.count() << " milliseconds" << std::endl;
}

/* void Game::checkLevelProgress() {
    if (robots[currentRobot]->getScore() >= scoreThreshold) {
        advanceLevel();
    }
} */

/* void Game::advanceLevel() {
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
            // Optionally end the game if it's the highest level
            // gameRunning = false;
            return;
    }
} */
