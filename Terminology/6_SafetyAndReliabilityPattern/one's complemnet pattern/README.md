# One's Complement Pattern Implementation

## Overview

This project implements the **One's Complement Pattern**, a detailed design pattern for detecting memory corruption in embedded systems. The pattern stores critical data twice - once in normal form and once in bit-wise inverted (one's complement) form. When data is retrieved, the inverted copy is re-inverted and compared with the normal copy to detect corruption.

## Pattern Description

### Purpose
- **Detect memory corruption** caused by EMI, heat, radiation, hardware faults, or software errors
- **Protect critical data** in embedded systems where data integrity is crucial
- **Provide error handling** when corruption is detected

### How It Works
1. **Storage**: Critical data is stored in two forms:
   - Normal form (original data)
   - Inverted form (bit-wise complement using `~` operator)

2. **Retrieval**: When data is accessed:
   - The inverted copy is re-inverted (`~~data = data`)
   - Re-inverted data is compared with normal data
   - If they match → data is valid
   - If they don't match → corruption detected → error handling triggered

3. **Error Handling**: When corruption is detected:
   - Error handler is called
   - Alarm is raised through AlarmManager
   - System can take appropriate action

## Architecture

### Class Diagram
The implementation includes the following key components:

- **DataClient**: Uses the protected data element
- **OwnShipAttitude**: Implements the One's Complement Pattern
- **AttitudeDataType**: Contains the critical data (roll, pitch, yaw)
- **AlarmManager**: Handles error reporting and alarm management

### Sequence Diagram
The sequence diagram shows the interaction flow for:
- Normal data operations
- Memory corruption detection
- Error handling and alarm generation

## File Structure

```
one's complement pattern/
├── *.puml                          # UML diagram source files
├── *.h                            # Header files
├── *.c                            # Implementation files
├── OnesComplementDemo.c           # Demonstration program
├── Makefile                       # Build configuration
└── README.md                      # This file
```

### Core Files

1. **AttitudeDataType.h/.c**
   - Defines the critical data structure (roll, pitch, yaw)
   - Provides basic operations for attitude data

2. **AlarmManager.h/.c**
   - Manages system alarms and notifications
   - Handles multiple alarm types including memory faults

3. **OwnShipAttitude.h/.c**
   - Core implementation of One's Complement Pattern
   - Stores data in both normal and inverted forms
   - Provides corruption detection and error handling

4. **OnesComplementDemo.c**
   - Comprehensive demonstration program
   - Shows normal operation, corruption detection, and error handling

## Building and Running

### Prerequisites
- GCC compiler
- Make utility
- (Optional) PlantUML for diagram generation

### Build Commands

```bash
# Build the project
make

# Build and run the demonstration
make run

# Clean build artifacts
make clean

# Generate UML diagrams (requires PlantUML)
make diagrams

# Show help
make help
```

### Windows PowerShell Commands
```powershell
# Compile manually if make is not available
gcc -Wall -Wextra -std=c99 -g -O0 -c *.c
gcc -o OnesComplementDemo *.o

# Run the demonstration
./OnesComplementDemo
```

## Demonstration Features

The demo program showcases:

1. **Bit Inversion Demonstration**
   - Shows how one's complement works with various integer values
   - Demonstrates that `~~x = x` (double inversion returns original)

2. **Normal Operation**
   - Setting attitude data
   - Successful retrieval with integrity verification
   - No alarms generated

3. **Memory Corruption Detection**
   - Simulates memory corruption
   - Shows corruption detection in action
   - Demonstrates alarm generation

4. **Data Integrity Validation**
   - Real-time integrity checking
   - Before and after corruption scenarios

## Key Features

### Memory Corruption Detection
- **Single-bit errors**: Detects when any bit in the data is flipped
- **Multiple-bit errors**: Can detect many types of multi-bit corruption
- **Hardware faults**: Identifies stuck bits, address line shorts, etc.
- **Environmental factors**: Detects corruption from EMI, heat, radiation

