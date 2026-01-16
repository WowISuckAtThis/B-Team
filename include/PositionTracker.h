#include <tuple>

class PositionTracker {

public:
    static void setPosition(double initX, double initY, double initHeading);
    static void updatePosition();
    static std::tuple<double, double> getPosition();
    static double getHeading();
};