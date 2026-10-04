#ifndef SENSOR_SIMULATOR_H
#define SENSOR_SIMULATOR_H

struct SensorData {
    double temperature;
    double humidity;
    bool motionDetected;
};

class SensorSimulator {
public:
    SensorData generate();
};

#endif
