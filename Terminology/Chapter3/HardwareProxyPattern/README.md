# Hardware Proxy Pattern Implementation

## Overview
This implementation demonstrates the Hardware Proxy Pattern as described in embedded systems design patterns. The pattern provides a clean interface to hardware devices while hiding the complexities of hardware communication, data marshaling/unmarshaling, and device-specific protocols.

## Files Structure
- `MotorProxy.hpp` - Header file containing the motor proxy class declaration
- `MotorProxy.cpp` - Implementation of the motor proxy class
- `main.cpp` - Demo application showing how to use the motor proxy

## Key Components

### MotorProxy Class
The main class that implements the Hardware Proxy Pattern with the following key features:

#### Public Interface (Motor Management Functions)
- `configure()` - Sets up memory-mapped address and rotary arm length
- `initialize()` - Initializes motor to default values (must be called first)
- `enable()` - Turns motor on with current set values
- `disable()` - Turns motor off but keeps set values intact

#### Access Functions (Motor Status)
- `accessMotorDirection()` - Returns current motor direction (OFF, FORWARD, REVERSE)
- `accessMotorSpeed()` - Returns current motor speed
- `accessMotorState()` - Returns error status

#### Mutate Functions (Motor Control)
- `writeMotorSpeed()` - Sets motor speed (adjusted for arm length)
- `writeMotorDirection()` - Sets motor direction

#### Error Management
- `clearErrorStatus()` - Clears all error bits

#### Private Implementation Details
- `marshal()` - Converts presentation format to native hardware format
- `unmarshal()` - Converts native hardware format to presentation format
- `deviceAddr` - Hardware address pointer (void*)
- Data validation and error handling

## Pattern Features Implemented

### 1. Hardware Abstraction
- The client interacts with simple, high-level functions
- Hardware-specific details are completely hidden
- Memory-mapped register access is abstracted away

### 2. Data Format Conversion
- **Marshal**: Converts user-friendly data to hardware register format
- **Unmarshal**: Converts hardware register format back to user-friendly data
- Bit-packing for efficient hardware communication

### 3. Device Configuration
- Memory-mapped address configuration
- Rotary arm length consideration for speed calculations
- Initialization and state management

### 4. Error Handling
- Comprehensive error status tracking
- Input validation
- Safe error recovery

### 5. State Management
- Tracks initialization and enable states
- Maintains current motor parameters
- Ensures proper device lifecycle

## Hardware Register Format
The implementation uses a bit-packed structure for efficient hardware communication:
```cpp
struct MotorRegister {
    uint16_t speed : 12;        // 12 bits for speed (0-4095)
    uint16_t direction : 2;     // 2 bits for direction
    uint16_t enable : 1;        // 1 bit for enable/disable
    uint16_t reserved : 1;      // 1 bit reserved
};
```

## Compilation and Usage

### To compile:
```bash
g++ -std=c++11 -o motor_demo main.cpp MotorProxy.cpp
```

### To run:
```bash
./motor_demo
```

## Demo Features
The demo application demonstrates:
1. Motor configuration and initialization
2. Speed and direction control
3. Enable/disable functionality
4. Error handling and validation
5. Different arm length configurations
6. Status monitoring and reporting

## Benefits of This Pattern
1. **Encapsulation**: Hardware details are completely hidden from clients
2. **Reusability**: Same interface can work with different hardware implementations
3. **Maintainability**: Changes to hardware interface don't affect client code
4. **Safety**: Input validation and error handling protect against invalid operations
5. **Performance**: Efficient bit-packing for hardware communication

This implementation follows embedded systems best practices and provides a robust foundation for hardware device control in embedded applications.
