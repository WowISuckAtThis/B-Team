#include "Wait.h"

Wait::Wait(uint32_t life_span) {
    life_time = life_span;
}

int Wait::run() {
    pros::delay(life_time);
    return 1;
}