#ifndef YOUREBACK
#define YOUREBACK
#include <cstdint>

class AutonomousAction {
protected:
    uint32_t init_time;
    uint32_t life_time;
    
    virtual bool isDead() = 0;

public:
    virtual int run() = 0;
    virtual ~AutonomousAction() = default;
};
#endif