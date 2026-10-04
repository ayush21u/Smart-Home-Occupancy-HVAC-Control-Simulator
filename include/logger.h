#ifndef LOGGER_H
#define LOGGER_H

#include "sensor_simulator.h"
#include "hvac_controller.h"

class Logger {
public:
    void log(const SensorData& data, bool occupied, const HVACDecision& decision);
};

#endif
