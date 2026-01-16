#include "Store.h"
#include "main.h"

Store::Store(int speed) {
    voltage = speed;
}

int Store::run() {
    pros::MotorGroup stages12({12, 13});
    
    stages12.move(voltage);
}

bool Store::isDead() {
    return false;
}