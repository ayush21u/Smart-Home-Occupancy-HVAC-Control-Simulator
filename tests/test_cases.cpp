#include <iostream>
#include <cassert>
#include "../include/hvac_controller.h"
#include "../include/occupancy.h"

int main() {
    HVACController controller;
    OccupancyManager occupancy;

    assert(occupancy.isOccupied(true) == true);
    assert(occupancy.isOccupied(false) == false);

    auto cooling = controller.decide(30.0, true);
    assert(cooling.mode == HVACMode::COOLING);

    auto heating = controller.decide(18.0, true);
    assert(heating.mode == HVACMode::HEATING);

    auto normal = controller.decide(24.0, true);
    assert(normal.mode == HVACMode::OFF);

    auto saving = controller.decide(30.0, false);
    assert(saving.mode == HVACMode::ENERGY_SAVING);

    std::cout << "All test cases passed.\n";
    return 0;
}
