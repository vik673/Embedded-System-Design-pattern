#include "GPSSpeedSensor.h"
#include <iostream>
#include <cmath>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GPSSpeedSensor::GPSSpeedSensor()
    : operational(false), rng(std::random_device{}()),
      noise_dist(-0.05, 0.05), speed_dist(1.0, 15.0),
      previousLatitude(0.0), previousLongitude(0.0), hasPreviousPosition(false) {
}

double GPSSpeedSensor::readSensor() {
    if (!operational) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    double latitude, longitude;
    if (!getGPSPosition(latitude, longitude)) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    if (!validatePosition(latitude, longitude)) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    auto currentTime = std::chrono::steady_clock::now();

    if (!hasPreviousPosition) {
        // First reading, can't calculate speed yet
        previousLatitude = latitude;
        previousLongitude = longitude;
        previousTime = currentTime;
        hasPreviousPosition = true;
        return 0.0; // Assume stationary for first reading
    }

    // Calculate time difference
    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime);
    double timeSeconds = timeDiff.count() / 1000.0;

    if (timeSeconds <= 0) {
        return 0.0;
    }

    // Calculate distance moved
    double distance = calculateDistance(previousLatitude, previousLongitude, latitude, longitude);
    
    // Calculate speed
    double speed = distance / timeSeconds;

    // Add some noise to simulate real GPS uncertainty
    speed += noise_dist(rng);

    // Update previous position
    previousLatitude = latitude;
    previousLongitude = longitude;
    previousTime = currentTime;

    return std::max(0.0, speed);
}

bool GPSSpeedSensor::initialize() {
    std::cout << "Initializing GPS Speed Sensor..." << std::endl;
    
    // Simulate GPS satellite acquisition
    std::cout << "Acquiring GPS satellites..." << std::endl;
    
    operational = true;
    hasPreviousPosition = false;
    
    std::cout << "GPS Speed Sensor initialized successfully" << std::endl;
    return true;
}

bool GPSSpeedSensor::isOperational() {
    return operational;
}

const char* GPSSpeedSensor::getSensorType() const {
    return "GPS Speed Sensor";
}

void GPSSpeedSensor::simulateFailure() {
    operational = false;
    std::cout << "GPS Speed Sensor failure simulated" << std::endl;
}

void GPSSpeedSensor::restoreOperation() {
    operational = true;
    hasPreviousPosition = false; // Reset position tracking
    std::cout << "GPS Speed Sensor operation restored" << std::endl;
}

bool GPSSpeedSensor::getGPSPosition(double& latitude, double& longitude) {
    // Simulate GPS position reading
    // In real implementation, this would interface with GPS hardware/receiver
    
    // Simulate some movement around a base position
    static double baseLat = 40.7128; // New York City as example
    static double baseLon = -74.0060;
    static double offset = 0.0;
    
    offset += 0.0001; // Simulate movement
    
    latitude = baseLat + offset;
    longitude = baseLon + offset * 0.5;
    
    return true;
}

double GPSSpeedSensor::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    // Haversine formula for calculating distance between two GPS coordinates
    const double R = 6371000.0; // Earth's radius in meters
    
    double lat1Rad = lat1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double deltaLat = (lat2 - lat1) * M_PI / 180.0;
    double deltaLon = (lon2 - lon1) * M_PI / 180.0;
    
    double a = sin(deltaLat / 2.0) * sin(deltaLat / 2.0) +
               cos(lat1Rad) * cos(lat2Rad) *
               sin(deltaLon / 2.0) * sin(deltaLon / 2.0);
    
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    
    return R * c;
}

bool GPSSpeedSensor::validatePosition(double latitude, double longitude) {
    // Basic validation for GPS coordinates
    return (latitude >= -90.0 && latitude <= 90.0 &&
            longitude >= -180.0 && longitude <= 180.0);
}
