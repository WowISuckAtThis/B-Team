#include "AutonomousAction.h"
#include "main.h"
#include <cstdint>

class DriveAction: public AutonomousAction {
public:
    DriveAction(double x_tar, double y_tar, uint32_t life_span);
    int run() override;

protected:
    double xTar;
    double yTar; 
    bool isDead() override;
};