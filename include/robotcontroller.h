#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "Robot.h"
#include "World.h"

class RobotController {
public:
    static void mineWithRobot(Robot* robot, World* world);
};

#endif // ROBOT_CONTROLLER_H
