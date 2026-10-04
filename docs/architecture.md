# System Architecture

## Layers

1. Sensor Simulation Layer
2. Linux Device Driver Layer
3. User-Space C++ Control Layer
4. HVAC Actuator Simulation Layer
5. Logging Layer

## Data Flow

```text
Sensor Data
    |
    v
Linux Character Driver
    |
    v
C++ Application
    |
    +--> Occupancy Manager
    |
    +--> HVAC Controller
    |
    v
HVAC Decision
    |
    v
Logger / Actuator Simulation
```

## Software Architecture

The application uses separate modules for sensor generation, occupancy detection, HVAC decisions, and logging. The Linux kernel module demonstrates the hardware/software interface expected in an embedded or smart-home architecture.
