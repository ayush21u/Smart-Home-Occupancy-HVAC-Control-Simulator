#include "logger.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>

void Logger::log(const SensorData& data, bool occupied, const HVACDecision& decision) {
    std::ofstream file("hvac_log.txt", std::ios::app);

    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);

    if (file) {
        file << std::put_time(local, "%Y-%m-%d %H:%M:%S")
             << " | Temp: " << std::fixed << std::setprecision(1) << data.temperature
             << " C | Humidity: " << data.humidity
             << " % | Occupied: " << (occupied ? "YES" : "NO")
             << " | HVAC: " << modeToString(decision.mode)
             << " | Fan: " << decision.fanSpeed << '\n';
    }
}
