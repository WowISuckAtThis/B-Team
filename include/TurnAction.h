#include "AutonomousAction.h"
#include "main.h"
#include <cstdint>

class TurnAction: public AutonomousAction {
public:
    TurnAction(double h_tar, uint32_t life_span);
    int run() override;

protected:
    double hTar;
    bool isDead() override;
};