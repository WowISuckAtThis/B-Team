#include "DriveDistanceAction.h"
#include "main.h"
#include "PositionTracker.h"

DriveDistanceAction::DriveDistanceAction(double dist, uint32_t life_span) {
    distance = dist;
    life_time = life_span;
    init_time = pros::millis();
    double r_x = 0;
    double r_y = 0;
    std::tie(r_x, r_y) = PositionTracker::getPosition();
    double heading = PositionTracker::getHeading();
    double t_x = init_rx + distance * cos(init_heading);
    double t_y = init_ry + distance * sin(init_heading);
    int forward_backward = (sqrt(pow(t_x - r_x, 2) + pow(t_y - r_y, 2) < 1.0)) ? 1.0 : -1.0;
    double init_rx;
    double init_ry;
    double init_heading = PositionTracker::getHeading();
    std::tie(init_rx, init_ry) = PositionTracker::getPosition();
}

int DriveDistanceAction::run() {
    if (isDead()) return 1;
    double speed;

    setDriveVelocities(speed * forward_backward, 0.0);
}

bool DriveDistanceAction::isDead() {
    double r_x = 0;
    double r_y = 0;
    std::tie(r_x, r_y) = PositionTracker::getPosition();
    double heading = PositionTracker::getHeading();
    double t_x = init_rx + distance * cos(init_heading);
    double t_y = init_ry + distance * sin(init_heading);
    bool age = pros::millis() >= life_time + init_time;
    bool proximity = sqrt(pow(t_x - r_x, 2) + pow(t_y - r_y, 2) < 1.0);
    bool direction = (forward_backward * (t_x - r_x) * cos(init_heading) + (t_y - r_y) * sin(init_heading)) <= 0;

    return age || proximity || direction;
}