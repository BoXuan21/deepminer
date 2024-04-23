#include "World.h"
#include "Robot.h"
#include <windows.h>  // Include Windows API header for handling console colors

// Function to set the color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Define color constants based on Windows Console colors
const int WHITE = 15;    // White text for normal field
const int RED = 12;      // Red text for danger field
const int YELLOW = 14;   // Yellow text for random field
const int GREEN = 10;    // Green text for bonus field
const int DEFAULT_COLOR = 7; // Default console color
const int BLUE = 1;

World::World() {
    srand(static_cast<unsigned int>(time(NULL)));  // Seed random number generator
    grid.resize(height, std::vector<std::vector<char>>(width, std::vector<char>(depth)));
    const char fieldTypes[] = {'O', '!', '?', '$'};
    const int fieldTypeCount = sizeof(fieldTypes) / sizeof(char);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < depth; ++k) {
                grid[i][j][k] = fieldTypes[rand() % fieldTypeCount];
            }
        }
    }
}

int World::calculateMaxInitialScore() {
    // Berechnet die maximale initiale Punktzahl basierend auf den Feldtypen in der Welt
    int maxInitialScore = 0;

    // Z�hle die Anzahl der Felder jedes Typs und berechne die Punkte entsprechend
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (int k = 0; k < depth; ++k) {
                char fieldType = grid[i][j][k];
                switch (fieldType) {
                    case 'O':
                        maxInitialScore += 5; // Punkte f�r ein normales Feld
                        break;
                    case '!':
                        maxInitialScore -= 5; // Punkte f�r ein Gefahrenfeld
                        break;
                    case '?':
                        maxInitialScore += 10; // Maximale Punkte f�r ein Zufallsfeld
                        break;
                    case '$':
                        maxInitialScore += 20; // Punkte f�r ein Bonusfeld
                        break;
                }
            }
        }
    }

    return maxInitialScore;
}

void World::displayWorld(const Robot& robot) {
    int robotLayer = robot.getZ();  // Get the current layer of the robot
    std::cout << "Current Layer: " << robotLayer << "\n";
    std::cout << "Points in the World: " << calculateMaxInitialScore() << "\n";

    // Display only the current layer
    std::cout << "Layer " << robotLayer << ":\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (robot.getX() == j && robot.getY() == i && robotLayer == robot.getZ()) {
                setColor(BLUE);  // Set color for robot
                std::cout << 'R' << " ";
            } else {
                char fieldType = grid[i][j][robotLayer];
                switch (fieldType) {
                    case 'O':
                        setColor(WHITE);  // Set color for normal field
                        break;
                    case '!':
                        setColor(RED);  // Set color for danger field
                        break;
                    case '?':
                        setColor(YELLOW);  // Set color for random field
                        break;
                    case '$':
                        setColor(GREEN);  // Set color for bonus field
                        break;
                }
                std::cout << fieldType << " ";
            }
            setColor(DEFAULT_COLOR);  // Reset to default color
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


char World::harvest(int x, int y, int z) {
    char harvestedValue = grid[x][y][z];
    grid[x][y][z] = 'O';  // Reset to a normal field after harvesting
    return harvestedValue;
}
