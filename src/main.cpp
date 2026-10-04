#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "sensor_simulator.h"
#include "occupancy.h"
#include "hvac_controller.h"
#include "logger.h"

int main() {
    SensorSimulator sensors;
    OccupancyManager occupancyManager;
    HVACController controller;
    Logger logger;

    std::cout << "========================================\n";
    std::cout << " Smart Home Occupancy & HVAC Simulator\n";
    std::cout << "========================================\n\n";

    for (int cycle = 1; cycle <= 10; ++cycle) {
        SensorData data = sensors.generate();
        bool occupied = occupancyManager.isOccupied(data.motionDetected);
        HVACDecision decision = controller.decide(data.temperature, occupied);

        std::cout << "Cycle " << cycle << "\n";
        std::cout << "Temperature : " << std::fixed << std::setprecision(1)
                  << data.temperature << " C\n";
        std::cout << "Humidity    : " << data.humidity << " %\n";
        std::cout << "Motion      : " << (data.motionDetected ? "DETECTED" : "NONE") << "\n";
        std::cout << "Occupancy   : " << (occupied ? "OCCUPIED" : "UNOCCUPIED") << "\n";
        std::cout << "HVAC Mode   : " << modeToString(decision.mode) << "\n";
        std::cout << "Fan Speed   : " << decision.fanSpeed << "\n";
        std::cout << "----------------------------------------\n";

        logger.log(data, occupied, decision);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Simulation completed.\n";
    return 0;
}
