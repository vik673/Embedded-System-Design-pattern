#ifndef GPS_SPEED_SENSOR_H
#define GPS_SPEED_SENSOR_H

#include "SensorDeviceDriver.h"
#include <random>
#include <chrono>

/**
 * @brief GPS speed sensor implementation
 * 
 * This sensor uses GPS to determine train speed through 3D triangulation
 * and position rate of change calculation.
 */
class GPSSpeedSensor : public SensorDeviceDriver {
private:
    bool operational;
    std::mt19937 rng;
    std::uniform_real_distribution<double> noise_dist;
    std::uniform_real_distribution<double> speed_dist;
    
    // Previous position for speed calculation
    double previousLatitude;
    double previousLongitude;
    std::chrono::steady_clock::time_point previousTime;
    bool hasPreviousPosition;

public:
    /**
     * @brief Constructor
     */
    GPSSpeedSensor();

    /**
     * @brief Read sensor data - returns speed in m/s
     * @return Speed in meters per second calculated from GPS position changes
     */
    double readSensor() override;

    /**
     * @brief Initialize the GPS sensor
     * @return true if initialization successful
     */
    bool initialize() override;

    /**
     * @brief Check if sensor is operational
     * @return true if operational
     */
    bool isOperational() override;

    /**
     * @brief Get sensor type identification
     * @return Sensor type string
     */
    const char* getSensorType() const override;

    /**
     * @brief Simulate sensor failure for testing
     */
    void simulateFailure();

    /**
     * @brief Restore sensor operation
     */
    void restoreOperation();

private:
    /**
     * @brief Simulate GPS position reading
     * @param latitude Reference to store latitude
     * @param longitude Reference to store longitude
     * @return true if position acquired successfully
     */
    bool getGPSPosition(double& latitude, double& longitude);

    /**
     * @brief Calculate distance between two GPS coordinates
     * @param lat1 First latitude
     * @param lon1 First longitude
     * @param lat2 Second latitude
     * @param lon2 Second longitude
     * @return Distance in meters
     */
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Validate GPS position data
     * @param latitude Latitude to validate
     * @param longitude Longitude to validate
     * @return true if position is valid
     */
    bool validatePosition(double latitude, double longitude);
};

#endif // GPS_SPEED_SENSOR_H
