#include "OpticalWheelSpeedSensor.h"
#include <iostream>
#include <cmath>
#include <limits>

OpticalWheelSpeedSensor::OpticalWheelSpeedSensor(double circumference)
    : wheelCircumference(circumference), operational(false), rng(std::random_device{}()),
      noise_dist(-0.1, 0.1), frequency_dist(0.5, 10.0) {
}

double OpticalWheelSpeedSensor::readSensor() {
    if (!operational) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    // Read optical frequency (marks per second)
    double frequency = readOpticalFrequency();
    
    // Convert frequency to speed: speed = frequency * circumference
    double speed = frequency * wheelCircumference;
    
    // Add some noise to simulate real sensor
    speed += noise_dist(rng);
    
    return std::max(0.0, speed); // Speed cannot be negative
}

bool OpticalWheelSpeedSensor::initialize() {
    std::cout << "Initializing Optical Wheel Speed Sensor..." << std::endl;
    
    // Simulate initialization process
    if (wheelCircumference <= 0) {
        std::cerr << "Invalid wheel circumference: " << wheelCircumference << std::endl;
        return false;
    }
    
    operational = true;
    std::cout << "Optical Wheel Speed Sensor initialized successfully" << std::endl;
    return true;
}

bool OpticalWheelSpeedSensor::isOperational() {
    return operational;
}

const char* OpticalWheelSpeedSensor::getSensorType() const {
    return "Optical Wheel Speed Sensor";
}

void OpticalWheelSpeedSensor::setWheelCircumference(double circumference) {
    if (circumference > 0) {
        wheelCircumference = circumference;
    }
}

void OpticalWheelSpeedSensor::simulateFailure() {
    operational = false;
    std::cout << "Optical Wheel Speed Sensor failure simulated" << std::endl;
}

void OpticalWheelSpeedSensor::restoreOperation() {
    operational = true;
    std::cout << "Optical Wheel Speed Sensor operation restored" << std::endl;
}

double OpticalWheelSpeedSensor::readOpticalFrequency() {
    // Simulate reading frequency from optical sensor
    // In real implementation, this would read from actual hardware
    return frequency_dist(rng);
}
