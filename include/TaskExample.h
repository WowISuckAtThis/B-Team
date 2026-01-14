#include "AutonomousTask.h"
#include "main.h"
#include <cstdint>

class TaskExample: public AutonomousTask {
    public:
        TaskExample(uint32_t curr_time, uint32_t life_span);

        int run(uint32_t curr_time) override;

    bool isDead(uint32_t curr_time) override;
};