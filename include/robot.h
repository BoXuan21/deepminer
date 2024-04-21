#ifndef ROBOT_H
#define ROBOT_H

#include "World.h"
#include "Robot.h"

class Robot {
protected:
    int x, y, z;
    int score;

public:
    Robot(World& world);
    void mine(World& world);
    int getScore() const { return score; }
    void resetPosition(World& world);  // Reset robot's position
    bool isAtLastLayer() const;        // Check if the robot is at the last layer
    void displayScore() const;  // Function to display the score
    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }
    void resetScore() { score = 0; }
    void robotAction(World& world);

private:
    void updatePosition(World& world);
};

#endif
