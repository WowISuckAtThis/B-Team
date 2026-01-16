#include "AutonomousAction.h"

class LittleWillDown: public AutonomousAction {
public:
    LittleWillDown();
    int run();

protected:
    bool isDead();
};