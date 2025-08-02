#include "DualChannelPattern.h"
#include <iostream>
#include <cmath>

DualChannelPattern::DualChannelPattern(RedundancyType type, OperationMode mode, double outputTolerance)
    : redundancyType(type), operationMode(mode), tolerance(outputTolerance), faultDetected(false) {
}

DualChannelPattern::~DualChannelPattern() {
    stop();
}

bool DualChannelPattern::initialize(std::shared_ptr<Channel> primary, std::shared_ptr<Channel> secondary) {
    if (!primary || !secondary) {
        std::cerr << "DualChannelPattern: Invalid channel pointers" << std::endl;
        return false;
    }

    primaryChannel = primary;
    secondaryChannel = secondary;

    if (!primaryChannel->isInitialized() || !secondaryChannel->isInitialized()) {
        std::cerr << "DualChannelPattern: Channels must be initialized before dual channel system" << std::endl;
        return false;
    }

    std::cout << "DualChannelPattern initialized with " 
              << (redundancyType == RedundancyType::HOMOGENEOUS ? "homogeneous" : "heterogeneous")
              << " redundancy in "
              << (operationMode == OperationMode::SIMULTANEOUS ? "simultaneous" : "primary-backup")
              << " mode" << std::endl;

    return true;
}

void DualChannelPattern::start() {
    if (!primaryChannel || !secondaryChannel) {
        std::cerr << "DualChannelPattern: Not properly initialized" << std::endl;
        return;
    }

    faultDetected = false;

    if (operationMode == OperationMode::SIMULTANEOUS) {
        // Enable both channels for simultaneous operation
        primaryChannel->enable();
        secondaryChannel->enable();
    } else {
        // Enable only primary channel initially for primary-backup mode
        primaryChannel->enable();
        // Keep secondary disabled but ready
    }

    std::cout << "DualChannelPattern started" << std::endl;
}

void DualChannelPattern::stop() {
    if (primaryChannel) {
        primaryChannel->disable();
    }
    if (secondaryChannel) {
        secondaryChannel->disable();
    }
    std::cout << "DualChannelPattern stopped" << std::endl;
}

bool DualChannelPattern::process() {
    if (!primaryChannel || !secondaryChannel) {
        return false;
    }

    if (operationMode == OperationMode::SIMULTANEOUS) {
        return processSimultaneous();
    } else {
        return processPrimaryBackup();
    }
}

bool DualChannelPattern::isOperational() {
    if (!primaryChannel || !secondaryChannel) {
        return false;
    }

    // System is operational if at least one channel is operational
    return primaryChannel->isOperational() || secondaryChannel->isOperational();
}

void DualChannelPattern::setFaultSafeCallback(std::function<void()> callback) {
    faultSafeCallback = callback;
}

std::shared_ptr<Channel> DualChannelPattern::getActiveChannel() {
    if (primaryChannel && primaryChannel->isEnabled()) {
        return primaryChannel;
    } else if (secondaryChannel && secondaryChannel->isEnabled()) {
        return secondaryChannel;
    }
    return nullptr;
}

DualChannelPattern::RedundancyType DualChannelPattern::getRedundancyType() const {
    return redundancyType;
}

DualChannelPattern::OperationMode DualChannelPattern::getOperationMode() const {
    return operationMode;
}

bool DualChannelPattern::isFaultDetected() const {
    return faultDetected;
}

bool DualChannelPattern::processSimultaneous() {
    // Both channels process simultaneously
    bool primary_success = primaryChannel->processChannel();
    bool secondary_success = secondaryChannel->processChannel();

    if (!primary_success && !secondary_success) {
        // Both channels failed
        std::cerr << "DualChannelPattern: Both channels failed - entering fault-safe state" << std::endl;
        handleFault();
        return false;
    }

    if (!primary_success) {
        std::cerr << "DualChannelPattern: Primary channel failed - switching to secondary only" << std::endl;
        primaryChannel->disable();
        return secondary_success;
    }

    if (!secondary_success) {
        std::cerr << "DualChannelPattern: Secondary channel failed - continuing with primary only" << std::endl;
        secondaryChannel->disable();
        return primary_success;
    }

    // Both channels succeeded - compare outputs if possible
    double primary_output = primaryChannel->getCurrentSensorReading();
    double secondary_output = secondaryChannel->getCurrentSensorReading();

    if (!compareOutputs(primary_output, secondary_output)) {
        std::cerr << "DualChannelPattern: Output mismatch detected - entering fault-safe state" << std::endl;
        handleFault();
        return false;
    }

    return true;
}

bool DualChannelPattern::processPrimaryBackup() {
    // Try primary channel first
    if (primaryChannel->isEnabled() && primaryChannel->isOperational()) {
        if (primaryChannel->processChannel()) {
            return true;
        } else {
            // Primary channel failed, switch to secondary
            std::cout << "DualChannelPattern: Primary channel failed - switching to secondary" << std::endl;
            switchToSecondary();
        }
    }

    // Try secondary channel
    if (secondaryChannel->isEnabled() && secondaryChannel->isOperational()) {
        return secondaryChannel->processChannel();
    }

    // Both channels failed
    std::cerr << "DualChannelPattern: Both channels failed - entering fault-safe state" << std::endl;
    handleFault();
    return false;
}

bool DualChannelPattern::compareOutputs(double output1, double output2) {
    if (std::isnan(output1) || std::isnan(output2)) {
        return false;
    }

    double difference = std::abs(output1 - output2);
    double max_value = std::max(std::abs(output1), std::abs(output2));
    
    // Use relative tolerance for large values, absolute tolerance for small values
    double threshold = std::max(tolerance, tolerance * max_value);
    
    return difference <= threshold;
}

void DualChannelPattern::handleFault() {
    faultDetected = true;
    enterFaultSafeState();
}

void DualChannelPattern::enterFaultSafeState() {
    // Disable both channels
    if (primaryChannel) {
        primaryChannel->disable();
    }
    if (secondaryChannel) {
        secondaryChannel->disable();
    }

    // Call fault-safe callback if provided
    if (faultSafeCallback) {
        faultSafeCallback();
    }

    std::cout << "DualChannelPattern: Entered fault-safe state" << std::endl;
}

void DualChannelPattern::switchToSecondary() {
    if (primaryChannel) {
        primaryChannel->disable();
    }
    if (secondaryChannel && secondaryChannel->isOperational()) {
        secondaryChannel->enable();
    }
}
