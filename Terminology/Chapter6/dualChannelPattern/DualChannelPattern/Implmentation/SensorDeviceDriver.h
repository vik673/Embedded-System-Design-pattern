#ifndef SENSOR_DEVICE_DRIVER_H
#define SENSOR_DEVICE_DRIVER_H

/**
 * @brief Abstract base class for sensor device drivers
 * 
 * This class acquires physical data from one or more sensors to put into
 * the channel for processing.
 */
class SensorDeviceDriver {
public:
    SensorDeviceDriver() = default;
    virtual ~SensorDeviceDriver() = default;

    /**
     * @brief Pure virtual function to read sensor data
     * @return Raw sensor reading
     */
    virtual double readSensor() = 0;

    /**
     * @brief Initialize the sensor
     * @return true if initialization successful, false otherwise
     */
    virtual bool initialize() = 0;

    /**
     * @brief Check if sensor is operational
     * @return true if sensor is working properly, false otherwise
     */
    virtual bool isOperational() = 0;

    /**
     * @brief Get sensor identification
     * @return String identifying the sensor type
     */
    virtual const char* getSensorType() const = 0;
};

#endif // SENSOR_DEVICE_DRIVER_H
