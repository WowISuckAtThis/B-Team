#include "ScoreMidGoal.h"
#include "main.h"

ScoreMidGoal::ScoreMidGoal(int speed) {
    voltage = speed;
}

int ScoreMidGoal::run() {
    pros::MotorGroup stages123({12, -13, -14});
    
    stages123.move(voltage);
}

bool ScoreMidGoal::isDead() {
    return false;
}