#ifndef YOUREBACK
#define YOUREBACK
#include <cstdint>

class AutonomousTask {
protected:
    uint32_t init_time;
    uint32_t life_time;

    virtual bool isDead() = 0;


public:
    virtual void run() = 0;
    virtual ~AutonomousTask() = default;
};
#endif