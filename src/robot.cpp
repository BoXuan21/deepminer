#include "Robot.h"
#include <cstdlib>  // For rand()
#include <chrono>
#include <thread>
#include <mutex>

Robot::Robot(World& world) : x(0), y(0), z(9), score(0) {
    updatePosition(world);
}

void Robot::updatePosition(World& world) {
    x = rand() % world.getWidth();  // Randomize x within world bounds
    y = rand() % world.getHeight(); // Randomize y within world bounds
    // You might not want to reset 'z' here if it's only to be updated
}


void Robot::mine(World& world) {
    if (z > 0) {
        z--;  // Move down a layer
    }
    updatePosition(world);  // Move to a new random position

    char field = world.harvest(x, y, z);  // Harvest the field at the new position

    // Score updates based on the type of field
    switch (field) {
        case 'O':  // Normal field
            score += 10;
            break;
        case '!':  // Danger field
            score -= 5;
            break;
        case '?':  // Random field
            score += rand() % 10 + 1;
            break;
        case '$':  // Money field
            score += 25;
            break;
    }
}

void Robot::robotAction(World& world) {
    while (!isAtLastLayer()) {
        mine(world); // Bergbauaktion ausführen
        std::this_thread::sleep_for(std::chrono::milliseconds(750)); // Wartezeit zwischen den Aktionen
        // Mutex sperren, um den Zugriff auf das Spielfeld zu synchronisieren
        std::lock_guard<std::mutex> lock(world.getMutex());
        // Mutex entsperren, um anderen Threads den Zugriff auf das Spielfeld zu ermöglichen
        // Der lock_guard wird automatisch entsperrt, wenn seine Lebensdauer endet

    }
}

void Robot::resetPosition(World& world) {
    x = rand() % world.getWidth();  // Randomize x within world bounds
    y = rand() % world.getHeight(); // Randomize y within world bounds
    z = 9;  // Reset z to the top layer, ensuring we start from the top
}


bool Robot::isAtLastLayer() const {
    return z == 0;
}

void Robot::displayScore() const {
    std::cout << "Current Score: " << score << std::endl;
}

