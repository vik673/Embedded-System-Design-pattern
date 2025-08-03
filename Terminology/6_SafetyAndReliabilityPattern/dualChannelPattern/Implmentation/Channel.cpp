#include "Channel.h"
#include <iostream>
#include <cmath>
#include <limits>

Channel::Channel(const std::string& id) : channelId(id), enabled(false), initialized(false) {
}

Channel::~Channel() {
    stop();
}

bool Channel::initialize(std::unique_ptr<SensorDeviceDriver> sensorDriver,
                        std::shared_ptr<ActuatorDeviceDriver> actuatorDriver) {
    if (!sensorDriver || !actuatorDriver) {
        std::cerr << "Channel " << channelId << ": Invalid sensor or actuator driver" << std::endl;
        return false;
    }

    sensor = std::move(sensorDriver);
    actuator = actuatorDriver;

    // Initialize components
    if (!sensor->initialize()) {
        std::cerr << "Channel " << channelId << ": Failed to initialize sensor" << std::endl;
        return false;
    }

    if (!actuator->initialize()) {
        std::cerr << "Channel " << channelId << ": Failed to initialize actuator" << std::endl;
        return false;
    }

    initialized = true;
    buildProcessingChain();
    
    std::cout << "Channel " << channelId << " initialized successfully" << std::endl;
    return true;
}

void Channel::addTransform(std::shared_ptr<AbstractDataTransform> transform) {
    if (transform) {
        transforms.push_back(transform);
        if (initialized) {
            buildProcessingChain();
        }
    }
}

void Channel::enable() {
    if (initialized && isOperational()) {
        enabled = true;
        std::cout << "Channel " << channelId << " enabled" << std::endl;
    } else {
        std::cerr << "Channel " << channelId << ": Cannot enable - not initialized or not operational" << std::endl;
    }
}

void Channel::disable() {
    enabled = false;
    if (actuator) {
        actuator->stop();
    }
    std::cout << "Channel " << channelId << " disabled" << std::endl;
}

bool Channel::isEnabled() const {
    return enabled;
}

bool Channel::isInitialized() const {
    return initialized;
}

bool Channel::processChannel() {
    if (!enabled || !initialized) {
        return false;
    }

    if (!isOperational()) {
        std::cerr << "Channel " << channelId << ": Components not operational, disabling channel" << std::endl;
        disable();
        return false;
    }

    try {
        double sensorData = sensor->readSensor();
        
        if (std::isnan(sensorData)) {
            std::cerr << "Channel " << channelId << ": Invalid sensor data" << std::endl;
            return false;
        }

        // Start the processing chain
        if (!transforms.empty()) {
            transforms[0]->executeChain(sensorData);
        } else {
            // No transforms, send directly to actuator
            actuator->actuate(sensorData);
        }

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Channel " << channelId << ": Exception during processing: " << e.what() << std::endl;
        return false;
    }
}

double Channel::getCurrentSensorReading() {
    if (!sensor || !enabled) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    
    return sensor->readSensor();
}

const std::string& Channel::getChannelId() const {
    return channelId;
}

bool Channel::isOperational() {
    if (!initialized) {
        return false;
    }

    return sensor->isOperational() && actuator->isOperational();
}

void Channel::stop() {
    disable();
}

void Channel::buildProcessingChain() {
    if (transforms.empty()) {
        return;
    }

    // Link transforms in sequence
    for (size_t i = 0; i < transforms.size() - 1; ++i) {
        transforms[i]->setNextTransform(transforms[i + 1]);
    }

    // Last transform connects to actuator
    if (!transforms.empty()) {
        transforms.back()->setOutputDriver(actuator);
    }
}
