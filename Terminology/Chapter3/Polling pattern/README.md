# Polling Pattern Implementation
## Embedded System Design Pattern

This project demonstrates the **Polling Pattern** for embedded systems, specifically implemented for a breathing circuit monitoring system in medical equipment.

## Overview

The Polling Pattern is used to periodically check sensor data when:
- Data is not critically urgent
- Hardware cannot generate interrupts
- Regular monitoring is sufficient

## Architecture

### Core Components

1. **BCPeriodicPoller** - Central polling coordinator
   - Manages periodic polling of multiple sensors
   - Coordinates with timer for regular intervals
   - Distributes sensor data to display

2. **BCTimer** - Timer management with interrupt simulation
   - Provides periodic timer interrupts
   - Manages timer start/stop operations
   - Simulates hardware timer ISR

3. **BreathingCircuitSensor** - Sensor abstraction
   - Three sensor types: O2 concentration, gas pressure, circuit pressure
   - Provides data and state information
   - Simulates real sensor readings

4. **MedicalDisplay** - Display interface
   - Shows sensor readings with status indicators
   - Provides visual alarms and warnings
   - Maintains current system state

## Key Design Patterns

### Polling Pattern Features
- **Periodic Polling**: Timer-driven regular sensor checks
- **Multi-device Support**: Handles multiple sensors simultaneously
- **State Management**: Tracks sensor states and error conditions
- **Relationship Management**: Proper component coupling/decoupling

### Safety Features
- **Alarm Thresholds**: Automatic alarm generation for critical values
- **Error Handling**: Graceful handling of sensor failures
- **Status Monitoring**: Continuous monitoring of system health

## File Structure

```
polling pattern/
├── BCPeriodicPoller.h/c    # Main polling coordinator
├── BCTimer.h/c             # Timer and interrupt management
├── BreathingCircuitSensor.h/c  # Sensor interface and simulation
├── MedicalDisplay.h/c      # Display and user interface
├── main.c                  # Demo application
├── Makefile               # Build configuration
└── README.md              # This file
```

## Building and Running

### Prerequisites
- GCC compiler
- Make utility
- Standard C library

### Build Commands

```bash
# Build the project
make all

# Clean build artifacts
make clean

# Build and run demo
make run

# Debug build
make debug

# Release build
make release
```

### Running the Demo

```bash
# Direct execution
./polling_pattern_demo

# Or via make
make run
```

## Demo Output

The demo will:
1. Initialize all system components
2. Set up sensor relationships
3. Start periodic polling (2-second intervals)
4. Display sensor readings with status
5. Run for 10 polling cycles
6. Show final system status
7. Clean shutdown

## Example Output

```
=== Embedded System Polling Pattern Demo ===
Breathing Circuit Monitoring System

System components created successfully
Timer started with period: 2000 ms
Periodic polling started

--- Polling sensors ---
DISPLAY: O2 Concentration: 21%
DISPLAY: Gas Flow: 15 cmH2O
DISPLAY: Gas Flow Status: NORMAL
DISPLAY: Circuit Pressure: 5 cmH2O
--- End polling ---
```

## Implementation Notes

### Sensor Monitoring
- **O2 Concentration**: Normal range 19-23%, Critical below 18% or above 24%
- **Gas Pressure**: Normal range 8-25 cmH2O, Critical below 5 or above 30
- **Circuit Pressure**: Normal below 15 cmH2O, Critical above 20 cmH2O

### Timer Simulation
- Uses software simulation of hardware timer interrupts
- In real embedded systems, this would be actual hardware ISR
- Demonstrates proper interrupt handling patterns

### Memory Management
- Proper constructor/destructor patterns
- Safe memory allocation and deallocation
- Relationship cleanup on shutdown

## Real-World Applications

This pattern is commonly used in:
- **Medical Devices**: Patient monitoring, ventilators
- **Industrial Control**: Process monitoring, safety systems
- **Automotive**: Engine management, emissions monitoring
- **IoT Devices**: Environmental sensors, smart meters

## Advantages

- **Simple Implementation**: Easy to understand and maintain
- **Predictable Timing**: Regular, known polling intervals
- **Resource Efficient**: Lower CPU overhead than continuous monitoring
- **Multi-device Support**: Can handle many sensors simultaneously

## Limitations

- **Response Latency**: Maximum delay equals polling period
- **Data Loss Risk**: Fast-changing data might be missed
- **Timing Constraints**: Must complete polling within period
- **Power Consumption**: Continuous operation even when no data changes

## Extensions

Possible enhancements:
- **Adaptive Polling**: Variable polling rates based on sensor criticality
- **Event-driven Hybrid**: Combination with interrupt pattern
- **Data Logging**: Historical sensor data storage
- **Network Integration**: Remote monitoring capabilities
- **Fault Tolerance**: Sensor failure detection and recovery

## Educational Value

This implementation demonstrates:
- Embedded system design patterns
- C programming best practices
- Component-based architecture
- Real-time system concepts
- Hardware abstraction techniques
