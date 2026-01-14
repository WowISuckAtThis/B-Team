#ifndef YOUREBACK
#define YOUREBACK
#include <cstdint>

class AutonomousTask {
protected:
    uint32_t init_time;
    uint32_t life_time;

virtual bool isDead(uint32_t curr_time) = 0;

public:
    virtual int run(uint32_t curr_time) = 0;
    virtual ~AutonomousTask() = default;
};
#endif