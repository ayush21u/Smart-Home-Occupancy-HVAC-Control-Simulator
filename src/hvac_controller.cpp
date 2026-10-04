#include "hvac_controller.h"

HVACController::HVACController(double cooling, double heating)
    : coolingThreshold(cooling),
      heatingThreshold(heating) {
}

HVACDecision HVACController::decide(double temperature, bool occupied) const {

    if (!occupied) {
        return {HVACMode::ENERGY_SAVING, "OFF"};
    }

    if (temperature > coolingThreshold) {
        std::string fan = temperature > 30.0 ? "HIGH" : "MEDIUM";
        return {HVACMode::COOLING, fan};
    }

    if (temperature < heatingThreshold) {
        return {HVACMode::HEATING, "MEDIUM"};
    }

    return {HVACMode::OFF, "LOW"};
}

std::string modeToString(HVACMode mode) {

    switch (mode) {
        case HVACMode::COOLING:
            return "COOLING";

        case HVACMode::HEATING:
            return "HEATING";

        case HVACMode::ENERGY_SAVING:
            return "ENERGY SAVING";

        default:
            return "OFF";
    }
}