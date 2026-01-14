#include "AutonomousTask.h"
#include "TaskExample.h"
#include "main.h"

TaskExample::TaskExample(uint32_t life_span) {
    life_time = life_span;
    init_time = pros::millis();
}

void TaskExample::run() {
    if (isDead()) return;
    
    test();
}

bool TaskExample::isDead() {
    return pros::millis() >= life_time + init_time;
}    
