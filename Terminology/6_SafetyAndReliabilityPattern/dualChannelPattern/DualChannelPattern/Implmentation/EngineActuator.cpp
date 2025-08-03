#include "EngineActuator.h"
#include <iostream>
#include <algorithm>

EngineActuator::EngineActuator(double minPower, double maxPower)
    : operational(false), currentOutput(0.0), minOutput(minPower), maxOutput(maxPower) {
}

void EngineActuator::actuate(double value) {
    if (!operational) {
        std::cerr << "Engine Actuator: Cannot actuate - not operational" << std::endl;
        return;
    }

    double clampedValue = clampOutput(value);
    currentOutput = clampedValue;
    
    std::cout << "Engine Actuator: Setting engine output to " << (clampedValue * 100.0) << "%" << std::endl;
    
    // In real implementation, this would send commands to actual engine hardware
}

bool EngineActuator::initialize() {
    std::cout << "Initializing Engine Actuator..." << std::endl;
    
    // Validate output limits
    if (minOutput < 0.0 || maxOutput > 1.0 || minOutput > maxOutput) {
        std::cerr << "Invalid output limits: min=" << minOutput << ", max=" << maxOutput << std::endl;
        return false;
    }
    
    currentOutput = 0.0;
    operational = true;
    
    std::cout << "Engine Actuator initialized successfully" << std::endl;
    return true;
}

bool EngineActuator::isOperational() {
    return operational;
}

const char* EngineActuator::getActuatorType() const {
    return "Engine Actuator";
}

void EngineActuator::stop() {
    currentOutput = 0.0;
    std::cout << "Engine Actuator: Emergency stop - engine output set to 0%" << std::endl;
    
    // In real implementation, this would immediately stop the engine
}

double EngineActuator::getCurrentOutput() const {
    return currentOutput;
}

void EngineActuator::setOutputLimits(double minPower, double maxPower) {
    if (minPower >= 0.0 && maxPower <= 1.0 && minPower <= maxPower) {
        minOutput = minPower;
        maxOutput = maxPower;
    }
}

void EngineActuator::simulateFailure() {
    operational = false;
    std::cout << "Engine Actuator failure simulated" << std::endl;
}

void EngineActuator::restoreOperation() {
    operational = true;
    std::cout << "Engine Actuator operation restored" << std::endl;
}

double EngineActuator::clampOutput(double value) {
    return std::clamp(value, minOutput, maxOutput);
}
