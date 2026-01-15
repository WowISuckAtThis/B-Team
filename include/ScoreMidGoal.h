#include "AutonomousAction.h"

class ScoreMidGoal: public AutonomousAction {
public:
    ScoreMidGoal(int speed);
    int run() override;

protected:
    bool isDead() override;
    double voltage;
};