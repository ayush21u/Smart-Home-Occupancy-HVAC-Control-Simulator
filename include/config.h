#ifndef CONFIG_H
#define CONFIG_H

#include <string>

struct Config {
    double coolingThreshold = 26.0;
    double heatingThreshold = 20.0;
    bool energySavingWhenUnoccupied = true;
    int occupancyTimeout = 30;
};

bool loadConfig(const std::string& filename, Config& config);

#endif