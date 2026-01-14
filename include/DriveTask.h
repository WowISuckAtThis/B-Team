#include "AutonomousTask.h"
#include "main.h"
#include <cstdint>

class DriveTask: public AutonomousTask {
public:
    double xTar;
    double yTar; 

    DriveTask(double x_tar, double y_tar, uint32_t life_span);
    void run() override;

protected:
    bool isDead() override;
};