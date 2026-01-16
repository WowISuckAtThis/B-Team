#include "LittleWillUp.h"
#include "main.h"

LittleWillUp::LittleWillUp() {

}

int LittleWillUp::run() {
    pros::ADIDigitalOut will(7);
    return will.set_value(0);
}

bool LittleWillUp::isDead() {
    return false;
}