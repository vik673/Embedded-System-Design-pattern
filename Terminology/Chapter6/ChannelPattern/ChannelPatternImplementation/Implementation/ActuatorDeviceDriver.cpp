#include "ActuatorDeviceDriver.h"
#include <limits>

ActuatorDeviceDriver::ActuatorDeviceDriver(int id) 
    : deviceId(id), currentValue(0.0), isEnabled(true) {
}

ActuatorDeviceDriver::~ActuatorDeviceDriver() {
    // Base destructor - derived classes should handle specific cleanup
}

double ActuatorDeviceDriver::getCurrentValue() const {
    return currentValue;
}

void ActuatorDeviceDriver::setEnabled(bool enabled) {
    isEnabled = enabled;
}

bool ActuatorDeviceDriver::isActuatorEnabled() const {
    return isEnabled;
}

int ActuatorDeviceDriver::getDeviceId() const {
    return deviceId;
}

bool ActuatorDeviceDriver::validateValue(double value) {
    // Basic validation - check for NaN and infinite values
    if (value != value) return false; // NaN check
    if (value == std::numeric_limits<double>::infinity()) return false;
    if (value == -std::numeric_limits<double>::infinity()) return false;
    
    // Derived classes can override for more specific validation
    return true;
}
