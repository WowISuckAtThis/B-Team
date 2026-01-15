#include "LittleWillDown.h"
#include "main.h"

LittleWillDown::LittleWillDown() {

}

int LittleWillDown::run() {
    pros::ADIDigitalOut will(7);
    return will.set_value(1);
}

bool isDead() {
    return false;
}