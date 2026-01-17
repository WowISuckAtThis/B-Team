#include "AutonomousAction.h"

class DriveDistanceAction: public AutonomousAction {
public:
    DriveDistanceAction(double dist, uint32_t life_span);
    int run();

protected:
    int forward_backward;
    double distance;
    double init_rx;
    double init_ry;
    double init_heading;
    bool isDead();
};