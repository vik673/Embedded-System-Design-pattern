# Guarded Call Pattern Implementation

This directory contains a complete implementation of the Guarded Call Pattern as described in the embedded systems design pattern documentation.

## Overview

The Guarded Call Pattern serializes access to a set of services that could potentially interfere with each other if called simultaneously by multiple callers. It uses semaphores to protect a related set of services from simultaneous access by multiple clients in a preemptive multitasking environment.

## Architecture

The implementation consists of the following components:

### Core Components
- **GuardedCallExample.h** - Main header with forward declarations and OS API
- **OSSemaphore.h/c** - Semaphore implementation for mutual exclusion
- **Position.h/c** - Position data structure (latitude, longitude, altitude)
- **Attitude.h/c** - Attitude data structure (pitch, roll, yaw)

### Guarded Resource
- **KinematicData.h/c** - The shared resource that uses semaphores to protect access to attitude and position data

### Client Classes
- **AttitudeController.h/c** - Manages aircraft attitude data
- **Navigator.h/c** - Updates position information
- **FlightDataDisplay.h/c** - Displays flight data to users

### Demo
- **main.c** - Demonstration program showing the pattern in action

## Key Features

1. **Mutual Exclusion**: The `KinematicData` class uses semaphores to ensure that only one client can access the data at a time
2. **Thread Safety**: All data access methods are protected by lock/release operations
3. **Concurrent Access**: Multiple clients can safely access the shared resource without data corruption
4. **Resource Management**: Proper initialization and cleanup of semaphores

## Building the Project

### Using Make (Linux/macOS/WSL)
```bash
make clean
make
make run
```

### Using GCC directly (Windows/Linux/macOS)
```bash
gcc -Wall -Wextra -std=c99 *.c -o guarded_call_demo
./guarded_call_demo
```

## Expected Output

When you run the demo, you should see:
- Semaphore creation and lock/release operations
- Attitude and position data being set and retrieved
- Multiple clients accessing the shared resource safely
- Clean resource destruction

## Pattern Benefits

1. **Data Integrity**: Prevents data corruption from simultaneous access
2. **Timely Access**: Provides immediate access when resource is not locked
3. **Scalability**: Multiple clients can safely share the same resource
4. **Modularity**: Clean separation between resource and clients

## Important Notes

- In a real RTOS environment, the semaphore implementation would be provided by the operating system
- This implementation simulates the blocking behavior with print statements
- Priority inheritance would be handled by the RTOS to prevent priority inversion
- The pattern is most effective when combined with proper task priority management

## Files Structure

```
implementation/
├── GuardedCallExample.h    # Main header file
├── OSSemaphore.h/c        # Semaphore implementation
├── Position.h/c           # Position data structure
├── Attitude.h/c           # Attitude data structure
├── KinematicData.h/c      # Guarded resource
├── AttitudeController.h/c # Attitude client
├── Navigator.h/c          # Navigation client
├── FlightDataDisplay.h/c  # Display client
├── main.c                 # Demo program
├── Makefile              # Build configuration
└── README.md             # This file
```

This implementation demonstrates the core concepts of the Guarded Call Pattern while maintaining the structure and naming conventions specified in the original documentation.
