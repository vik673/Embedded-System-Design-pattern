# Ordered Locking Pattern Implementation

This directory contains a complete implementation of the Ordered Locking Pattern as described in the embedded systems design patterns documentation.

## Pattern Overview

The Ordered Locking Pattern prevents deadlock by eliminating circular waiting conditions. It enforces a policy where resources must always be locked in a specific order based on their resource IDs.

### Key Components

1. **Mutex** - Provides basic locking mechanism
2. **ResourceList** - Maintains ordered list of locked resources and enforces ordering policy
3. **OrderedResource** (sensors) - Resources with unique IDs that must be locked in order
4. **ResourceClient** - Clients that use the resources

### Resource Ordering

The implementation uses the following resource ID ordering:
- PositionSensor: ID = 1 (lowest)
- VelocitySensor: ID = 2 (middle)  
- AttitudeSensor: ID = 3 (highest)

## Files Structure

### Core Pattern Implementation
- `OrderedLockingExample.h` - Common error codes and definitions
- `Mutex.h/c` - Basic mutex implementation
- `ResourceList.h/c` - Ordered resource list manager

### Data Types
- `Position.h/c` - Position data structure
- `Velocity.h/c` - Velocity data structure  
- `Attitude.h/c` - Attitude data structure

### Ordered Resources (Sensors)
- `PositionSensor.h/c` - Position sensor with ordered locking
- `VelocitySensor.h/c` - Velocity sensor with ordered locking
- `AttitudeSensor.h/c` - Attitude sensor with ordered locking

### Resource Clients
- `KinematicModelClient.h/c` - Example client that uses all sensors

### Demo and Build
- `main.c` - Demonstration program
- `Makefile` - Build configuration

## Building and Running

### Prerequisites
- GCC compiler
- Make utility

### Build Commands
```bash
# Build the demo
make all

# Clean build artifacts
make clean

# Build and run the demo
make run

# Show help
make help
```

### Windows PowerShell
If using PowerShell on Windows, you may need to use:
```powershell
# Build
mingw32-make all

# Run
./ordered_locking_demo.exe
```

## How It Works

### Successful Locking Sequence
1. Client locks PositionSensor (ID=1)
2. Client locks VelocitySensor (ID=2) 
3. Client locks AttitudeSensor (ID=3)
4. Client processes data
5. Client releases resources (order doesn't matter for release)

### Deadlock Prevention
- ResourceList checks that each new lock request has an ID greater than all currently locked IDs
- If a client tries to lock resources out of order, the lock is denied with error code `POORLY_ORDERED_ACCESS`
- This prevents circular waiting conditions that could cause deadlock

### Error Codes
- `0` - Success
- `POORLY_ORDERED_ACCESS (1)` - Attempted to lock resource out of order
- `DUPLICATED_IDS (2)` - Attempted to lock resource with duplicate ID

## Usage Example

```c
// Create and setup sensors with proper resource IDs
PositionSensor* posSensor = PositionSensor_Create();  // ID = 1
VelocitySensor* velSensor = VelocitySensor_Create();  // ID = 2  
AttitudeSensor* attSensor = AttitudeSensor_Create();  // ID = 3

// Lock in correct order (1, 2, 3)
result = PositionSensor_lockDyadic(posSensor);     // OK
result = VelocitySensor_lockDyadic(velSensor);     // OK
result = AttitudeSensor_lockDyadic(attSensor);     // OK

// Process data...

// Release resources
AttitudeSensor_releaseDyadic(attSensor);
VelocitySensor_releaseDyadic(velSensor);
PositionSensor_releaseDyadic(posSensor);
```

## Design Decisions

1. **Resource ID Assignment**: IDs are assigned at design time in the sensor constructors to ensure deterministic ordering
2. **Error Handling**: Functions return error codes to indicate ordering violations
3. **Resource Release**: Resources can be released in any order since this doesn't affect deadlock prevention
4. **Single ResourceList**: One global ResourceList instance ensures consistent ordering across the entire application

## Benefits

- **Deadlock Prevention**: Eliminates possibility of circular waiting
- **Deterministic**: Predictable resource allocation behavior
- **Flexible**: Supports both monadic (internal locking) and dyadic (external locking) operations
- **Scalable**: Can handle multiple resources with proper ID assignment

## Limitations

- **Design Time Analysis**: Requires careful resource ID assignment during design
- **Blocking**: May cause more blocking than other approaches if resources are not accessed in optimal order
- **Discipline Required**: Developers must follow the ordering discipline consistently
