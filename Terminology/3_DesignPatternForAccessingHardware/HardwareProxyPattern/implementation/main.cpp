#include "MotorProxy.hpp"
#include <iostream>
#include <iomanip>

void printMotorStatus(MotorProxy& motor) {
    std::cout << "\n=== Motor Status ===" << std::endl;
    std::cout << "Initialized: " << (motor.isMotorInitialized() ? "Yes" : "No") << std::endl;
    std::cout << "Enabled: " << (motor.isMotorEnabled() ? "Yes" : "No") << std::endl;
    std::cout << "Arm Length: " << motor.getArmLength() << std::endl;
    std::cout << "Current Speed: " << motor.accessMotorSpeed() << std::endl;
    
    MotorDirection dir = motor.accessMotorDirection();
    std::cout << "Current Direction: ";
    switch (dir) {
        case MotorDirection::OFF:
            std::cout << "OFF" << std::endl;
            break;
        case MotorDirection::FORWARD:
            std::cout << "FORWARD" << std::endl;
            break;
        case MotorDirection::REVERSE:
            std::cout << "REVERSE" << std::endl;
            break;
    }
    
    MotorState state = motor.accessMotorState();
    std::cout << "Error Status: " << static_cast<int>(state);
    if (state == MotorState::OK) {
        std::cout << " (OK)" << std::endl;
    } else {
        std::cout << " (ERROR)" << std::endl;
    }
    std::cout << "===================" << std::endl;
}

int main() {
    std::cout << "Hardware Proxy Pattern Demo - Motor Control" << std::endl;
    std::cout << "===========================================" << std::endl;
    
    // Create a motor proxy instance
    MotorProxy motor;
    
    std::cout << "\n1. Initial motor state:" << std::endl;
    printMotorStatus(motor);
    
    // Configure the motor
    std::cout << "\n2. Configuring motor..." << std::endl;
    bool success = motor.configure(0x1000, 2.5);  // Memory address 0x1000, arm length 2.5
    if (success) {
        std::cout << "Motor configuration successful!" << std::endl;
    } else {
        std::cout << "Motor configuration failed!" << std::endl;
        return -1;
    }
    
    // Initialize the motor
    std::cout << "\n3. Initializing motor..." << std::endl;
    success = motor.initialize();
    if (success) {
        std::cout << "Motor initialization successful!" << std::endl;
    } else {
        std::cout << "Motor initialization failed!" << std::endl;
        return -1;
    }
    
    printMotorStatus(motor);
    
    // Set motor speed and direction
    std::cout << "\n4. Setting motor parameters..." << std::endl;
    motor.writeMotorSpeed(1000);
    motor.writeMotorDirection(MotorDirection::FORWARD);
    
    printMotorStatus(motor);
    
    // Enable the motor
    std::cout << "\n5. Enabling motor..." << std::endl;
    motor.enable();
    
    printMotorStatus(motor);
    
    // Change motor direction
    std::cout << "\n6. Changing motor direction to REVERSE..." << std::endl;
    motor.writeMotorDirection(MotorDirection::REVERSE);
    
    printMotorStatus(motor);
    
    // Change motor speed
    std::cout << "\n7. Changing motor speed to 2000..." << std::endl;
    motor.writeMotorSpeed(2000);
    
    printMotorStatus(motor);
    
    // Test error handling - try to set invalid speed
    std::cout << "\n8. Testing error handling - setting invalid speed (5000)..." << std::endl;
    success = motor.writeMotorSpeed(5000);
    if (!success) {
        std::cout << "Speed setting failed as expected (speed too high)" << std::endl;
    }
    
    printMotorStatus(motor);
    
    // Clear errors
    std::cout << "\n9. Clearing error status..." << std::endl;
    motor.clearErrorStatus();
    
    printMotorStatus(motor);
    
    // Disable the motor
    std::cout << "\n10. Disabling motor..." << std::endl;
    motor.disable();
    
    printMotorStatus(motor);
    
    // Test different arm lengths
    std::cout << "\n11. Testing different arm lengths..." << std::endl;
    motor.configure(0x1000, 1.0);  // Arm length 1.0
    motor.initialize();
    motor.writeMotorSpeed(1000);
    motor.enable();
    std::cout << "With arm length 1.0:" << std::endl;
    printMotorStatus(motor);
    
    motor.configure(0x1000, 5.0);  // Arm length 5.0
    motor.initialize();
    motor.writeMotorSpeed(1000);
    motor.enable();
    std::cout << "With arm length 5.0:" << std::endl;
    printMotorStatus(motor);
    
    std::cout << "\nDemo completed successfully!" << std::endl;
    
    return 0;
}
