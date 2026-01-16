#include "AutonomousAction.h"

class Store: public AutonomousAction {
public:
    Store(int speed);
    int run() override;

protected:
    bool isDead() override;
    double voltage;
};