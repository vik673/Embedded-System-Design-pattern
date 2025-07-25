# Interrupt Pattern Implementation

This directory contains a complete implementation of the Interrupt Pattern as described in the embedded systems design patterns documentation.

## Overview

The Interrupt Pattern allows embedded systems to respond to hardware events immediately, even when the system is busy with other processing. This implementation demonstrates how to structure interrupt handlers for button press/release events that control an LED.

## Files

### Core Implementation
- **ButtonHandler.h/c** - Main interrupt handler implementation
- **RobotInterruptVectorTable.h/c** - Interrupt vector table management
- **LED.h/c** - LED abstraction with on/off control
- **Button.h/c** - Button abstraction for input handling
- **main.c** - Example usage and demonstration

### Build System
- **Makefile** - Build configuration for gcc
- **README.md** - This documentation file

## Key Components

### Interrupt Handler (`ButtonHandler`)
- Manages interrupt vector installation/deinstallation
- Implements ISRs for button push and release events
- Controls LED state based on button events

### Interrupt Vector Table (`RobotInterruptVectorTable`)
- Global array of function pointers to ISRs
- Simulates hardware interrupt vector table
- Index 0: Button push interrupt
- Index 1: Button release interrupt

### Hardware Abstractions
- **LED**: Represents a controllable LED with on/off states
- **Button**: Represents a button input device

## Building and Running

### Prerequisites
- GCC compiler
- Make utility (optional, can compile manually)

### Build Commands
```bash
# Build the project
make

# Build and run
make run

# Clean build artifacts
make clean

# Build with debug information
make debug
```

### Manual Compilation
```bash
gcc -Wall -Wextra -std=c99 -o interrupt_pattern main.c ButtonHandler.c LED.c Button.c RobotInterruptVectorTable.c
```

## Pattern Benefits

1. **Immediate Response**: Events are handled as soon as they occur
2. **Non-blocking**: Main processing continues uninterrupted
3. **Deterministic**: Consistent response times for critical events
4. **Modular**: Clean separation between ISRs and application logic

## Real Embedded System Considerations

This implementation is designed for desktop simulation. For real embedded systems:

1. **Interrupt Keywords**: Add appropriate compiler-specific interrupt attributes
2. **Hardware Registers**: Replace printf statements with actual GPIO operations
3. **Memory Locations**: Place interrupt vector table at processor-specific addresses
4. **Atomic Operations**: Add proper synchronization for shared resources
5. **Stack Management**: Ensure adequate stack space for ISR execution

## Example Output

```
Interrupt Pattern Example
========================

Interrupt vectors installed:
- Vector 0: Button Push Interrupt
- Vector 1: Button Release Interrupt

Simulating button press interrupt...
LED turned ON (Pin 13)

Simulating button release interrupt...
LED turned OFF (Pin 13)

Checking LED state: OFF

Interrupt vectors deinstalled.

Program completed successfully.
```

## Thread Safety Considerations

In real embedded systems, consider:
- Disabling interrupts during critical sections
- Using atomic operations for shared variables
- Implementing mutex protection for shared resources
- Avoiding blocking operations in ISRs

## Further Reading

Refer to the `Interruptpattern.txt` file for detailed pattern theory and embedded-specific implementation strategies.
