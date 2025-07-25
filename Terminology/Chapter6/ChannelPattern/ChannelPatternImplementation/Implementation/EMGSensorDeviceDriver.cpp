#include "EMGSensorDeviceDriver.h"
#include <random>
#include <cmath>

EMGSensorDeviceDriver::EMGSensorDeviceDriver(int id) 
    : SensorDeviceDriver(id), voltage(0), amplificationFactor(10), noiseThreshold(0.1) {
}

EMGSensorDeviceDriver::~EMGSensorDeviceDriver() {
    // Cleanup EMG-specific resources if needed
}

double EMGSensorDeviceDriver::acquireData() {
    voltage = static_cast<int>(readPhysicalSensor());
    return static_cast<double>(voltage);
}

int EMGSensorDeviceDriver::getVoltage() const {
    return voltage;
}

void EMGSensorDeviceDriver::setAmplificationFactor(int factor) {
    amplificationFactor = factor;
}

void EMGSensorDeviceDriver::setNoiseThreshold(double threshold) {
    noiseThreshold = threshold;
}

double EMGSensorDeviceDriver::readPhysicalSensor() {
    // Simulate reading from actual EMG hardware
    int rawReading = simulateEMGReading();
    
    // Apply amplification
    double amplifiedSignal = rawReading * amplificationFactor * sensitivity;
    
    // Filter noise
    double filteredSignal = filterNoise(amplifiedSignal);
    
    return filteredSignal;
}

double EMGSensorDeviceDriver::filterNoise(double rawVoltage) {
    // Simple noise filtering - remove values below threshold
    if (std::abs(rawVoltage) < noiseThreshold) {
        return 0.0;
    }
    return rawVoltage;
}

int EMGSensorDeviceDriver::simulateEMGReading() {
    // Simulate EMG signal with some variability
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-5.0, 5.0);
    
    // Generate a base signal with some muscle activity pattern
    static double phase = 0.0;
    phase += 0.1;
    
    double baseSignal = 3.0 * std::sin(phase) + 1.5 * std::sin(2.0 * phase);
    double noise = dis(gen) * 0.5;
    
    return static_cast<int>(baseSignal + noise);
}
