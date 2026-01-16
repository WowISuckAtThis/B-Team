#ifndef YOUREBACK
#define YOUREBACK
#include "PositionTracker.h"
#include "main.h"
#include <thread>

const double TRACKINGWHEELDIAMETER = 2.75;
const double LPODOFFSETX = -3.0625;
const double RPODOFFSETX =  3.0625;
const double CPODOFFSETY = -2.0;

double robot_x = 0;
double robot_y = 0;
double heading = 0;

void PositionTracker::setPosition(double initX, double initY, double initHeading) {
    robot_x = initX;
    robot_y = initY;
    heading = initHeading;
}

void PositionTracker::updatePosition() {
    pros::Rotation lPod(20); lPod.reset_position();   
    pros::Rotation rPod(19); rPod.reset_position();
    pros::Rotation cPod(18); cPod.reset_position();

    double mL = lPod.get_position() *  TRACKINGWHEELDIAMETER; lPod.reset_position();
    double mR = rPod.get_position() * -TRACKINGWHEELDIAMETER; rPod.reset_position();
    double mC = cPod.get_position() * -TRACKINGWHEELDIAMETER; cPod.reset_position();
    pros::lcd::print(0, "(%d, %d, %d)", mL, mC, mR);


    double diff = mR - mL;

    if (diff != 0) { //Arc Case
        //Center of Rotation Info - Relative to Robot's heading and position
        double rotCenterX = (RPODOFFSETX * mL - LPODOFFSETX * mR) / (diff);
        double arcAngle   = (mL != 0) ? (diff / (2 * RPODOFFSETX * mL)) : (diff / (2 * LPODOFFSETX * mR));
        double rotCenterY = mC * (1 / arcAngle) + CPODOFFSETY;

        //Convert coordinates into fields rotation and robots position
        double rotCenterXp = rotCenterX * cos(heading - M_PI / 2) - rotCenterY * sin(heading - M_PI / 2);
        double rotCenterYp = rotCenterY * cos(heading - M_PI / 2) + rotCenterX * sin(heading - M_PI / 2);

        //Rotate Robot Around its center of rotation, and add the robots field position
        robot_x += -rotCenterXp * cos(arcAngle) + rotCenterYp * sin(arcAngle);
        robot_y += -rotCenterYp * cos(arcAngle) - rotCenterXp * sin(arcAngle);
        heading += arcAngle;
    } else { //Straight Line Case
        double mLR = (mL + mR) / 2.0;

        robot_x += mC * cos(heading - M_PI / 2) - mLR * sin(heading - M_PI / 2);
        robot_y += mC * sin(heading - M_PI / 2) + mLR * cos(heading - M_PI / 2);
    }
}

std::tuple<double, double> PositionTracker::getPosition() {
    return std::make_tuple(robot_x, robot_y);
}

double PositionTracker::getHeading() {
    return heading;
}

#endif