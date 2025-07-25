#include "MotorProxy.hpp"
#include <cstring>
#include <stdexcept>

// Constructor
MotorProxy::MotorProxy() 
    : deviceAddr(nullptr)
    , memoryMappedAddress(0)
    , rotaryArmLength(1.0)
    , isInitialized(false)
    , isEnabled(false)
    , currentDirection(MotorDirection::OFF)
    , currentSpeed(0)
    , errorStatus(0) {
}

// Destructor
MotorProxy::~MotorProxy() {
    if (isEnabled) {
        disable();
    }
}

// Configure the motor proxy with hardware address and arm length
bool MotorProxy::configure(uint32_t memoryAddress, double armLength) {
    try {
        if (armLength <= 0.0) {
            errorStatus |= static_cast<uint8_t>(MotorState::SPEED_ERROR);
            return false;
        }
        
        memoryMappedAddress = memoryAddress;
        rotaryArmLength = armLength;
        
        // In real implementation, this would map to actual hardware memory
        deviceAddr = reinterpret_cast<void*>(memoryAddress);
        
        std::cout << "Motor configured - Address: 0x" << std::hex << memoryAddress 
                  << ", Arm Length: " << std::dec << armLength << std::endl;
        
        return true;
    } catch (...) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        return false;
    }
}

// Disable the motor but keep set values intact
bool MotorProxy::disable() {
    try {
        if (!isInitialized) {
            errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
            return false;
        }
        
        // Create register data with enable bit set to false
        MotorRegister regData = marshal(currentSpeed, currentDirection, false);
        writeToHardware(regData);
        
        isEnabled = false;
        std::cout << "Motor disabled" << std::endl;
        
        return true;
    } catch (...) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        return false;
    }
}

// Enable the motor with current set values
bool MotorProxy::enable() {
    try {
        if (!isInitialized) {
            errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
            return false;
        }
        
        // Create register data with enable bit set to true
        MotorRegister regData = marshal(currentSpeed, currentDirection, true);
        writeToHardware(regData);
        
        isEnabled = true;
        std::cout << "Motor enabled with speed: " << currentSpeed 
                  << ", direction: " << static_cast<int>(currentDirection) << std::endl;
        
        return true;
    } catch (...) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        return false;
    }
}

// Initialize the motor to default values
bool MotorProxy::initialize() {
    try {
        if (deviceAddr == nullptr) {
            errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
            return false;
        }
        
        // Set default values
        currentSpeed = 0;
        currentDirection = MotorDirection::OFF;
        isEnabled = false;
        errorStatus = 0;
        
        // Write default values to hardware
        MotorRegister regData = marshal(currentSpeed, currentDirection, isEnabled);
        writeToHardware(regData);
        
        isInitialized = true;
        std::cout << "Motor initialized to default values" << std::endl;
        
        return true;
    } catch (...) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        isInitialized = false;
        return false;
    }
}

// Access motor direction
MotorDirection MotorProxy::accessMotorDirection() {
    if (!isInitialized) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        return MotorDirection::OFF;
    }
    
    try {
        // Read current state from hardware
        MotorRegister regData = readFromHardware();
        uint16_t speed;
        MotorDirection direction;
        bool enabled;
        
        unmarshal(regData, speed, direction, enabled);
        currentDirection = direction;
        
        return currentDirection;
    } catch (...) {
        errorStatus |= static_cast<uint8_t>(MotorState::COMMUNICATION_ERROR);
        return MotorDirection::OFF;
    }
}

// Access motor speed
uint16_t MotorProxy::accessMotorSpeed() {
    if (!isInitialized) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        return 0;
    }
    
    try {
        // Read current state from hardware
        MotorRegister regData = readFromHardware();
        uint16_t speed;
        MotorDirection direction;
        bool enabled;
        
        unmarshal(regData, speed, direction, enabled);
        currentSpeed = speed;
        
        return currentSpeed;
    } catch (...) {
        errorStatus |= static_cast<uint8_t>(MotorState::COMMUNICATION_ERROR);
        return 0;
    }
}

// Access motor state (error status)
MotorState MotorProxy::accessMotorState() {
    return static_cast<MotorState>(errorStatus);
}

