#include "TurnAction.h"
#include "PositionTracker.h"

TurnAction::TurnAction(double h_tar, uint32_t life_span) {
    life_time = life_span;
    init_time = pros::millis();

    hTar = h_tar;
}

int TurnAction::run() {
    double max_turn_vel = 10.0;

    double diff = hTar - PositionTracker::getHeading();
    if (isDead() || fabs(diff) < 0.05) return 1;

    double turn_dir = (diff < 0) ? -1.0 : 1.0;
    double vel = fabs(diff) > max_turn_vel ? turn_dir * max_turn_vel : diff;

    setDriveVelocities(0.0, vel);

    return 0;
}

bool TurnAction::isDead() {
    return pros::millis() > init_time + life_time;
}