#ifndef MOTOR_PROXY_HPP
#define MOTOR_PROXY_HPP

#include <cstdint>
#include <iostream>

// Enumeration for motor direction
enum class MotorDirection {
    OFF = 0,
    FORWARD = 1,
    REVERSE = 2
};

// Enumeration for motor state/error status
enum class MotorState {
    OK = 0,
    SPEED_ERROR = 1,
    DIRECTION_ERROR = 2,
    HARDWARE_ERROR = 4,
    COMMUNICATION_ERROR = 8
};

// Structure representing native motor register format
struct MotorRegister {
    uint16_t speed : 12;        // 12 bits for speed (0-4095)
    uint16_t direction : 2;     // 2 bits for direction
    uint16_t enable : 1;        // 1 bit for enable/disable
    uint16_t reserved : 1;      // 1 bit reserved
};

class MotorProxy {
private:
    // Hardware address - in real implementation this would point to memory-mapped hardware
    void* deviceAddr;
    
    // Motor configuration parameters
    uint32_t memoryMappedAddress;
    double rotaryArmLength;
    bool isInitialized;
    bool isEnabled;
    
    // Current motor state
    MotorDirection currentDirection;
    uint16_t currentSpeed;
    uint8_t errorStatus;
    
    // Private data formatting functions
    MotorRegister marshal(uint16_t speed, MotorDirection direction, bool enable);
    void unmarshal(const MotorRegister& nativeData, uint16_t& speed, MotorDirection& direction, bool& enable);
    
    // Helper function to simulate hardware read/write
    MotorRegister readFromHardware();
    void writeToHardware(const MotorRegister& data);
    
    // Helper function to adjust speed based on arm length
    uint16_t adjustSpeedForArmLength(uint16_t requestedSpeed);

public:
    // Constructor
    MotorProxy();
    
    // Destructor
    ~MotorProxy();
    
    // Motor Management Functions
    bool configure(uint32_t memoryAddress, double armLength);
    bool disable();
    bool enable();
    bool initialize();
    
    // Motor Status Functions (access functions)
    MotorDirection accessMotorDirection();
    uint16_t accessMotorSpeed();
    MotorState accessMotorState();
    
    // Motor Control Functions (mutate functions)
    bool writeMotorSpeed(uint16_t speed);
    bool writeMotorDirection(MotorDirection direction);
    
    // Motor Error Management Functions
    bool clearErrorStatus();
    
    // Utility functions
    bool isMotorInitialized() const;
    bool isMotorEnabled() const;
    double getArmLength() const;
};

#endif // MOTOR_PROXY_HPP
