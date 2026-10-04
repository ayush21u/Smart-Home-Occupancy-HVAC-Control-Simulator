# Smart Home Occupancy & HVAC Control Simulator

## 1. Project Overview

The Smart Home Occupancy & HVAC Control Simulator is a Linux-based
simulation project developed using C and C++.

The project simulates environmental sensor data such as temperature,
humidity, and motion. Based on room occupancy and temperature, the
system automatically decides whether the HVAC system should cool,
heat, remain off, or enter energy-saving mode.

The project also includes a Linux character device driver to
demonstrate basic Linux device-driver concepts.

---

## 2. Objectives

- Simulate smart-home environmental sensors.
- Detect room occupancy using motion information.
- Automatically control a simulated HVAC system.
- Reduce unnecessary HVAC operation when the room is unoccupied.
- Demonstrate Linux character device-driver concepts.
- Demonstrate user-space and kernel-space interaction.
- Use C and C++ for the complete implementation.
- Build and test the project on Linux.

---

## 3. Main Features

- Temperature simulation
- Humidity simulation
- Motion detection
- Occupancy detection
- Automatic HVAC control
- Cooling mode
- Heating mode
- Energy-saving mode
- Fan-speed control
- HVAC activity logging
- Linux character device driver
- Automated test cases

---

## 4. System Architecture

```text
              SMART HOME SYSTEM
                     |
          +----------+----------+
          |                     |
   Temperature Sensor      Occupancy Sensor
          |                     |
          +----------+----------+
                     |
                     v
             Sensor Data
                     |
                     v
             Occupancy Logic
                     |
                     v
             HVAC Controller
                     |
          +----------+----------+
          |          |          |
       COOLING     HEATING     OFF
          |
          v
     Energy Saving
     when unoccupied
                     |
                     v
                 Logger