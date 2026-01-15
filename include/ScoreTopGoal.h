#include "AutonomousAction.h"

class ScoreTopGoal: public AutonomousAction {
public:
    ScoreTopGoal(int speed);
    int run() override;

protected:
    bool isDead() override;
    double voltage;
};