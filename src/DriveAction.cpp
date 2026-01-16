#include "AutonomousAction.h"
#include "DriveAction.h"
#include "PositionTracker.h"
#include "main.h"
#include "pros/motor_group.hpp"

DriveAction::DriveAction(double x_tar, double y_tar, uint32_t life_span) {
    life_time = life_span;
    init_time = pros::millis();

    xTar = x_tar;
    yTar = y_tar;
}

int DriveAction::run() {
    //TODO
    if (isDead()) return 1;
    double xCur;
    double yCur;
    std::tie(xCur, yCur) = PositionTracker::getPosition();

    double hCur = PositionTracker::getHeading();

    double deltaX = xTar - xCur;
    double deltaY = yTar - yCur;

    double dist = sqrt(deltaX * deltaX + deltaY * deltaY);

    double deltaXNorm = deltaX / dist;
    double deltaYNorm = deltaY / dist;

    double xFacingNorm = cos(hCur);
    double yFacingNorm = sin(hCur);

    double xFacingNormDeriv = -sin(hCur);
    double yFacingNormDeriv =  cos(hCur);

    double dotProd      = deltaXNorm * xFacingNorm      + deltaYNorm * yFacingNorm;
    double dotProdDeriv = deltaXNorm * xFacingNormDeriv + deltaYNorm * yFacingNormDeriv;

    double max_vel = 20.0;
    double vel = max_vel;

    double front_or_back = (dotProd > 0) ? 1.0 : -1.0;
    double turning = max_vel * dotProdDeriv * front_or_back;

    pros::MotorGroup({});
    pros::MotorGroup({});

    return 0;
}

bool DriveAction::isDead() {
    //May be rehashed later to take curr velocity into account
    double xCur;
    double yCur;
    std::tie(xCur, yCur) = PositionTracker::getPosition();

    double dist = sqrt(pow(xCur - xTar, 2) + pow(yCur - yTar, 2));
    return (pros::millis() >= life_time + init_time || dist < 0.5);
}