#include "AutonomousAction.h"

class ScoreLowGoal: public AutonomousAction {
public:
    ScoreLowGoal(int speed);
    int run() override;

protected:
    bool isDead() override;
    double voltage;
};