// Write motor speed
bool MotorProxy::writeMotorSpeed(uint16_t speed) {
    if (!isInitialized) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        return false;
    }
    
    try {
        // Validate speed range (12-bit value)
        if (speed > 4095) {
            errorStatus |= static_cast<uint8_t>(MotorState::SPEED_ERROR);
            return false;
        }
        
        // Adjust speed for arm length
        uint16_t adjustedSpeed = adjustSpeedForArmLength(speed);
        
        // Update current speed
        currentSpeed = adjustedSpeed;
        
        // If motor is enabled, write to hardware immediately
        if (isEnabled) {
            MotorRegister regData = marshal(currentSpeed, currentDirection, true);
            writeToHardware(regData);
        }
        
        std::cout << "Motor speed set to: " << currentSpeed << std::endl;
        return true;
    } catch (...) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        return false;
    }
}

// Write motor direction
bool MotorProxy::writeMotorDirection(MotorDirection direction) {
    if (!isInitialized) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        return false;
    }
    
    try {
        // Validate direction
        if (direction != MotorDirection::OFF && 
            direction != MotorDirection::FORWARD && 
            direction != MotorDirection::REVERSE) {
            errorStatus |= static_cast<uint8_t>(MotorState::DIRECTION_ERROR);
            return false;
        }
        
        // Update current direction
        currentDirection = direction;
        
        // If motor is enabled, write to hardware immediately
        if (isEnabled) {
            MotorRegister regData = marshal(currentSpeed, currentDirection, true);
            writeToHardware(regData);
        }
        
        std::cout << "Motor direction set to: " << static_cast<int>(currentDirection) << std::endl;
        return true;
    } catch (...) {
        errorStatus |= static_cast<uint8_t>(MotorState::HARDWARE_ERROR);
        return false;
    }
}

// Clear error status
bool MotorProxy::clearErrorStatus() {
    errorStatus = 0;
    std::cout << "Error status cleared" << std::endl;
    return true;
}

// Marshal function: converts presentation format to native format
MotorRegister MotorProxy::marshal(uint16_t speed, MotorDirection direction, bool enable) {
    MotorRegister regData;
    regData.speed = speed & 0x0FFF;  // Mask to 12 bits
    regData.direction = static_cast<uint16_t>(direction) & 0x03;  // Mask to 2 bits
    regData.enable = enable ? 1 : 0;
    regData.reserved = 0;
    
    return regData;
}

// Unmarshal function: converts native format to presentation format
void MotorProxy::unmarshal(const MotorRegister& nativeData, uint16_t& speed, 
                          MotorDirection& direction, bool& enable) {
    speed = nativeData.speed;
    direction = static_cast<MotorDirection>(nativeData.direction);
    enable = (nativeData.enable == 1);
}

// Simulate reading from hardware
MotorRegister MotorProxy::readFromHardware() {
    // In real implementation, this would read from actual hardware memory
    // For simulation, we'll return the current marshaled state
    return marshal(currentSpeed, currentDirection, isEnabled);
}

// Simulate writing to hardware
void MotorProxy::writeToHardware(const MotorRegister& data) {
    // In real implementation, this would write to actual hardware memory
    // For simulation, we'll just print the operation
    std::cout << "Writing to hardware - Speed: " << data.speed 
              << ", Direction: " << data.direction 
              << ", Enable: " << data.enable << std::endl;
}

// Adjust speed based on rotary arm length
uint16_t MotorProxy::adjustSpeedForArmLength(uint16_t requestedSpeed) {
    // Simple adjustment formula: speed = requestedSpeed / armLength
    // This ensures that the tip speed remains constant regardless of arm length
    double adjustedSpeed = static_cast<double>(requestedSpeed) / rotaryArmLength;
    
    // Ensure we don't exceed the maximum speed
    if (adjustedSpeed > 4095.0) {
        adjustedSpeed = 4095.0;
    }
    
    return static_cast<uint16_t>(adjustedSpeed);
}

// Utility functions
bool MotorProxy::isMotorInitialized() const {
    return isInitialized;
}

bool MotorProxy::isMotorEnabled() const {
    return isEnabled;
}

double MotorProxy::getArmLength() const {
    return rotaryArmLength;
}
