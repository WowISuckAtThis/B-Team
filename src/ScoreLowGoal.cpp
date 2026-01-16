#include "ScoreLowGoal.h"
#include "main.h"

ScoreLowGoal::ScoreLowGoal(int speed) {
    voltage = speed;
}

int ScoreLowGoal::run() {
    pros::MotorGroup stages123({-12, -13, -14});
    
    stages123.move(voltage);
}

bool ScoreLowGoal::isDead() {
    return false;
}