#include "AutonomousTask.h"
#include "DriveTask.h"
#include "main.h"

DriveTask::DriveTask(double x_tar, double y_tar, uint32_t life_span) {
    life_time = life_span;
    init_time = pros::millis();

    xTar = x_tar;
    yTar = y_tar;
}

void DriveTask::run() {
    //TODO
}

bool DriveTask::isDead() {
    //May be rehashed later to taken curr velocity into account
    return pros::millis() >= life_time + init_time;
}