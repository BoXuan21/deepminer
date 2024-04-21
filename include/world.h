#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include <iostream>
#include <mutex>

class World {
private:
    std::vector<std::vector<std::vector<char>>> grid;
    static const int depth = 10;
    static const int height = 5;
    static const int width = 5;
    std::mutex mutex; // Definition des Mutex als Datenmitglied

public:
    World();
    void displayWorld(const class Robot& robot);
    char harvest(int x, int y, int z);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void displayInitialSum();
    int calculateMaxInitialScore();
    int maxInitialScore();
     std::mutex& getMutex() {
        return mutex;
    }
};

#endif
