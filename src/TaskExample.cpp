#include "AutonomousTask.h"
#include "TaskExample.h"
#include "main.h"

TaskExample::TaskExample(uint32_t curr_time, uint32_t life_span) {
    life_time = life_span;
    init_time = curr_time;
}

int TaskExample::run(uint32_t curr_time) {
    if (isDead(curr_time)) return -1;

    test();
    return 1;
}

bool TaskExample::isDead(uint32_t curr_time) {
    return curr_time >= life_time + init_time;
}    
