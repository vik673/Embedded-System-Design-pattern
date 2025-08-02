#include "AbstractDataTransform.h"
#include "ActuatorDeviceDriver.h"

AbstractDataTransform::AbstractDataTransform() 
    : nextTransform(nullptr), actuatorDriver(nullptr) {
}

AbstractDataTransform::~AbstractDataTransform() {
    // Note: We don't delete nextTransform or actuatorDriver here
    // as they are managed by the Channel or other owner objects
}

void AbstractDataTransform::setNextTransform(AbstractDataTransform* next) {
    nextTransform = next;
    // Clear actuator driver if we're setting a next transform
    if (next != nullptr) {
        actuatorDriver = nullptr;
    }
}

void AbstractDataTransform::setActuatorDriver(ActuatorDeviceDriver* driver) {
    actuatorDriver = driver;
    // Clear next transform if we're setting an actuator driver
    if (driver != nullptr) {
        nextTransform = nullptr;
    }
}

AbstractDataTransform* AbstractDataTransform::getNextTransform() const {
    return nextTransform;
}

ActuatorDeviceDriver* AbstractDataTransform::getActuatorDriver() const {
    return actuatorDriver;
}

void AbstractDataTransform::forwardData(double processedData) {
    if (nextTransform != nullptr) {
        // Pass data to next transformation in the chain
        nextTransform->processData(processedData);
    } else if (actuatorDriver != nullptr) {
        // Send data to actuator for final output
        actuatorDriver->actuate(processedData);
    }
    // If neither is set, this is an error condition that should be logged
}
