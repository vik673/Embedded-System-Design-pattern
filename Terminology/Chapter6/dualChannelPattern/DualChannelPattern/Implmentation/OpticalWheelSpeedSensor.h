#ifndef OPTICAL_WHEEL_SPEED_SENSOR_H
#define OPTICAL_WHEEL_SPEED_SENSOR_H

#include "SensorDeviceDriver.h"
#include <random>

/**
 * @brief Optical wheel speed sensor implementation
 * 
 * This sensor uses a light shining on the inside of a train wheel and measures
 * the frequency of mark appearance to compute speed.
 */
class OpticalWheelSpeedSensor : public SensorDeviceDriver {
private:
    bool operational;
    double wheelCircumference; // in meters
    std::mt19937 rng;
    std::uniform_real_distribution<double> noise_dist;
    std::uniform_real_distribution<double> frequency_dist;

public:
    /**
     * @brief Constructor
     * @param circumference Wheel circumference in meters
     */
    explicit OpticalWheelSpeedSensor(double circumference = 2.5);

    /**
     * @brief Read sensor data - returns speed in m/s
     * @return Speed in meters per second
     */
    double readSensor() override;

    /**
     * @brief Initialize the optical sensor
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
     * @brief Set wheel circumference
     * @param circumference Wheel circumference in meters
     */
    void setWheelCircumference(double circumference);

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
     * @brief Simulate reading the optical frequency
     * @return Frequency in Hz
     */
    double readOpticalFrequency();
};

#endif // OPTICAL_WHEEL_SPEED_SENSOR_H
