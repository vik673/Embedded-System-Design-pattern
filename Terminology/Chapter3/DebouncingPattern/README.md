# Debouncing Pattern Implementation in C

This is a complete implementation of the Debouncing Pattern as described in embedded systems design patterns literature. The pattern is designed to filter out false events caused by mechanical switch bouncing.

## Overview

The Debouncing Pattern solves the problem where mechanical switches (buttons, relays, etc.) generate multiple electronic signals due to physical contact bouncing. This implementation demonstrates a microwave oven toggle button that properly handles button bouncing.

## Components

### Core Pattern Components

1. **Button** (`Button.h`, `Button.c`)
   - Represents the bouncing hardware device
   - Simulates mechanical switch bouncing behavior
   - Manages device state and backlight

2. **ButtonDriver** (`ButtonDriver.h`, `ButtonDriver.c`)
   - The debouncer component
   - Processes incoming events and filters bouncing
   - Implements toggle logic for microwave control

3. **Timer** (`Timer.h`, `Timer.c`)
   - Provides non-busy wait debouncing delay
   - Supports configurable resolution
   - Cross-platform sleep implementation

4. **MicrowaveEmitter** (`MicrowaveEmitter.h`, `MicrowaveEmitter.c`)
   - Application client that receives debounced events
   - Represents the microwave heating element
   - Manages power levels and emission state

## Key Features

- **Debounce Filtering**: Filters out rapid state changes within 40ms window
- **Toggle Functionality**: Press once to turn on, press again to turn off
- **State Management**: Proper cleanup and association management
- **Cross-platform**: Works on Windows and Unix-like systems
- **Configurable Timing**: Adjustable debounce periods and timer resolution

## Building and Running

### Using Make (recommended)
```bash
# Build the demo
make

# Build and run
make run

# Clean build artifacts
make clean

# Show all available targets
make help
```

### Manual Compilation
```bash
# Compile all source files
gcc -Wall -Wextra -std=c99 -g -c *.c

# Link the executable
gcc *.o -o debouncing_demo

# Run the demo
./debouncing_demo
```

### Windows (PowerShell)
```powershell
# Compile and link
gcc -Wall -Wextra -std=c99 -g *.c -o debouncing_demo.exe

# Run
.\debouncing_demo.exe
```

## Demo Scenarios

The main program demonstrates three key scenarios:

1. **Normal Operation**: Regular button press/release cycles
2. **Bouncing Simulation**: Simulates mechanical switch bouncing
3. **Rapid Press Test**: Tests debouncing with rapid button events

## Pattern Benefits

- **Reliability**: Eliminates false triggering from switch bouncing
- **Configurable**: Adjustable debounce timing for different hardware
- **Separation of Concerns**: Clean separation between hardware and application logic
- **Reusable**: Pattern can be applied to any bouncing input device

## Configuration

Key constants in `ButtonDriver.h`:
- `DEBOUNCE_TIME`: Debounce period in milliseconds (default: 40ms)
- `LOOPS_PER_MS`: Calibration for busy-wait timing (if needed)

## Architecture Notes

The implementation follows object-oriented principles in C:
- Proper encapsulation with public/private methods
- Constructor/destructor pattern
- Association management between objects
- Clean separation of interface and implementation

## Use Cases

This pattern is essential for:
- Push buttons and toggle switches
- Mechanical relays
- Reed switches
- Any metal-contact input device
- Interrupt-driven input systems

## Embedded System Considerations

- Timer resolution affects minimum debounce period
- Interrupt handling may require static methods
- Memory management should be adapted for embedded constraints
- Consider using hardware timers instead of software delays in real systems
