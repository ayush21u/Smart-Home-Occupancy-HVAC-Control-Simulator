#include "config.h"

#include <fstream>
#include <iostream>
#include <sstream>

bool loadConfig(const std::string& filename, Config& config) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Warning: Could not open config file: "
                  << filename << std::endl;
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {

        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string key;
        std::string value;

        if (std::getline(iss, key, '=') &&
            std::getline(iss, value)) {

            if (key == "cooling_threshold") {
                config.coolingThreshold = std::stod(value);
            }
            else if (key == "heating_threshold") {
                config.heatingThreshold = std::stod(value);
            }
            else if (key == "energy_saving_when_unoccupied") {
                config.energySavingWhenUnoccupied =
                    (value == "true");
            }
            else if (key == "occupancy_timeout") {
                config.occupancyTimeout = std::stoi(value);
            }
        }
    }

    file.close();
    return true;
}