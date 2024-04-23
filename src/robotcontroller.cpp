#include "RobotController.h"
#include <chrono>
#include <thread>

void RobotController::mineWithRobot(Robot* robot, World* world) {
    while (!robot->isAtLastLayer()) {
        robot->mine(*world);
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
    }
}
