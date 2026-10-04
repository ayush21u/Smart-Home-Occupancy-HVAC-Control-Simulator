#include "sensor_simulator.h"
#include <random>

SensorData SensorSimulator::generate() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<double> temperature(16.0, 34.0);
    static std::uniform_real_distribution<double> humidity(35.0, 80.0);
    static std::bernoulli_distribution motion(0.65);

    return {
        temperature(generator),
        humidity(generator),
        motion(generator)
    };
}
