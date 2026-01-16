#include "AutonomousAction.h"
#include "main.h"
#include <cstdint>

class Wait: public AutonomousAction {
public:
    Wait(uint32_t life_span);
    int run() override;

protected:
    bool isDead() override;
};