# Testing

| Test | Input | Expected Result |
|---|---|---|
| 1 | Occupied, 30 C | Cooling |
| 2 | Occupied, 18 C | Heating |
| 3 | Occupied, 24 C | HVAC Off |
| 4 | Unoccupied, 30 C | Energy Saving |
| 5 | Motion detected | Occupied |
| 6 | No motion | Unoccupied |

## Commands

Build application:

```bash
make
```

Run application:

```bash
./smart_home
```

Build tests:

```bash
make test
```

Run tests:

```bash
./test_cases
```

Build driver:

```bash
cd driver
make
```
