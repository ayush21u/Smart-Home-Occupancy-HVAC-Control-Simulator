#ifndef HVAC_CONTROLLER_H
#define HVAC_CONTROLLER_H

#include <string>

enum class HVACMode {
    OFF,
    COOLING,
    HEATING,
    ENERGY_SAVING
};

struct HVACDecision {
    HVACMode mode;
    std::string fanSpeed;
};

class HVACController {
private:
    double coolingThreshold;
    double heatingThreshold;

public:
    HVACController(double cooling = 26.0, double heating = 20.0);

    HVACDecision decide(double temperature, bool occupied) const;
};

std::string modeToString(HVACMode mode);

#endif