### Error Handling
- **Alarm generation**: Automatic alarm creation when corruption detected
- **Error codes**: Specific alarm codes for different fault types
- **Logging**: Console output for debugging and monitoring
- **Recovery options**: Framework for implementing recovery strategies

### Performance Characteristics
- **Memory overhead**: 2x storage requirement for protected data
- **CPU overhead**: Additional processing for inversion and comparison
- **Detection capability**: High reliability for single-location faults

## Usage Example

```c
#include "OwnShipAttitude.h"
#include "AlarmManager.h"

int main() {
    // Create instances
    AlarmManager* alarmMgr = AlarmManager_Create();
    OwnShipAttitude* attitude = OwnShipAttitude_Create();
    
    // Associate alarm manager
    OwnShipAttitude_setItsAlarmManager(attitude, alarmMgr);
    
    // Set attitude data
    AttitudeDataType data;
    AttitudeDataType_Set(&data, 15, -5, 270);
    OwnShipAttitude_setAttitude(attitude, data);
    
    // Retrieve data (with automatic corruption detection)
    AttitudeDataType retrieved;
    int result = OwnShipAttitude_getAttitude(attitude, &retrieved);
    
    if (result) {
        printf("Data valid: roll=%d, pitch=%d, yaw=%d\n",
               retrieved.roll, retrieved.pitch, retrieved.yaw);
    } else {
        printf("Corruption detected!\n");
    }
    
    // Cleanup
    OwnShipAttitude_Destroy(attitude);
    AlarmManager_Destroy(alarmMgr);
    
    return 0;
}
```

## Design Patterns Used

1. **One's Complement Pattern** (Primary)
   - Memory corruption detection through data redundancy
   - Bit-wise inversion for integrity checking

2. **Observer Pattern** (AlarmManager)
   - Decoupled error notification system
   - Multiple alarm subscribers possible

3. **Factory Pattern** (Create/Destroy functions)
   - Consistent object creation and cleanup
   - Memory management encapsulation

## Advantages

- **High Detection Rate**: Can detect most single-bit and many multi-bit errors
- **Simple Implementation**: Easy to understand and implement
- **Real-time Detection**: Errors detected immediately upon data access
- **Minimal Dependencies**: No complex libraries required
- **Embedded-Friendly**: Suitable for resource-constrained environments

## Limitations

- **Memory Overhead**: Requires 2x storage for protected data
- **Performance Impact**: Additional processing on every data access
- **Limited Scope**: Best for small, critical data sets
- **No Correction**: Only detects corruption, doesn't correct it

## Related Patterns

- **CRC Pattern**: Alternative for large data structures where memory overhead is prohibitive
- **Checksum Pattern**: Simpler but less reliable corruption detection
- **Hamming Code Pattern**: Can both detect and correct certain types of errors

## Testing

The implementation includes comprehensive testing through the demo program:

- **Unit-level testing**: Individual function verification
- **Integration testing**: Component interaction validation
- **Corruption simulation**: Artificial corruption injection for testing
- **Edge case handling**: NULL pointer and boundary condition testing

## Future Enhancements

Possible improvements to consider:

1. **Multi-bit Error Detection**: Enhanced algorithms for complex corruption patterns
2. **Error Correction**: Add capability to correct detected errors
3. **Performance Optimization**: Reduce overhead for high-frequency operations
4. **Configuration Options**: Runtime configuration of protection levels
5. **Statistics Collection**: Track corruption frequency and patterns

## References

- Embedded System Design Patterns (Chapter 6)
- Safety-Critical Systems Design Guidelines
- Memory Protection Techniques for Embedded Systems
- Fault-Tolerant Computing Principles

---

This implementation demonstrates a robust approach to memory corruption detection suitable for safety-critical embedded systems where data integrity is paramount.
