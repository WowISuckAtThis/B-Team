#include "ScoreTopGoal.h"
#include "main.h"

ScoreTopGoal::ScoreTopGoal(int speed) {
    voltage = speed;
}

int ScoreTopGoal::run() {
    pros::MotorGroup stages123({12, 13, 14});
    
    stages123.move(voltage);
}

bool ScoreTopGoal::isDead() {
    return false;
}