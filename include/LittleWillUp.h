#include "AutonomousAction.h"

class LittleWillUp: public AutonomousAction {
public:
    LittleWillUp();
    int run();

protected:
    bool isDead();
};