#include "SensorDeviceDriver.h"

SensorDeviceDriver::SensorDeviceDriver(int id) 
    : sensorId(id), sensitivity(1), firstTransform(nullptr) {
}

SensorDeviceDriver::~SensorDeviceDriver() {
    // Note: We don't delete firstTransform here as it's managed by the Channel
}

void SensorDeviceDriver::setSensitivity(int sens) {
    sensitivity = sens;
}

int SensorDeviceDriver::getSensitivity() const {
    return sensitivity;
}

void SensorDeviceDriver::setFirstTransform(AbstractDataTransform* transform) {
    firstTransform = transform;
}

AbstractDataTransform* SensorDeviceDriver::getFirstTransform() const {
    return firstTransform;
}

void SensorDeviceDriver::startProcessing() {
    double rawData = acquireData();
    
    if (firstTransform != nullptr) {
        firstTransform->processData(rawData);
    }
    // If no transform is set, this might be an error condition
}
