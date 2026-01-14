#include "AutonomousTask.h"
#include "main.h"
#include <cstdint>

class TaskExample: public AutonomousTask {

public:
    TaskExample(uint32_t life_span);
    void run() override;

protected:
    bool isDead() override;
};