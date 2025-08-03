#include "Channel.h"
#include <stdexcept>

Channel::Channel() : isInitialized(false) {
}

Channel::~Channel() {
    cleanup();
}

void Channel::initialize(std::unique_ptr<SensorDeviceDriver> sensorDriver,
                        std::unique_ptr<ActuatorDeviceDriver> actuatorDriver) {
    if (!sensorDriver || !actuatorDriver) {
        throw std::invalid_argument("Sensor and actuator drivers cannot be null");
    }
    
    sensor = std::move(sensorDriver);
    actuator = std::move(actuatorDriver);
    
    // Initialize relations if we have transforms
    if (!transforms.empty()) {
        initializeRelations();
    }
    
    isInitialized = validateConfiguration();
}

void Channel::addTransform(std::unique_ptr<AbstractDataTransform> transform) {
    if (!transform) {
        throw std::invalid_argument("Transform cannot be null");
    }
    
    transforms.push_back(std::move(transform));
    
    // Re-initialize relations if channel is already initialized
    if (isInitialized && sensor && actuator) {
        initializeRelations();
        isInitialized = validateConfiguration();
    }
}

void Channel::processChannel() {
    if (!isInitialized) {
        throw std::runtime_error("Channel not properly initialized");
    }
    
    // Start the data processing pipeline
    sensor->startProcessing();
}

double Channel::getCurrentSensorReading() {
    if (!sensor) {
        throw std::runtime_error("No sensor available");
    }
    
    return sensor->acquireData();
}

double Channel::getCurrentActuatorValue() {
    if (!actuator) {
        throw std::runtime_error("No actuator available");
    }
    
    return actuator->getCurrentValue();
}

bool Channel::getInitializationStatus() const {
    return isInitialized;
}

size_t Channel::getTransformCount() const {
    return transforms.size();
}

void Channel::setChannelEnabled(bool enabled) {
    if (actuator) {
        actuator->setEnabled(enabled);
    }
}

void Channel::cleanup() {
    // Clear all components
    sensor.reset();
    transforms.clear();
    actuator.reset();
    isInitialized = false;
}

void Channel::initializeRelations() {
    if (!sensor || !actuator) {
        return;
    }
    
    if (transforms.empty()) {
        // Direct connection from sensor to actuator (no transformations)
        // This would require a different design or adapter
        return;
    }
    
    // Set up the chain of transformations
    sensor->setFirstTransform(transforms[0].get());
    
    // Link transforms in sequence
    for (size_t i = 0; i < transforms.size() - 1; ++i) {
        transforms[i]->setNextTransform(transforms[i + 1].get());
    }
    
    // Connect the last transform to the actuator
    if (!transforms.empty()) {
        transforms.back()->setActuatorDriver(actuator.get());
    }
}

bool Channel::validateConfiguration() {
    if (!sensor || !actuator) {
        return false;
    }
    
    // Check that the chain is properly connected
    if (!transforms.empty()) {
        // Verify sensor is connected to first transform
        if (sensor->getFirstTransform() != transforms[0].get()) {
            return false;
        }
        
        // Verify transform chain is properly linked
        for (size_t i = 0; i < transforms.size() - 1; ++i) {
            if (transforms[i]->getNextTransform() != transforms[i + 1].get()) {
                return false;
            }
        }
        
        // Verify last transform is connected to actuator
        if (transforms.back()->getActuatorDriver() != actuator.get()) {
            return false;
        }
    }
    
    return true;
}
