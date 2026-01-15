#include "AutonomousAction.h"
#include "DriveAction.h"
#include "PositionTracker.h"
#include "main.h"

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

    
}

bool DriveAction::isDead() {
    //May be rehashed later to take curr velocity into account
    return pros::millis() >= life_time + init_time;
}