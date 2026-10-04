# Design Document

## Problem
A smart home needs to control HVAC equipment according to room occupancy and environmental conditions while reducing unnecessary energy consumption.

## Inputs
- Temperature
- Humidity
- Motion/occupancy

## Outputs
- Cooling
- Heating
- HVAC OFF
- Energy Saving Mode
- Fan speed

## Control Logic

```text
IF room is unoccupied
    Energy Saving Mode
ELSE IF temperature > 26
    Cooling
ELSE IF temperature < 20
    Heating
ELSE
    HVAC OFF
```

## Linux Concepts
- Kernel module
- Character device
- Device number allocation
- `struct file_operations`
- `open()`
- `read()`
- `write()`
- `release()`
- `/dev` device interface
